/****************************************************************
 * gcode.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef GCODE_H
#define GCODE_H

#include "log4qtdef.h"

#include <QString>
#include <QFile>
#include <QThread>
#include <QTextStream>
#include "definitions.h"
#include "rs232.h"
#include "coord3d.h"
#include "controlparams.h"

#define BUF_SIZE 300

#define RESPONSE_OK "ok"
#define RESPONSE_ERROR "error"

// as defined in the grbl project on github...
#define GRBL_RX_BUFFER_SIZE     128

#define CTRL_X '\x18'

#define DEFAULT_AXIS_COUNT      3
#define MAX_AXIS_COUNT          4

class CmdResponse
{
public:
    CmdResponse(const char *buf, int c, int l) : cmd(buf), count(c), line(l)
    {
        waitForMe = false;
        if (buf[0] == 'M')
        {
            int value = cmd.mid(1,-1).toInt();
            if (value == 9)
                waitForMe = true;
        }
    }
public:
    QString cmd;
    int count;
    int line;
    bool waitForMe;
};

class DecimalFilter
{
public:
    DecimalFilter(QString t) : token(t), decimals(0) {}
public:
    QString token;
    int decimals;
};

class GCode : public QObject
{
    Q_OBJECT

public:
    GCode();
/// T4
    void setPause(bool);
    void setAbort();
    void setReset();
    void setShutdown();
    int getSettingsItemCount();
	int getNumaxis();

    static void trimToEnd(QString& strline, QChar);

signals:
    void addList(QString line);
    void addListFull(QStringList list);
    void addListOut(QString line);
    void sendMsgSatusBar(QString msg);
    void stopSending();
    void portIsClosed(bool reopen);
    void portIsOpen(bool sendCode);
    void setCommandText(QString value);
    void adjustedAxis();
    void gcodeResult(int id, QString result);
    void setProgress(int);
    void setQueuedCommands(int, bool);
    void resetTimer(bool timeIt);
    void enableGrblDialogButton();
    void updateCoordinates(Coord3D maposReqKindchineCoord, Coord3D workCoord);
    void setLastState(QString state);
    void setLivePoint(double x, double y, bool isMM, bool isLiveCP);
/// T4
    void setLivePoint(QVector3D);
    void setNumLine(QString);

    void setVisCurrLine(int currLine);
    void setLcdState(bool valid);
    void setVisualLivenessCurrPos(bool isLiveCP);
/// T2
	void setVersionGrbl(QString versionGrbl );
/// T3
    void setLinesFile(QString  nbline, bool check);
/// T4
    void setUnitMmAll(bool usemm);

    void endHomeAxis();

public slots:
    void openPort(QString commPortStr, QString baudRate);
    void closePort(bool reopen);
    void sendGcode(QString line);
    void sendGcodeAndGetResult(int id, QString line);
///  T3
    void sendFile(QString path, bool checkfile) ;
    void gotoXYZFourth(QString line);
    void axisAdj(char axis, float coord, bool inv, bool absoluteAfterAxisAdj, int sliderZCount);
    void setResponseWait(ControlParams controlParams);
    void grblSetHome();
/// T4
    void sendGrblHelp();
    void sendGrblParameters() ;
    void sendGrblParserState();
    void sendGrblBuildInfo();
    void sendGrblStartupBlocks();
    void sendGrblCheck(bool);
    void sendGrblUnlock();
    void sendGrblHomingCycle();
    void sendGrblCycleStart();
    void sendGrblFeedHold() ;
    void sendGrblStatus();
    void sendGrblReset();
/// T3
    void setPosReqKind(int);

    void goToHome();
    void goToHomeAxis(char axis);

    QString removeUnsupportedCommands(QString line);

protected:
    void timerEvent(QTimerEvent *event);

private:
    enum PosReqStatus
    {
        POS_REQ_RESULT_OK,
        POS_REQ_RESULT_ERROR,
        POS_REQ_RESULT_TIMER_SKIP,
        POS_REQ_RESULT_UNAVAILABLE
    };
private:
    bool sendGcodeLocal(QString line, bool recordResponseOnFail = false, int waitSec = -1, bool aggressive = false, int currLine = 0);
/// T4
    bool waitForOk(QString& result, int waitCount, bool sentReqForLocation,
                    bool sentRequestForSettings, bool sentReqForParserState,
                    bool aggressive, bool finalize);
    bool waitForStartupBanner(QString& result, int waitSec, bool failOnNoFound);
    bool sendGcodeInternal(QString line, QString& result, bool recordResponseOnFail, int waitSec, bool aggressive, int currLine = 0);
    QString reducePrecision(QString line);
    bool isGCommandValid(float value, bool& toEndOfLine);
    bool isMCommandValid(float value);
    bool isPortOpen();
    QString getMoveAmountFromString(QString prefix, QString item);
    bool SendJog(QString strline, bool absoluteAfterAxisAdj);
    void parseCoordinates(const QString& received, bool aggressive);
    void pollPosWaitForIdle(bool checkMeasurementUnits);
    void checkAndSetCorrectMeasurementUnits();
    void setOldFormatMeasurementUnitControl();
    void setConfigureMmMode(bool setGrblUnits);
    void setConfigureInchesMode(bool setGrblUnits);
    QStringList doZRateLimit(QString strline, QString& msg, bool& xyRateSet);
    void sendStatusList(QStringList& listToSend);
    void clearToHome();
    bool checkGrbl(const QString& result);
    PosReqStatus positionUpdate(bool forceIfEnabled = false);
    bool checkForGetPosStr(QString& line);
    void setLivenessState(bool valid);
/// T4
    QString getNumGrblUnit();
    bool sendToPort(const char *buf, QString txt=QString());

    void gotoPause();

private:
    RS232 port;
    AtomicIntBool abortState;
    AtomicIntBool resetState;
    AtomicIntBool shutdownState;
/// T4
    AtomicIntBool pauseState;

    ControlParams controlParams;
    int errorCount;
    QString currComPort;
    bool doubleDollarFormat;
    AtomicIntBool settingsItemCount;
    QString lastState;
    bool incorrectMeasurementUnits;
    bool incorrectLcdDisplayUnits;
    Coord3D machineCoord, workCoord;
    Coord3D machineCoordLastIdlePos, workCoordLastIdlePos;
    double maxZ;
    QList<CmdResponse> sendCount;
    QTime parseCoordTimer;
    bool motionOccurred;
    int sliderZCount;
    QStringList grblCmdErrors;
    QStringList grblFilteredCmds;
    QTime pollPosTimer;
    bool positionValid;

    int sentI;
    int rcvdI;
    int numaxis;
/// T3
    bool checkState;
/// T4
    int posReqKind;
    QString versionGrbl;
};

#endif // GCODE_H
