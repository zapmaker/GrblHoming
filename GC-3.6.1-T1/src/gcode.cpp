/****************************************************************
 * gcode.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "gcode.h"

#include <QObject>

GCode::GCode()
    : errorCount(0), doubleDollarFormat(false),
      incorrectMeasurementUnits(false), incorrectLcdDisplayUnits(false),
      maxZ(0), motionOccurred(false),
      sliderZCount(0),
      positionValid(false),
      numaxis(DEFAULT_AXIS_COUNT)
{
    // use base class's timer - use it to capture random text from the controller
    startTimer(1000);
    // for position polling
    pollPosTimer.start();
}

void GCode::openPort(QString commPortStr, QString baudRate)
{
    numaxis = controlParams.useFourAxis ? MAX_AXIS_COUNT : DEFAULT_AXIS_COUNT;

    clearToHome();

    currComPort = commPortStr;

    port.setCharSendDelayMs(controlParams.charSendDelayMs);

    if (port.OpenComport(commPortStr, baudRate))
    {
        emit portIsOpen(true);
    }
    else
    {
        emit portIsClosed(false);
        QString msg = tr("Can't open COM port ") + commPortStr;
        sendMsg(msg);
        addList(msg);
        warn("%s", qPrintable(msg));

        addList(tr("-Is hardware connected to USB?") );
        addList(tr("-Is correct port chosen?") );
        addList(tr("-Does current user have sufficient permissions?") );
#if defined(Q_OS_LINUX)
        addList("-Is current user in sudoers group?");
#endif
        //QMessageBox(QMessageBox::Critical,"Error","Could not open port.",QMessageBox::Ok).exec();
    }
}

void GCode::closePort(bool reopen)
{
    port.CloseComport();
    emit portIsClosed(reopen);
}

bool GCode::isPortOpen()
{
    return port.isPortOpen();
}

// Abort means stop file send after the end of this line
void GCode::setAbort()
{
    // cross-thread operation, only set one atomic variable in this method (bool in this case) or add critsec
    abortState.set(true);
}

// Reset means immediately stop waiting for a response
void GCode::setReset()
{
    // cross-thread operation, only set one atomic variable in this method (bool in this case) or add critsec
    resetState.set(true);
}

// Shutdown means app is shutting down - we give thread about .3 sec to exit what it is doing
void GCode::setShutdown()
{
    // cross-thread operation, only set one atomic variable in this method (bool in this case) or add critsec
    shutdownState.set(true);
}

// Slot for interrupting current operation or doing a clean reset of grbl without changing position values
void GCode::sendGrblReset()
{
    clearToHome();

    QString x(CTRL_X);
    sendGcodeLocal(x, true, SHORT_WAIT_SEC);
}

void GCode::sendGrblUnlock()
{
    sendGcodeLocal(SET_UNLOCK_STATE_V08c);
}

// Slot for gcode-based 'zero out the current position values without motion'
void GCode::grblSetHome()
{
    clearToHome();

    if (numaxis == MAX_AXIS_COUNT)
/// LETARTARE T1
        gotoXYZFourth(QString("G92 x0 y0 z0 ").append(QString(controlParams.fourthAxisType)).toLower().append("0"));
	else
        gotoXYZFourth("G92 x0 y0 z0");
}

void GCode::goToHome()
{
    if (!motionOccurred)
        return;

    double maxZOver = maxZ;

    if (doubleDollarFormat)
    {
        maxZOver += (controlParams.useMm ? PRE_HOME_Z_ADJ_MM : (PRE_HOME_Z_ADJ_MM / MM_IN_AN_INCH));
    }
    else
    {
        // all reporting is in mm
        maxZOver += PRE_HOME_Z_ADJ_MM;
    }

    QString zpos = QString::number(maxZOver);

    gotoXYZFourth(QString("G0 z").append(zpos));

    if (numaxis == MAX_AXIS_COUNT)
/// LETARTARE T1
        gotoXYZFourth(QString("G1 x0 y0 z0 ").append(QString(controlParams.fourthAxisType)).toLower().append("0"));
	else
        gotoXYZFourth("G1 x0 y0 z0");

    maxZ -= maxZOver;

    motionOccurred = false;
}

// Slot called from other threads (i.e. main window, grbl dialog, etc.)
void GCode::sendGcode(QString line)
{
    bool checkMeasurementUnits = false;

    // empty line means we have just opened the com port
    if (line.length() == 0)
    {
        resetState.set(false);

        QString result;
        if (!waitForStartupBanner(result, SHORT_WAIT_SEC, false))
        {
            if (shutdownState.get() || resetState.get())
                return;
            // it is possible that we are already connected and missed the
            // signon banner. Force a reset (is this ok?) to get the banner

            emit addListOut("(CTRL-X)");

            char buf[2] = {0};

            buf[0] = CTRL_X;

			diag(qPrintable(tr("SENDING: 0x%02X (CTRL-X) to check presence of Grbl\n")), buf[0])  ;
            if (!port.SendBuf(buf, 1))
            {
                QString msg = tr("Sending to port failed");
				err("%s", qPrintable(msg));
                emit addList(msg);
                emit sendMsg(msg);
                return;
            }

            if (!waitForStartupBanner(result, SHORT_WAIT_SEC, true))
                return;
        }

        checkMeasurementUnits = true;
    }
    else
    {
        pollPosWaitForIdle(false);
        // normal send of actual commands
        sendGcodeLocal(line, false);
    }

    pollPosWaitForIdle(checkMeasurementUnits);
}

// keep polling our position and state until we are done running
void GCode::pollPosWaitForIdle(bool checkMeasurementUnits)
{
    if (controlParams.usePositionRequest
           && (controlParams.positionRequestType == PREQ_ALWAYS_NO_IDLE_CHK
                    || controlParams.positionRequestType == PREQ_ALWAYS
                    || checkMeasurementUnits))
    {
        bool immediateQuit = false;
        for (int i = 0; i < 10000; i++)
        {
            GCode::PosReqStatus ret = positionUpdate();
            if (ret == POS_REQ_RESULT_ERROR || ret == POS_REQ_RESULT_UNAVAILABLE)
            {
                immediateQuit = true;
                break;
            }
            else if (ret == POS_REQ_RESULT_TIMER_SKIP)
            {
                SLEEP(250);
                continue;
            }

            if (doubleDollarFormat)
            {
                if (lastState.compare("Run") != 0)
                    break;
            }
            else
            {
                if (machineCoordLastIdlePos == machineCoord
                    && workCoordLastIdlePos == workCoord)
                {
                    break;
                }

                machineCoordLastIdlePos = machineCoord;
                workCoordLastIdlePos = workCoord;
            }

            if (shutdownState.get())
                return;
        }

        if (immediateQuit)
            return;

        if (checkMeasurementUnits)
        {
            if (doubleDollarFormat)
                checkAndSetCorrectMeasurementUnits();
            else
                setOldFormatMeasurementUnitControl();
        }
    }
    else
    {
        setLivenessState(false);
    }
}

// Slot called from other thread that returns whatever text comes back from the controller
void GCode::sendGcodeAndGetResult(int id, QString line)
{
    QString result;

    emit sendMsg("");
    resetState.set(false);
    if (!sendGcodeInternal(line, result, false, SHORT_WAIT_SEC, false))
        result.clear();

    emit gcodeResult(id, result);
}

// To be called only from this class, not from other threads. Use above two methods for that.
// Wraps sendGcodeInternal() to allow proper handling of failure cases, etc.
bool GCode::sendGcodeLocal(QString line, bool recordResponseOnFail /* = false */, int waitSec /* = -1 */, bool aggressive /* = false */, int currLine /* = 0 */)
{
    QString result;
    sendMsg("");
    resetState.set(false);

    bool ret = sendGcodeInternal(line, result, recordResponseOnFail, waitSec, aggressive, currLine);
    if (shutdownState.get())
        return false;

    if (!ret && (!recordResponseOnFail || resetState.get()))
    {
        if (!resetState.get())
            emit stopSending();

        if (!ret && resetState.get())
        {
            resetState.set(false);
            port.Reset();
        }
    }
    else
    {
        if (checkGrbl(result))
        {
            emit enableGrblDialogButton();
        }
    }
    resetState.set(false);
    return ret;
}

bool GCode::checkGrbl(const QString& result)
{
    if (result.contains("Grbl"))
    {
        QRegExp rx("Grbl (\\d+)\\.(\\d+)(\\w*)");
        if (rx.indexIn(result) != -1 && rx.captureCount() > 0)
        {
            doubleDollarFormat = false;

            QStringList list = rx.capturedTexts();
            if (list.size() >= 3)
            {
                int majorVer = list.at(1).toInt();
                int minorVer = list.at(2).toInt();
                char letter = ' ';
                if (list.size() == 4 && list.at(3).size() > 0)
                {
                    letter = list.at(3).toLatin1().at(0);
                }

                if (majorVer > 0 || (minorVer > 8 && minorVer < 51) || letter > 'a')
                {
                    doubleDollarFormat = true;
                }

                diag(qPrintable(tr("Got Grbl Version (Parsed:) %d.%d%c ($$=%d)\n")),
                            majorVer, minorVer, letter, doubleDollarFormat);
            }

            if (!doubleDollarFormat)
                setUnitsTypeDisplay(true);
        }
        return true;
    }
    return false;
}

// Wrapped method. Should only be called from above method.
bool GCode::sendGcodeInternal(QString line, QString& result, bool recordResponseOnFail, int waitSec, bool aggressive, int currLine /* = 0 */)
{
    if (!port.isPortOpen())
    {
        QString msg = tr("Port not available yet")  ;
        err("%s", msg.toLocal8Bit().constData());
        emit addList(msg);
        emit sendMsg(msg);
        return false;
    }

    bool ctrlX = line.size() > 0 ? (line.at(0).toLatin1() == CTRL_X) : false;

    bool sentReqForLocation = false;
    bool sentReqForSettings = false;
    bool sentReqForParserState = false;

    if (checkForGetPosStr(line))
    {
        sentReqForLocation = true;
        setLivenessState(true);
    }
    else if (!line.compare(REQUEST_PARSER_STATE_V08c))
    {
        sentReqForParserState = true;
    }
    else if (!line.compare(SETTINGS_COMMAND_V08a))
    {
        if (doubleDollarFormat)
            line = SETTINGS_COMMAND_V08c;

        sentReqForSettings = true;
    }
    else
        motionOccurred = true;

    // adds to UI list, but prepends a > indicating a sent command
    if (ctrlX)
    {
        emit addListOut("(CTRL-X)");
    }
    else if (!sentReqForLocation)// if requesting location, don't add that "noise" to the output view
    {
/// T1 + fix bug
        QString nline(line);
        if (currLine && (line.at(0).toLatin1() != 'N') )
            nline = "L" + QString().setNum(currLine) + "  " + line;
 /// <--
        emit addListOut(nline);
    }

    if (line.size() == 0 || (!line.endsWith('\r') && !ctrlX))
        line.append('\r');

    char buf[BUF_SIZE + 1] = {0};
    if (line.length() >= BUF_SIZE)
    {
        QString msg = tr("Buffer size too small");
        err("%s", qPrintable(msg));
        emit addList(msg);
        emit sendMsg(msg);
        return false;
    }
    for (int i = 0; i < line.length(); i++)
        buf[i] = line.at(i).toLatin1();

    if (ctrlX)
        diag(qPrintable(tr("SENDING[%d]: 0x%02X (CTRL-X)\n")), currLine, buf[0]);
    else
       // diag(qPrintable(tr("SENDING[%d]: %s\n")), currLine, buf);
        diag(qPrintable(tr("SENDING[%d]: ->%s<-\n")), currLine, buf);

    int waitSecActual = waitSec == -1 ? controlParams.waitTime : waitSec;

    if (aggressive)
    {
        if (ctrlX)
            sendCount.append(CmdResponse("(CTRL-X)", line.length(), currLine));
        else
            sendCount.append(CmdResponse(buf, line.length(), currLine));

        //diag("DG Buffer Add %d", sendCount.size());

        emit setQueuedCommands(sendCount.size(), true);

        waitForOk(result, waitSecActual, false, false, aggressive, false);

        if (shutdownState.get())
            return false;
    }

    if (!port.SendBuf(buf, line.length()))
    {
        QString msg = tr("Sending to port failed")  ;
        err("%s", qPrintable(msg));
        emit addList(msg);
        emit sendMsg(msg);
        return false;
    }
    else
    {
        sentI++;
        if (!waitForOk(result, waitSecActual, sentReqForLocation, sentReqForParserState, aggressive, false))
        {
            diag(qPrintable(tr("WAITFOROK FAILED\n")));
            if (shutdownState.get())
                return false;

            if (!recordResponseOnFail && !(resetState.get() || abortState.get()))
            {
                QString msg = tr("Wait for ok failed");
                emit addList(msg);
                emit sendMsg(msg);
            }

            return false;
        }
        else
        {
            if (sentReqForSettings)
            {
                QStringList list = result.split("$");
                for (int i = 0; i < list.size(); i++)
                {
                    QString item = list.at(i);
                    const QRegExp rx(REGEXP_SETTINGS_LINE);

                    if (rx.indexIn(item, 0) != -1 && rx.captureCount() == 3)
                    {
                        QStringList capList = rx.capturedTexts();
                        if (!capList.at(1).compare("13"))
                        {
                            if (!capList.at(2).compare("0"))
                            {
                                if (!controlParams.useMm)
                                    incorrectLcdDisplayUnits = true;
                            }
                            else
                            {
                                if (controlParams.useMm)
                                    incorrectLcdDisplayUnits = true;
                            }
                            break;
                        }
                    }
                }

                settingsItemCount.set(list.size());
            }
        }
    }
    return true;
}

bool GCode::waitForOk(QString& result, int waitSec, bool sentReqForLocation, bool sentReqForParserState, bool aggressive, bool finalize)
{
    int okcount = 0;

    if (aggressive)
    {
        //if (!port.bytesAvailable()) //more conservative code
        if (!finalize || !port.bytesAvailable())
        {
            int total = 0;
            bool haveWait = false;
            foreach (CmdResponse cmdResp, sendCount)
            {
                total += cmdResp.count;
                if (cmdResp.waitForMe)
                {
                    haveWait = true;
                }
            }

            //printf("Total out (a): %d (%d) (%d)\n", total, sendCount.size(), haveWait);

            if (!haveWait)
            {
                if (total < (GRBL_RX_BUFFER_SIZE - 1))
                {
                    return true;
                }
            }
        }
    }

    char tmp[BUF_SIZE + 1] = {0};
    int count = 0;
    int waitCount = waitSec * 10;// multiplier depends on sleep values below
    bool status = true;
    result.clear();
    while (!result.contains(RESPONSE_OK) && !result.contains(RESPONSE_ERROR) && !resetState.get())
    {
        int n = port.PollComportLine(tmp, BUF_SIZE);
        if (n == 0)
        {
            if (aggressive && sendCount.size() == 0)
                return false;

            count++;
            SLEEP(100);
        }
        else if (n < 0)
        {
			QString Mes(tr("Error reading data from COM port\n"))  ;
            err(qPrintable(Mes));

            if (aggressive && sendCount.size() == 0)
                return false;
        }
        else
        {
            tmp[n] = 0;
            result.append(tmp);

            QString tmpTrim(tmp);
            int pos = tmpTrim.indexOf(port.getDetectedLineFeed());
            if (pos != -1)
                tmpTrim.remove(pos, port.getDetectedLineFeed().size());
            QString received(tmp);

            if (aggressive)
            {
                if (received.contains(RESPONSE_OK))
                {
                    if (sendCount.isEmpty()) {
                        err(qPrintable(tr("Unexpected: list is empty (o)!")));
                    }
                    else
                    {
                        CmdResponse cmdResp = sendCount.takeFirst();
                        diag(qPrintable(tr("GOT[%d]:%s for %s\n")), cmdResp.line, tmpTrim.toLocal8Bit().constData(), cmdResp.cmd.toLocal8Bit().constData());

						//diag("DG Buffer %d", sendCount.size());

						emit setQueuedCommands(sendCount.size(), true);
                    }
                    rcvdI++;
                    okcount++;
                }
                else if (received.contains(RESPONSE_ERROR))
                {
                    QString orig(tr("Error?"));
                    if (sendCount.isEmpty())
                        err(qPrintable(tr("Unexpected: list is empty (e)!")));
                    else
                    {
                        CmdResponse cmdResp = sendCount.takeFirst();
                        orig = cmdResp.cmd;
                        diag(qPrintable(tr("GOT[%d]:%s for %s\n")), cmdResp.line, tmpTrim.toLocal8Bit().constData(), orig.toLocal8Bit().constData());

						//diag("DG Buffer %d", sendCount.size());

                        emit setQueuedCommands(sendCount.size(), true);
                    }
                    errorCount++;
                    QString result;
                    QTextStream(&result) << received << " [for " << orig << "]";
                    emit addList(result);
                    grblCmdErrors.append(result);
                    rcvdI++;
                }
                else
                {
                    diag(qPrintable(tr("GOT:%s\n")), tmpTrim.toLocal8Bit().constData());
                    parseCoordinates(received, aggressive);
                }

                int total = 0;
                foreach (CmdResponse cmdResp, sendCount)
                {
                    total += cmdResp.count;
                }

                //printf("Total out (b): %d (%d)\n", total, sendCount.size());
                //printf("SENT:%d RCVD:%d\n", sentI, rcvdI);

                if (total >= (GRBL_RX_BUFFER_SIZE - 1))
                {
                    //diag("DG Loop again\n");
                    result.clear();
                    continue;
                }
                else if (port.bytesAvailable())
                {
                    // comment out this block for more conservative approach
                    if (!finalize && okcount > 0)
                    {
                        //diag("DG Leave early\n");
                        return true;
                    }

                    result.clear();
                    continue;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                diag(qPrintable(tr("GOT:%s\n")), tmpTrim.toLocal8Bit().constData());
            }

            if (!received.contains(RESPONSE_OK) && !received.contains(RESPONSE_ERROR))
            {
                if (sentReqForParserState)
                {
                    const QRegExp rx("\\[([\\s\\w\\.\\d]+)\\]");

                    if (rx.indexIn(received, 0) != -1 && rx.captureCount() == 1)
                    {
                        QStringList list = rx.capturedTexts();
                        if (list.size() == 2)
                        {
                            QStringList items = list.at(1).split(" ");
                            if (items.contains("G20"))// inches
                            {
                                if (controlParams.useMm)
                                    incorrectMeasurementUnits = true;
                                else
                                    incorrectMeasurementUnits = false;
                            }
                            else if (items.contains("G21"))// millimeters
                            {
                                if (controlParams.useMm)
                                    incorrectMeasurementUnits = false;
                                else
                                    incorrectMeasurementUnits = true;
                            }
                            else
                            {
                                // not in list!
                                incorrectMeasurementUnits = true;
                            }
                        }
                    }
                }
                else
                {
                    parseCoordinates(received, aggressive);
                }
            }
            count = 0;
        }

        SLEEP(100);

        if (count > waitCount)
        {
            // waited too long for a response, fail
            status = false;
            break;
        }
    }

    if (shutdownState.get())
    {
        return false;
    }

    if (status)
    {
        if (!aggressive)
            SLEEP(100);

        if (resetState.get())
        {
            QString msg(tr("Wait interrupted by user"));
            err("%s", qPrintable(msg));
            emit addList(msg);
        }
    }

    if (result.contains(RESPONSE_ERROR))
    {
        errorCount++;
        // skip over errors
        //status = false;
    }

    QStringList list = QString(result).split(port.getDetectedLineFeed());
    QStringList listToSend;
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i).length() > 0 && list.at(i) != RESPONSE_OK && !sentReqForLocation && !list.at(i).startsWith("MPos:["))
            listToSend.append(list.at(i));
    }

    sendStatusList(listToSend);

    if (resetState.get())
    {
        // we have been told by the user to stop.
        status = false;
    }

    return status;
}

bool GCode::waitForStartupBanner(QString& result, int waitSec, bool failOnNoFound)
{
    char tmp[BUF_SIZE + 1] = {0};
    int count = 0;
    int waitCount = waitSec * 10;// multiplier depends on sleep values below
    bool status = true;
    result.clear();
    while (!resetState.get())
    {
        int n = port.PollComportLine(tmp, BUF_SIZE);
        if (n == 0)
        {
            count++;
            SLEEP(100);
        }
        else if (n < 0)
        {
            err(qPrintable(tr("Error reading data from COM port\n")) );
        }
        else
        {
            tmp[n] = 0;
            result.append(tmp);

            QString tmpTrim(tmp);
            int pos = tmpTrim.indexOf(port.getDetectedLineFeed());
            if (pos != -1)
                tmpTrim.remove(pos, port.getDetectedLineFeed().size());
            diag(qPrintable(tr("GOT:%s\n")), tmpTrim.toLocal8Bit().constData());

            if (tmpTrim.length() > 0)
            {
                if (!checkGrbl(tmpTrim))
                {
                    if (failOnNoFound)
                    {
                        QString msg(tr("Expecting Grbl version string. Unable to parse response."));
                        emit addList(msg);
                        emit sendMsg(msg);

                        closePort(false);
                    }
                    status = false;
                }
                else
                {
                    emit enableGrblDialogButton();
                }
                break;
            }
        }

        SLEEP(100);

        if (count > waitCount)
        {
            if (failOnNoFound)
            {
                // waited too long for a response, fail

                QString msg(tr("No data from COM port after connect. Expecting Grbl version string."));
                emit addList(msg);
                emit sendMsg(msg);

                closePort(false);
            }

            status = false;
            break;
        }
    }

    if (shutdownState.get())
    {
        return false;
    }

    if (status)
    {
        if (resetState.get())
        {
            QString msg(tr("Wait interrupted by user (startup)"));
            err("%s", qPrintable(msg));
            emit addList(msg);
        }
    }

    if (result.contains(RESPONSE_ERROR))
    {
        errorCount++;
        // skip over errors
        //status = false;
    }

    QStringList list = QString(result).split(port.getDetectedLineFeed());
    QStringList listToSend;
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i).length() > 0 && list.at(i) != RESPONSE_OK)
            listToSend.append(list.at(i));
    }

    sendStatusList(listToSend);

    if (resetState.get())
    {
        // we have been told by the user to stop.
        status = false;
    }

    return status;
}

/// LETARTARE T1
/*
/// May 13, 2014
	1- frame1 : < 8c (3 axes), 0.845 (4 axes)  	-> $$==0
		received == "MPos:[....],WPos:[....]"
	2- frame2 : 0.8c1 or 0.8c2 (4 axes)       			-> $$==1
		received == "<State,MPos:...,WPos:...>"
    3- frame2 : 0.8c (3 axes)        			-> $$==1
		received == "<State,MPos:...,WPos:...>"
    4- frame3 : 0.9d (3 axes), 0.9d1 (4 axes) 	-> $$==1
		received == "<State,MPos: ... ,WPos:...,Ln=..>"
*/

void GCode::parseCoordinates(const QString& received, bool aggressive)
{
    if (aggressive)
    {
        int ms = parseCoordTimer.elapsed();
        if (ms < 500)
            return;

        parseCoordTimer.restart();
    }

	bool good = false ;
	int captureCount ;
	QString state;
    QString prepend;
    QString append;
    QString preamble = "([a-zA-Z]+),MPos:";
    if (!doubleDollarFormat)
    {
        prepend = "\\[";
        append = "\\]";
        preamble = "MPos:" ;
    }
	QString coordRegExp;
	QRegExp rxStateMPos;
	QRegExp rxWPos;
/// 1 axis
	QString format1("(-*\\d+\\.\\d+)") ;
	QString sep(",");
	/// 3 axes
	QString format3 = format1 + sep + format1 + sep + format1 ;
	/// 4 axes
	QString format4 = format3 + sep + format1 ;
	QString format ;
    int naxis ;
	for (naxis = MAX_AXIS_COUNT; naxis >= DEFAULT_AXIS_COUNT; naxis--) {
		if (!doubleDollarFormat)
			captureCount = naxis ;
		else
			captureCount = naxis + 1 ;

        if (naxis == MAX_AXIS_COUNT )
			format = format4;
		else
			format = format3;

		coordRegExp = prepend + format + append ;
		rxStateMPos = QRegExp(preamble + coordRegExp);
        rxWPos = QRegExp(QString("WPos:") + coordRegExp);
		good = rxStateMPos.indexIn(received, 0) != -1
				&& rxStateMPos.captureCount() == captureCount
				&& rxWPos.indexIn(received, 0) != -1
				&& rxWPos.captureCount() == naxis
				;

		// find naxis ...
		if (good)
			break;
	}
	if (good) {  /// naxis contains number axis
        if (numaxis <= DEFAULT_AXIS_COUNT)
        {
            if (naxis > DEFAULT_AXIS_COUNT)
            {
                QString msg = tr("Incorrect - extra axis present in hardware but options set for only 3 axes. Please fix options.");
                emit addList(msg);
                emit sendMsg(msg);
            }
        }
        else
        {
            if (naxis <= DEFAULT_AXIS_COUNT)
            {
                QString msg = tr("Incorrect - extra axis not present in hardware but options set for > 3 axes. Please fix options.");
                emit addList(msg);
                emit sendMsg(msg);
            }
   }

		numaxis = naxis;
		QStringList list = rxStateMPos.capturedTexts();
		int index = 1;

		if (doubleDollarFormat)
			state = list.at(index++);

		machineCoord.x = list.at(index++).toFloat();
		machineCoord.y = list.at(index++).toFloat();
		machineCoord.z = list.at(index++).toFloat();
        if (numaxis == MAX_AXIS_COUNT)
            machineCoord.fourth = list.at(index++).toFloat();
		list = rxWPos.capturedTexts();
		workCoord.x = list.at(1).toFloat();
		workCoord.y = list.at(2).toFloat();
		workCoord.z = list.at(3).toFloat();
        if (numaxis == MAX_AXIS_COUNT)
            workCoord.fourth = list.at(4).toFloat();
		if (state != "Run")
			workCoord.stoppedZ = true;
		else
			workCoord.stoppedZ = false;

		workCoord.sliderZIndex = sliderZCount;

        if (doubleDollarFormat)
			diag(qPrintable(tr("Decoded: State:%s")),  qPrintable(state) );
        if (numaxis == DEFAULT_AXIS_COUNT)
            diag(qPrintable(tr("Decoded: MPos: %f,%f,%f WPos: %f,%f,%f\n")),
                 machineCoord.x, machineCoord.y, machineCoord.z,
                 workCoord.x, workCoord.y, workCoord.z
				 );
        else if (numaxis == MAX_AXIS_COUNT)
            diag(qPrintable(tr("Decoded: MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f\n")),
                 machineCoord.x, machineCoord.y, machineCoord.z, machineCoord.fourth,
                 workCoord.x, workCoord.y, workCoord.z, workCoord.fourth
				 );

		if (workCoord.z > maxZ)
			maxZ = workCoord.z;

		emit updateCoordinates(machineCoord, workCoord);
        emit setLivePoint(workCoord.x, workCoord.y, controlParams.useMm, positionValid);
		emit setLastState(state);

		lastState = state;
		return;
	}
    // TODO fix to print
    //if (!good /*&& received.indexOf("MPos:") != -1*/)
    //    err(qPrintable(tr("Error decoding position data! [%s]\n")), qPrintable(received));

    lastState = "";
}

void GCode::sendStatusList(QStringList& listToSend)
{
    if (listToSend.size() > 1)
    {
        emit addListFull(listToSend);
    }
    else if (listToSend.size() == 1)
    {
        emit addList(listToSend.at(0));
    }
}

// called once a second to capture any random strings that come from the controller
void GCode::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (port.isPortOpen())
    {
        char tmp[BUF_SIZE + 1] = {0};
        QString result;

        for (int i = 0; i < 10 && !shutdownState.get() && !resetState.get(); i++)
        {
            int n = port.PollComport(tmp, BUF_SIZE);
            if (n == 0)
                break;

            tmp[n] = 0;
            result.append(tmp);
            diag(qPrintable(tr("GOT-TE:%s\n")), tmp);
        }

        if (shutdownState.get())
        {
            return;
        }

        QStringList list = QString(result).split(port.getDetectedLineFeed());
        QStringList listToSend;
        for (int i = 0; i < list.size(); i++)
        {
            if (list.at(i).length() > 0 && (list.at(i) != "ok" || (list.at(i) == "ok" && abortState.get())))
                listToSend.append(list.at(i));
        }

        sendStatusList(listToSend);
    }
}

void GCode::sendFile(QString path)
{
    addList(QString(tr("Sending file '%1'")).arg(path));

    // send something to be sure the controller is ready
    //sendGcodeLocal("", true, SHORT_WAIT_SEC);

    setProgress(0);
    emit setQueuedCommands(0, false);
    grblCmdErrors.clear();
    grblFilteredCmds.clear();
    errorCount = 0;
    abortState.set(false);
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
/// LETARTARE T1
        int totalLineCount = 0;
        QTextStream code(&file);
        while ((code.atEnd() == false))
        {
            totalLineCount++;
            code.readLine();
        }
        if (totalLineCount == 0)
            totalLineCount = 1;

        code.seek(0);

        // set here once so that it doesn't change in the middle of a file send
        bool aggressive = controlParams.useAggressivePreload;
        if (aggressive)
        {
            sendCount.clear();
            //if (sendCount.size() == 0)
            //{
            //    diag("DG Buffer 0 at start\n"));
            //}

            emit setQueuedCommands(sendCount.size(), true);
        }

        sentI = 0;
        rcvdI = 0;
        emit resetTimer(true);

        parseCoordTimer.restart();

        int currLine = 0;
        bool xyRateSet = false;
/// LETARTARE T1
        QString strline ;
        do
        {
            strline = code.readLine();

            emit setVisCurrLine(currLine + 1);

            if (controlParams.filterFileCommands)
            {
                trimToEnd(strline, '(');
                trimToEnd(strline, ';');
                trimToEnd(strline, '%');
            }

            strline = strline.trimmed();

            if (strline.size() == 0)
            {}//ignore comments
            else
            {
                if (controlParams.filterFileCommands)
                {
                    strline = strline.toUpper();
                    strline.replace(QRegExp("([A-Z])"), " \\1");
                    strline = removeUnsupportedCommands(strline);
                }

                if (strline.size() != 0)
                {
                    if (controlParams.reducePrecision)
                    {
                        strline = reducePrecision(strline);
                    }

                    QString rateLimitMsg;
                    QStringList outputList;
                    if (controlParams.zRateLimit)
                    {
                        outputList = doZRateLimit(strline, rateLimitMsg, xyRateSet);
                    }
                    else
                    {
                        outputList.append(strline);
                    }

                    bool ret = false;
                    if (outputList.size() == 1)
                    {
                        ret = sendGcodeLocal(outputList.at(0), false, -1, aggressive, currLine + 1);
                    }
                    else
                    {
                        foreach (QString outputLine, outputList)
                        {
                            ret = sendGcodeLocal(outputLine, false, -1, aggressive, currLine + 1);

                            if (!ret)
                                break;
                        }
                    }

                    if (rateLimitMsg.size() > 0)
                        addList(rateLimitMsg);

                    if (!ret)
                    {
                        abortState.set(true);
                        break;
                    }
                }
            }

            float percentComplete = (currLine * 100.0) / totalLineCount;
            setProgress((int)percentComplete);

            positionUpdate();
            currLine++;
        } while ((code.atEnd() == false) && (!abortState.get()));
        file.close();

        if (aggressive)
        {
            int limitCount = 5000;
            while (sendCount.size() > 0 && limitCount)
            {
                QString result;
                waitForOk(result, controlParams.waitTime, false, false, aggressive, true);
                SLEEP(100);

                if (shutdownState.get())
                    return;

                if (abortState.get())
                    break;

                limitCount--;
            }

            if (!limitCount)
            {
                err(qPrintable(tr("Gave up waiting for OK\n")));
            }
        }

        positionUpdate();

        emit resetTimer(false);

        if (shutdownState.get())
        {
            return;
        }

        QString msg;
        if (!abortState.get())
        {
            setProgress(100);
            if (errorCount > 0)
            {
                msg = QString(tr("Code sent successfully with %1 error(s):")).arg(QString::number(errorCount));
                emit sendMsg(msg);
                emit addList(msg);

                foreach(QString errItem, grblCmdErrors)
                {
                    emit sendMsg(errItem);
                }
                emit addListFull(grblCmdErrors);
            }
            else
            {
                msg = tr("Code sent successfully with no errors.");
                emit sendMsg(msg);
                emit addList(msg);
            }

            if (grblFilteredCmds.size() > 0)
            {
                msg = QString(tr("Filtered %1 commands:")).arg(QString::number(grblFilteredCmds.size()));
                emit sendMsg(msg);
                emit addList(msg);

                foreach(QString errItem, grblFilteredCmds)
                {
                    emit sendMsg(errItem);
                }
                emit addListFull(grblFilteredCmds);
            }
        }
        else
        {
            msg = tr("Process interrupted.");
            emit sendMsg(msg);
            emit addList(msg);
        }
    }

    pollPosWaitForIdle(true);

    if (!resetState.get())
    {
        emit stopSending();
    }

    emit setQueuedCommands(0, false);
}

void GCode::trimToEnd(QString& strline, QChar ch)
{
    int pos = strline.indexOf(ch);
    if (pos != -1)
        strline = strline.left(pos);
}

QString GCode::removeUnsupportedCommands(QString line)
{
    QStringList components = line.split(" ", QString::SkipEmptyParts);
    QString tmp;
    QString s;
    QString following;
    bool toEndOfLine = false;
    foreach (s, components)
    {
        if (toEndOfLine)
        {
            QString msg(QString(tr("Removed unsupported command '%1' part of '%2'")).arg(s).arg(following));
            warn("%s", qPrintable(msg));
            grblFilteredCmds.append(msg);
            emit addList(msg);
            continue;
        }

        if (s.at(0) == 'G')
        {
            float value = s.mid(1,-1).toFloat();
            if (isGCommandValid(value, toEndOfLine))
                tmp.append(s).append(" ");
            else
            {
                if (toEndOfLine)
                    following = s;
                QString msg(QString(tr("Removed unsupported G command '%1'")).arg(s));
                warn("%s", qPrintable(msg));
                grblFilteredCmds.append(msg);
                emit addList(msg);
            }
        }
        else if (s.at(0) == 'M')
        {
            float value = s.mid(1,-1).toFloat();
            if (isMCommandValid(value))
                tmp.append(s).append(" ");
            else
            {
                QString msg(QString(tr("Removed unsupported M command '%1'")).arg(s));
                warn("%s", qPrintable(msg));
                grblFilteredCmds.append(msg);
                emit addList(msg);
            }
        }
        else if (s.at(0) == 'N')
        {
            // skip line numbers
        }
        else if (s.at(0) == 'X' || s.at(0) == 'Y' || s.at(0) == 'Z'
                 || s.at(0) == 'A' || s.at(0) == 'B' || s.at(0) == 'C'
/// LETARTARE
				|| s.at(0) == 'U' || s.at(0) == 'V' || s.at(0) == 'W'
/// <--
                 || s.at(0) == 'I' || s.at(0) == 'J' || s.at(0) == 'K'
                 || s.at(0) == 'F' || s.at(0) == 'L' || s.at(0) == 'S')
        {
            tmp.append(s).append(" ");
        }
        else
        {
            QString msg(QString(tr("Removed unsupported command '%1'")).arg(s));
            warn("%s", qPrintable(msg));
            grblFilteredCmds.append(msg);
            emit addList(msg);
        }
    }

    return tmp.trimmed();
}

QString GCode::reducePrecision(QString line)
{
    // first remove all spaces to determine what are line length is
    QStringList components = line.split(" ", QString::SkipEmptyParts);
    QString result;
    foreach(QString token, components)
    {
        result.append(token);
    }

    if (result.length() == 0)
        return line;// nothing to do

    if (!result.at(0).isLetter())
        return line;// leave as-is if not a command

    // find first comment and eliminate
    int pos = result.indexOf('(');
    if (pos >= 0)
        result = result.left(pos);

    int charsToRemove = result.length() - (controlParams.grblLineBufferLen - 1);// subtract 1 to account for linefeed sent with command later

    if (charsToRemove > 0)
    {
        // ok need to do something with precision
        // split apart based on letter
        pos = 0;
        components.clear();
        int i;
        for (i = 1; i < result.length(); i++)
        {
            if (result.at(i).isLetter())
            {
                components.append(result.mid(pos, i - pos));
                pos = i;
            }
        }

        if (pos == 0)
        {
            // we get here if only one command
            components.append(result);
        }
        else
        {
            // add last item
            components.append(result.mid(pos, i));
        }

        QList<DecimalFilter> items;
        foreach (QString tmp, components)
        {
            items.append(DecimalFilter(tmp));
        }

        int totalDecCount = 0;
        int eligibleArgumentCount = 0;
        int largestDecCount = 0;
        for (int j = 0; j < items.size(); j++)
        {
            DecimalFilter& item = items[j];
            pos = item.token.indexOf('.');
            if ((item.token.at(1).isDigit() || item.token.at(1) == '-' || item.token.at(1) == '.') && pos >= 0)
            {
                // candidate to modify
                // count number of decimal places
                int decPlaceCount = 0;
                for (i = pos + 1; i < item.token.length(); i++, decPlaceCount++)
                {
                    if (!item.token.at(i).isDigit())
                        break;
                }

                // skip commands that have a single decimal place
                if (decPlaceCount > 1)
                {
                    item.decimals = decPlaceCount;
                    totalDecCount += decPlaceCount - 1;// leave at least the last decimal place
                    eligibleArgumentCount++;
                    if (decPlaceCount > largestDecCount)
                        largestDecCount = decPlaceCount;
                }
            }
        }

        bool failRemoveSufficientDecimals = false;
        if (totalDecCount < charsToRemove)
        {
            // remove as many as possible, then grbl will truncate
            charsToRemove = totalDecCount;
            failRemoveSufficientDecimals = true;
        }

        if (eligibleArgumentCount > 0)
        {
            for (int k = largestDecCount; k > 1 && charsToRemove > 0; k--)
            {
                for (int j = 0; j < items.size() && charsToRemove > 0; j++)
                {
                    DecimalFilter& item = items[j];
                    if (item.decimals == k)
                    {
                        item.token.chop(1);
                        item.decimals--;
                        charsToRemove--;
                    }
                }
            }

            //chk.clear();
            //chk.append("CORRECTED:");
            result.clear();
            foreach (DecimalFilter item, items)
            {
                result.append(item.token);

                //chk.append("[");
                //chk.append(item.token);
                //chk.append("]");
            }
            //diag(chk.toLocal8Bit().constData());

            err(qPrintable(tr("Unable to remove enough decimal places for command (will be truncated): %s")), line.toLocal8Bit().constData());

            QString msg;
            if (failRemoveSufficientDecimals)
                msg = QString(tr("Error, insufficent reduction '%1'")).arg(result);
            else
                msg = QString(tr("Precision reduced '%1'")).arg(result);

            emit addList(msg);
            emit sendMsg(msg);
        }
    }

    return result;
}

bool GCode::isGCommandValid(float value, bool& toEndOfLine)
{
    toEndOfLine = false;
    // supported values obtained from https://github.com/grbl/grbl/wiki
    const static float supported[] =
    {
        0,    1,    2,    3,    4,
        10,    17,    18,    19,    20,    21,    28,    28.1,    30,    30.1,
        53,    54,    55,    56,    57,    58,    59,
        80,    90,    91,    92,    92.1,    93,    94
    };

    int len = sizeof(supported) / sizeof(float);
    for (int i = 0; i < len; i++)
    {
        if (value == supported[i])
            return true;
    }

    if (value == 43 || value == 44)
    {
        toEndOfLine = true;
    }
    return false;
}

bool GCode::isMCommandValid(float value)
{
    // supported values obtained from https://github.com/grbl/grbl/wiki

    // NOTE: M2 and M30 are supported but they cause occasional grbl lockups
    // and thus have been removed from the supported list. No harm is caused
    // by their removal.
    const static float supported[] =
    {
        0,    3,    4,    5,    8,    9
    };

    int len = sizeof(supported) / sizeof(float);
    for (int i = 0; i < len; i++)
    {
        if (value == supported[i])
            return true;
    }
    return false;
}

QStringList GCode::doZRateLimit(QString inputLine, QString& msg, bool& xyRateSet)
{
    // i.e.
    //G00 Z1 => G01 Z1 F100
    //G01 Z1 F260 => G01 Z1 F100
    //G01 Z1 F30 => G01 Z1 F30
    //G01 X1 Y1 Z1 F200 -> G01 X1 Y1 & G01 Z1 F100
    QStringList list;
    QString line = inputLine.toUpper();

    if (line.count("Z") > 0)
    {
        QStringList components = line.split(" ", QString::SkipEmptyParts);
        QString s;
        bool foundFeed = false;
        bool didLimit = false;

        // We need to build one or two command strings depending on input.
        QString x, y, g, f;

        // First get all component parts
        bool inLimit = false;
        foreach (s, components)
        {
            if (s.at(0) == 'G')
            {
                g = s;
            }
            else if (s.at(0) == 'F')
            {
                f = s;

                double value = s.mid(1,-1).toDouble();
                if (value > controlParams.zRateLimitAmount)
                    inLimit = true;
            }
            else if (s.at(0) == 'X')
            {
                x = s;
            }
            else if (s.at(0) == 'Y')
            {
                y = s;
            }
        }

        // Determine whether we want to have one or two command lins
        // 1 string: Have !G0 and F but not in limit
        // 1 string: Have Z only
        // 2 strings: All other conditions
        QString line1;
        QString line2;
        if ((g != "G0" && f.size() > 0 && !inLimit)
                || (x.size() == 0 && y.size() == 0))
        {
            foreach (s, components)
            {
                if (s.at(0) == 'G')
                {
                    int value = s.mid(1,-1).toInt();
                    if (value == 0)
                        line1.append("G1");
                    else
                        line1.append(s);
                }
                else if (s.at(0) == 'F')
                {
                    double value = s.mid(1,-1).toDouble();
                    if (value > controlParams.zRateLimitAmount)
                    {
                        line1.append("F").append(QString::number(controlParams.zRateLimitAmount));
                        didLimit = true;
                    }
                    else
                        line1.append(s);

                    foundFeed = true;
                }
                else
                {
                    line1.append(s);
                }
                line1.append(" ");
            }
        }
        else
        {
            // two lines
            foreach (s, components)
            {
                if (s.at(0) == 'G')
                {
                    int value = s.mid(1,-1).toInt();
                    if (value != 1)
                        line1.append("G1").append(" ");
                    else
                        line1.append(s).append(" ");

                    line2.append(s).append(" ");
                }
                else if (s.at(0) == 'F')
                {
                    double value = s.mid(1,-1).toDouble();
                    if (value > controlParams.zRateLimitAmount)
                    {
                        line1.append("F").append(QString::number(controlParams.zRateLimitAmount));
                        didLimit = true;
                    }
                    else
                        line1.append(s).append(" ");

                    line2.append(s).append(" ");

                    foundFeed = true;
                }
                else if (s.at(0) == 'Z')
                {
                    line1.append(s).append(" ");
                }
                else
                {
                    line2.append(s).append(" ");
                }
            }
        }

        if (!foundFeed)
        {
            line1.append("F").append(QString::number(controlParams.zRateLimitAmount));
            didLimit = true;
        }

        line1 = line1.trimmed();
        line2 = line2.trimmed();

        if (didLimit)
        {
            if (line2.size() == 0)
            {
                msg = QString(tr("Z-Rate Limit: [%1]=>[%2]")).arg(inputLine).arg(line1);
                xyRateSet = true;
            }
            else
            {
                msg = QString(tr("Z-Rate Limit: [%1]=>[%2,%3]")).arg(inputLine).arg(line1).arg(line2);
                line2.append(QString(" F").append(QString::number(controlParams.xyRateAmount)));
            }
        }

        list.append(line1);
        if (line2.size() > 0)
            list.append(line2);
        return list;
    }
    else if (xyRateSet)
    {
        QStringList components = line.split(" ", QString::SkipEmptyParts);
        QString s;

        bool addRateG = false;
        bool addRateXY = false;
        bool gotF = false;
        foreach (s, components)
        {
            if (s.at(0) == 'G')
            {
                int value = s.mid(1,-1).toInt();
                if (value != 0)
                {
                    addRateG = true;
                }
            }
            else if (s.at(0) == 'F')
            {
                gotF = true;
            }
            else
            if (s.at(0) == 'X' || s.at(0) == 'Y' || s.at(0) == 'A' || s.at(0) == 'B' || s.at(0) == 'C')
            {
                addRateXY = true;
            }
        }

        if (addRateG && addRateXY)
        {
            if (!gotF)
            {
                QString line = inputLine;
                line.append(QString(" F").append(QString::number(controlParams.xyRateAmount)));
                msg = QString(tr("XY-Rate Limit FIX: [%1]=>[%2]")).arg(inputLine).arg(line);
                list.append(line);
            }
            else
            {
                list.append(inputLine);
            }

            xyRateSet = false;

            return list;
        }
    }

    list.append(inputLine);
    return list;

}

void GCode::gotoXYZFourth(QString line)
{
    bool queryPos = checkForGetPosStr(line);
 if (!queryPos && controlParams.usePositionRequest
            && controlParams.positionRequestType == PREQ_ALWAYS)
        pollPosWaitForIdle(false);

    if (sendGcodeLocal(line))
    {
        line = line.toUpper();

        bool moveDetected = false;

        QStringList list = line.split(QRegExp("[\\s]+"));
        for (int i = 0; i < list.size(); i++)
        {
            QString item = getMoveAmountFromString("X", list.at(i));
            moveDetected = item.length() > 0;

            item = getMoveAmountFromString("Y", list.at(i));
            moveDetected = item.length() > 0;

            item = getMoveAmountFromString("Z", list.at(i));
            moveDetected = item.length() > 0 ;
            if (numaxis == MAX_AXIS_COUNT)  {
                item = getMoveAmountFromString(QString(controlParams.fourthAxisType), list.at(i));
				moveDetected = item.length() > 0;
			}
        }

        if (!moveDetected)
        {
            //emit addList("No movement expected for command.");
        }

        if (!queryPos)
            pollPosWaitForIdle(false);
    }
    else
    {
        QString msg(QString(tr("Bad command: %1")).arg(line));
        warn("%s", qPrintable(msg));
        emit addList(msg);
    }

    emit setCommandText("");
}


QString GCode::getMoveAmountFromString(QString prefix, QString item)
{
    int index = item.indexOf(prefix);
    if (index != -1)
        return item.mid(index + 1);

    return "";
}

void GCode::axisAdj(char axis, float coord, bool inv, bool absoluteAfterAxisAdj, int sZC)
{
    if (inv)
    {
        coord = (-coord);
    }

    QString cmd = QString("G01 ").append(axis)
            .append(QString::number(coord));

    if (axis == 'Z')
    {
        cmd.append(" F").append(QString::number(controlParams.zJogRate));
    }

    SendJog(cmd, absoluteAfterAxisAdj);

    if (axis == 'Z')
        sliderZCount = sZC;

    emit adjustedAxis();
}

bool GCode::SendJog(QString cmd, bool absoluteAfterAxisAdj)
{
    pollPosWaitForIdle(false);

    // G91 = distance relative to previous
    bool ret = sendGcodeLocal("G91\r");

    bool result = ret && sendGcodeLocal(cmd.append("\r"));

    if (result)
    {
        pollPosWaitForIdle(false);
    }

    if (absoluteAfterAxisAdj)
        sendGcodeLocal("G90\r");

    return result;
}

// settings change calls here
void GCode::setResponseWait(ControlParams controlParamsIn)
{
    bool oldMm = controlParams.useMm;

    controlParams = controlParamsIn;

    controlParams.useMm = oldMm;

    port.setCharSendDelayMs(controlParams.charSendDelayMs);

    if ((oldMm != controlParamsIn.useMm) && isPortOpen() && doubleDollarFormat)
    {
        if (controlParamsIn.useMm)
        {
            setConfigureMmMode(true);
        }
        else
        {
            setConfigureInchesMode(true);
        }
    }

    controlParams.useMm = controlParamsIn.useMm;
    numaxis = controlParams.useFourAxis ? MAX_AXIS_COUNT : DEFAULT_AXIS_COUNT;

    setUnitsTypeDisplay(controlParams.useMm);
}

int GCode::getSettingsItemCount()
{
    return settingsItemCount.get();
}

// 0.8c and above only!
void GCode::checkAndSetCorrectMeasurementUnits()
{
    sendGcodeLocal(REQUEST_PARSER_STATE_V08c, false);

    if (incorrectMeasurementUnits)
    {
        if (controlParams.useMm)
        {
            emit addList(tr("Options specify use mm but Grbl parser set for inches. Fixing."));
            setConfigureMmMode(true);
        }
        else
        {
            emit addList(tr("Options specify use inches but Grbl parser set for mm. Fixing.") );
            setConfigureInchesMode(true);
        }
        incorrectMeasurementUnits = false;// hope this is ok to do here
        positionUpdate(true);
    }
    else
    {
        sendGcodeLocal(SETTINGS_COMMAND_V08c);

        if (incorrectLcdDisplayUnits)
        {
            if (controlParams.useMm)
            {
                emit addList(tr("Options specify use mm but Grbl reporting set for inches. Fixing."));
                setConfigureMmMode(false);
            }
            else
            {
                emit addList(tr("Options specify use inches but Grbl reporting set for mm. Fixing."));
                setConfigureInchesMode(false);
            }
        }
        incorrectLcdDisplayUnits = false;
    }
}

void GCode::setOldFormatMeasurementUnitControl()
{
    if (controlParams.useMm)
        sendGcodeLocal("G21");
    else
        sendGcodeLocal("G20");
}

void GCode::setConfigureMmMode(bool setGrblUnits)
{
    sendGcodeLocal("$13=0");
    if (setGrblUnits)
        sendGcodeLocal("G21");
    positionUpdate(true);
}

void GCode::setConfigureInchesMode(bool setGrblUnits)
{
    sendGcodeLocal("$13=1");
    if (setGrblUnits)
        sendGcodeLocal("G20");
    positionUpdate(true);
}

void GCode::setUnitsTypeDisplay(bool millimeters)
{
    if (millimeters)
    {
        emit setUnitsWork(tr("(mm)"));
        emit setUnitsMachine(tr("(mm)"));
    }
    else
    {
        emit setUnitsWork(tr("(in)"));
        emit setUnitsMachine(tr("(in)"));
    }
}

void GCode::clearToHome()
{
    maxZ = 0;
    motionOccurred = false;
}

int GCode:: getNumaxis()
{
	return numaxis;
}

GCode::PosReqStatus GCode::positionUpdate(bool forceIfEnabled /* = false */)
{
    if (controlParams.usePositionRequest)
    {
        if (forceIfEnabled)
        {
            return sendGcodeLocal(REQUEST_CURRENT_POS) ? POS_REQ_RESULT_OK : POS_REQ_RESULT_ERROR;
        }
        else
        {
            int ms = pollPosTimer.elapsed();
            if (ms >= controlParams.postionRequestTimeMilliSec)
            {
                pollPosTimer.restart();
                return sendGcodeLocal(REQUEST_CURRENT_POS) ? POS_REQ_RESULT_OK : POS_REQ_RESULT_ERROR;
            }
            else
            {
                return POS_REQ_RESULT_TIMER_SKIP;
            }
        }
    }
    return POS_REQ_RESULT_UNAVAILABLE;
}

bool GCode::checkForGetPosStr(QString& line)
{
    return (!line.compare(REQUEST_CURRENT_POS)
        || (line.startsWith(REQUEST_CURRENT_POS) && line.endsWith('\r') && line.length() == 2));
}

void GCode::setLivenessState(bool valid)
{
    positionValid = valid;
    emit setVisualLivenessCurrPos(valid);
    emit setLcdState(valid);
}
