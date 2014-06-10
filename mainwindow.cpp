/****************************************************************
 * mainwindow.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "mainwindow.h"
#include "version.h"
#include "ui_mainwindow.h"

extern Log4Qt::FileAppender *p_fappender;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
   // open_button_text(tr(OPEN_BUTTON_TEXT)),
   // close_button_text(tr(CLOSE_BUTTON_TEXT)),
    open_button_text(tr("Open")),
    close_button_text(tr("Close / Reset")),
    absoluteAfterAxisAdj(false),
    checkLogWrite(false),
    sliderPressed(false),
    sliderTo(0.0),
    sliderZCount(0),
    queuedCommandsStarved(false), lastQueueCount(0), queuedCommandState(QCS_OK),
    lastLcdStateValid(true)
{
    // Setup our application information to be used by QSettings
    QCoreApplication::setOrganizationName(COMPANY_NAME);
    QCoreApplication::setOrganizationDomain(DOMAIN_NAME);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    // required if passing the object by reference into signals/slots
    qRegisterMetaType<Coord3D>("Coord3D");
    qRegisterMetaType<PosItem>("PosItem");
    qRegisterMetaType<ControlParams>("ControlParams");


    ui->setupUi(this);

    readSettings();

    info("%s has started", GRBL_CONTROLLER_NAME_AND_VERSION);

    // see http://blog.qt.digia.com/2010/06/17/youre-doing-it-wrong/
    // The thread points out that the documentation for QThread is wrong :) and
    // you should NOT subclass from QThread and override run(), rather,
    // attach your QOBJECT to a thread and use events (signals/slots) to communicate.
    gcode.moveToThread(&gcodeThread);
    runtimeTimer.moveToThread(&runtimeTimerThread);

    ui->lcdWorkNumberX->setDigitCount(8);
    ui->lcdMachNumberX->setDigitCount(8);
    ui->lcdWorkNumberY->setDigitCount(8);
    ui->lcdMachNumberY->setDigitCount(8);
    ui->lcdWorkNumberZ->setDigitCount(8);
    ui->lcdMachNumberZ->setDigitCount(8);
    ui->lcdWorkNumberFourth->setDigitCount(8);
    ui->lcdMachNumberFourth->setDigitCount(8);

    if (!controlParams.useFourAxis)
    {
        ui->DecFourthBtn->hide();
        ui->IncFourthBtn->hide();
        ui->lblFourthJog->hide();
        ui->lcdWorkNumberFourth->hide();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lcdMachNumberFourth->hide();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lblFourth->hide();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
    }

    //buttons
    connect(ui->btnOpenPort,SIGNAL(clicked()),this,SLOT(openPort()));
    connect(ui->btnGRBL,SIGNAL(clicked()),this,SLOT(setGRBL()));
    connect(ui->DecXBtn,SIGNAL(clicked()),this,SLOT(decX()));
    connect(ui->DecYBtn,SIGNAL(clicked()),this,SLOT(decY()));
    connect(ui->DecZBtn,SIGNAL(clicked()),this,SLOT(decZ()));
    connect(ui->IncXBtn,SIGNAL(clicked()),this,SLOT(incX()));
    connect(ui->IncYBtn,SIGNAL(clicked()),this,SLOT(incY()));
    connect(ui->IncZBtn,SIGNAL(clicked()),this,SLOT(incZ()));
    connect(ui->DecFourthBtn,SIGNAL(clicked()),this,SLOT(decFourth()));
    connect(ui->IncFourthBtn,SIGNAL(clicked()),this,SLOT(incFourth()));
    connect(ui->btnSetHome,SIGNAL(clicked()),this,SLOT(setHome()));
    connect(ui->comboCommand->lineEdit(),SIGNAL(editingFinished()),this,SLOT(gotoXYZFourth()));
    connect(ui->Begin,SIGNAL(clicked()),this,SLOT(begin()));
    connect(ui->openFile,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(ui->Stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->SpindleOn,SIGNAL(toggled(bool)),this,SLOT(toggleSpindle()));
    connect(ui->chkRestoreAbsolute,SIGNAL(toggled(bool)),this,SLOT(toggleRestoreAbsolute()));
    connect(ui->actionOptions,SIGNAL(triggered()),this,SLOT(getOptions()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->btnResetGrbl,SIGNAL(clicked()),this,SLOT(grblReset()));
    connect(ui->btnUnlockGrbl,SIGNAL(clicked()),this,SLOT(grblUnlock()));
    connect(ui->btnGoHomeSafe,SIGNAL(clicked()),this,SLOT(goHomeSafe()));
    connect(ui->verticalSliderZJog,SIGNAL(valueChanged(int)),this,SLOT(zJogSliderDisplay(int)));
    connect(ui->verticalSliderZJog,SIGNAL(sliderPressed()),this,SLOT(zJogSliderPressed()));
    connect(ui->verticalSliderZJog,SIGNAL(sliderReleased()),this,SLOT(zJogSliderReleased()));
    connect(ui->pushButtonRefreshPos,SIGNAL(clicked()),this,SLOT(refreshPosition()));
    connect(ui->comboStep,SIGNAL(currentIndexChanged(QString)),this,SLOT(comboStepChanged(QString)));

    connect(this, SIGNAL(sendFile(QString)), &gcode, SLOT(sendFile(QString)));
    connect(this, SIGNAL(openPort(QString,QString)), &gcode, SLOT(openPort(QString,QString)));
    connect(this, SIGNAL(closePort(bool)), &gcode, SLOT(closePort(bool)));
    connect(this, SIGNAL(sendGcode(QString)), &gcode, SLOT(sendGcode(QString)));
    connect(this, SIGNAL(gotoXYZFourth(QString)), &gcode, SLOT(gotoXYZFourth(QString)));
    connect(this, SIGNAL(axisAdj(char, float, bool, bool, int)), &gcode, SLOT(axisAdj(char, float, bool, bool, int)));
    connect(this, SIGNAL(setResponseWait(ControlParams)), &gcode, SLOT(setResponseWait(ControlParams)));
    connect(this, SIGNAL(shutdown()), &gcodeThread, SLOT(quit()));
    connect(this, SIGNAL(shutdown()), &runtimeTimerThread, SLOT(quit()));
    connect(this, SIGNAL(setProgress(int)), ui->progressFileSend, SLOT(setValue(int)));
    connect(this, SIGNAL(setRuntime(QString)), ui->outputRuntime, SLOT(setText(QString)));
    connect(this, SIGNAL(sendSetHome()), &gcode, SLOT(grblSetHome()));
    connect(this, SIGNAL(sendGrblReset()), &gcode, SLOT(sendGrblReset()));
    connect(this, SIGNAL(sendGrblUnlock()), &gcode, SLOT(sendGrblUnlock()));
    connect(this, SIGNAL(goToHome()), &gcode, SLOT(goToHome()));
    connect(this, SIGNAL(setItems(QList<PosItem>)), ui->wgtVisualizer, SLOT(setItems(QList<PosItem>)));
    
    connect(&gcode, SIGNAL(sendMsg(QString)),this,SLOT(receiveMsg(QString)));
    connect(&gcode, SIGNAL(portIsClosed(bool)), this, SLOT(portIsClosed(bool)));
    connect(&gcode, SIGNAL(portIsOpen(bool)), this, SLOT(portIsOpen(bool)));
    connect(&gcode, SIGNAL(addList(QString)),this,SLOT(receiveList(QString)));
    connect(&gcode, SIGNAL(addListFull(QStringList)),this,SLOT(receiveListFull(QStringList)));
    connect(&gcode, SIGNAL(addListOut(QString)),this,SLOT(receiveListOut(QString)));
    connect(&gcode, SIGNAL(stopSending()), this, SLOT(stopSending()));
    connect(&gcode, SIGNAL(setCommandText(QString)), ui->comboCommand->lineEdit(), SLOT(setText(QString)));
    connect(&gcode, SIGNAL(setProgress(int)), ui->progressFileSend, SLOT(setValue(int)));
    connect(&gcode, SIGNAL(setQueuedCommands(int, bool)), this, SLOT(setQueuedCommands(int, bool)));
    connect(&gcode, SIGNAL(adjustedAxis()), this, SLOT(adjustedAxis()));
    connect(&gcode, SIGNAL(resetTimer(bool)), &runtimeTimer, SLOT(resetTimer(bool)));
    connect(&gcode, SIGNAL(enableGrblDialogButton()), this, SLOT(enableGrblDialogButton()));
    connect(&gcode, SIGNAL(updateCoordinates(Coord3D,Coord3D)), this, SLOT(updateCoordinates(Coord3D,Coord3D)));
    connect(&gcode, SIGNAL(setLastState(QString)), ui->outputLastState, SLOT(setText(QString)));
    connect(&gcode, SIGNAL(setUnitsWork(QString)), ui->outputUnitsWork, SLOT(setText(QString)));
    connect(&gcode, SIGNAL(setUnitsMachine(QString)), ui->outputUnitsMachine, SLOT(setText(QString)));
    connect(&gcode, SIGNAL(setLivePoint(double, double, bool, bool)), ui->wgtVisualizer, SLOT(setLivePoint(double, double, bool, bool)));
    connect(&gcode, SIGNAL(setVisualLivenessCurrPos(bool)), ui->wgtVisualizer, SLOT(setVisualLivenessCurrPos(bool)));
    connect(&gcode, SIGNAL(setVisCurrLine(int)), ui->wgtVisualizer, SLOT(setVisCurrLine(int)));
    connect(&gcode, SIGNAL(setLcdState(bool)), this, SLOT(setLcdState(bool)));

    connect(&runtimeTimer, SIGNAL(setRuntime(QString)), ui->outputRuntime, SLOT(setText(QString)));

    runtimeTimerThread.start();
    gcodeThread.start();

    queuedCommandsEmptyTimer.start();
    queuedCommandsRefreshTimer.start();

    // Cool utility class off Google code that enumerates COM ports in platform-independent manner
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    int portIndex = -1;
    for (int i = 0; i < ports.size(); i++)
    {
        ui->cmbPort->addItem(ports.at(i).portName.toLocal8Bit().constData());

        if (ports.at(i).portName == lastOpenPort)
            portIndex = i;

        //diag("port name: %s\n", ports.at(i).portName.toLocal8Bit().constData());
        //diag("friendly name: %s\n", ports.at(i).friendName.toLocal8Bit().constData());
        //diag("physical name: %s\n", ports.at(i).physName.toLocal8Bit().constData());
        //diag("enumerator name: %s\n", ports.at(i).enumName.toLocal8Bit().constData());
        //diag("===================================\n\n");
    }

    if (portIndex >= 0)
    {
        // found matching port
        ui->cmbPort->setCurrentIndex(portIndex);
    }
    else if (lastOpenPort.size() > 0)
    {
        // did not find matching port
        // This code block is used to restore a port to view that isn't visible to QextSerialEnumerator
        ui->cmbPort->addItem(lastOpenPort.toLocal8Bit().constData());
        if (ports.size() > 0)
            ui->cmbPort->setCurrentIndex(ports.size());
        else
            ui->cmbPort->setCurrentIndex(0);
    }

    int baudRates[] = { 9600, 19200, 38400, 57600, 115200 };
    int baudRateCount = sizeof baudRates / sizeof baudRates[0];
    int baudRateIndex = 0;
    for (int i = 0; i < baudRateCount; i++)
    {
        QString baudRate = QString::number(baudRates[i]);
        ui->comboBoxBaudRate->addItem(baudRate);
        if (baudRate == lastBaudRate)
        {
            baudRateIndex = i;
        }
    }

    ui->comboBoxBaudRate->setCurrentIndex(baudRateIndex);

    ui->tabAxisVisualizer->setEnabled(false);
    if (!controlParams.useFourAxis)
    {
        ui->lcdWorkNumberFourth->setEnabled(false);;
        ui->lcdMachNumberFourth->setEnabled(false);;
        ui->IncFourthBtn->setEnabled(false);
        ui->DecFourthBtn->setEnabled(false);
        ui->lblFourthJog->setEnabled(false);
    }
    ui->groupBoxSendFile->setEnabled(true);
    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
    ui->Begin->setEnabled(false);
    ui->Stop->setEnabled(false);

    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);

    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    ui->btnGRBL->setEnabled(false);
    ui->btnSetHome->setEnabled(false);
    ui->btnResetGrbl->setEnabled(false);
    ui->btnUnlockGrbl->setEnabled(false);
    ui->btnGoHomeSafe->setEnabled(false);
    ui->pushButtonRefreshPos->setEnabled(false);
    styleSheet = ui->btnOpenPort->styleSheet();
    //ui->statusList->setEnabled(true);
    ui->openFile->setEnabled(true);

    this->setWindowTitle(GRBL_CONTROLLER_NAME_AND_VERSION);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    QSettings settings;
    QString useAggrPreload = settings.value(SETTINGS_USE_AGGRESSIVE_PRELOAD, "true").value<QString>();
    controlParams.useAggressivePreload = useAggrPreload == "true";

    if (!controlParams.useAggressivePreload && !promptedAggrPreload)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("You appear to have upgraded to the latest version of Grbl Controller. "
                       "Please be aware that as of version 3.4 the default behavior of sending commands "
                       "to Grbl has been changed to send them as fast as possible (Aggressive preload mode).\n\n"
                       "Your settings have been changed to enable this mode. Why? Because it provides the most "
                       "optimal use of Grbl and greatly reduces the time to finish a typical job.\n\n"
                       "What does this mean to you? "
                       "Arc commands will now run smoother and faster than before, which may "
                       "cause your spindle to work slightly harder, so please run some tests first. "
                       "Alternately, go to the Options dialog and manually disable Aggressive Preload") );
        msgBox.exec();

        controlParams.useAggressivePreload = true;
        settings.setValue(SETTINGS_USE_AGGRESSIVE_PRELOAD, controlParams.useAggressivePreload);
    }

    promptedAggrPreload = true;

    emit setResponseWait(controlParams);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// called when user has clicked the close application button
void MainWindow::closeEvent(QCloseEvent *event)
{
    gcode.setShutdown();
    gcode.setAbort();
    gcode.setReset();

    writeSettings();

    info("%s has stopped", GRBL_CONTROLLER_NAME_AND_VERSION);

    SLEEP(300);

    emit shutdown();

    event->accept();
}

void MainWindow::begin()
{
    if (ui->tabAxisVisualizer->currentIndex() != TAB_VISUALIZER_INDEX)
    {
        emit ui->tabAxisVisualizer->setCurrentIndex(TAB_VISUALIZER_INDEX);
    }

    //receiveList("Starting File Send.");
    resetProgress();
    int ret = QMessageBox::No;
    if((ui->lcdWorkNumberX->value()!=0)||(ui->lcdWorkNumberY->value()!=0)||(ui->lcdWorkNumberZ->value()!=0)
        || (ui->lcdWorkNumberFourth->value()!=0))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Do you want to zero the displayed position before proceeding?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        ret = msgBox.exec();
        if(ret ==QMessageBox::Yes)
            setHome();
    }
    if(ret!=QMessageBox::Cancel)
    {
        ui->tabAxisVisualizer->setEnabled(false);
        ui->comboCommand->setEnabled(false);
        ui->labelCommand->setEnabled(false);
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(true);
        ui->progressFileSend->setEnabled(true);
        ui->progressQueuedCommands->setEnabled(true);
        ui->labelFileSendProgress->setEnabled(true);
        ui->labelQueuedCommands->setEnabled(true);
        ui->outputRuntime->setEnabled(true);
        ui->labelRuntime->setEnabled(true);
        ui->openFile->setEnabled(false);
        ui->btnGRBL->setEnabled(false);
        ui->btnUnlockGrbl->setEnabled(false);
        ui->btnSetHome->setEnabled(false);
        ui->btnGoHomeSafe->setEnabled(false);
        ui->pushButtonRefreshPos->setEnabled(false);
        emit sendFile(ui->filePath->text());
    }
}

void MainWindow::stop()
{
    gcode.setAbort();

    // Reenable a bunch of UI
    ui->Begin->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->btnGRBL->setEnabled(true);
    ui->btnSetHome->setEnabled(true);
    ui->btnResetGrbl->setEnabled(true);
    ui->btnUnlockGrbl->setEnabled(true);
    ui->btnGoHomeSafe->setEnabled(true);
    ui->pushButtonRefreshPos->setEnabled(true);
}

void MainWindow::grblReset()
{
    gcode.setAbort();
    gcode.setReset();
    emit sendGrblReset();
}

void MainWindow::grblUnlock()
{
    emit sendGrblUnlock();
}

void MainWindow::goHomeSafe()
{
    emit goToHome();
}

// slot called from GCode class to update our state
void MainWindow::stopSending()
{
    ui->tabAxisVisualizer->setEnabled(true);
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->lblFourthJog->setEnabled(controlParams.useFourAxis);
    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);
    ui->Begin->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    ui->btnOpenPort->setEnabled(true);
    ui->btnGRBL->setEnabled(true);
    ui->btnSetHome->setEnabled(true);
    ui->btnResetGrbl->setEnabled(true);
    ui->btnUnlockGrbl->setEnabled(true);
    ui->btnGoHomeSafe->setEnabled(true);
    ui->pushButtonRefreshPos->setEnabled(true);
    ui->openFile->setEnabled(true);
}

// User has asked to open the port
void MainWindow::openPort()
{
	QString Mes = tr("User clicked Port Open/Close");
    info(qPrintable(Mes) );

    openPortCtl(false);
}

// User has asked to set current position as 'home' = 0,0,0
void MainWindow::setHome()
{
    resetProgress();
    sendSetHome();
}

void MainWindow::resetProgress()
{
    setProgress(0);
    setQueuedCommands(0, false);
    setRuntime("");
}

// If the port isn't open, we ask to open it
// If the port is open, we close it, but if 'reopen' is
// true, we call back to this thread to reopen it which
// is done mainly to toggle the COM port state to reset
// the controller.
void MainWindow::openPortCtl(bool reopen)
{
    if (ui->btnOpenPort->text() == open_button_text)
    {
        // Port is closed if the button says 'Open'
        QString portStr = ui->cmbPort->currentText();
        QString baudRate = ui->comboBoxBaudRate->currentText();

        ui->btnOpenPort->setEnabled(false);
        ui->comboBoxBaudRate->setEnabled(false);
        emit openPort(portStr, baudRate);
    }
    else
    {
        if (!reopen)
            resetProgress();

        // presume button says 'Close' currently, meaning port is open

        // Tell gcode port thread to stop what it is doing immediately (within 0.1 sec)
        gcode.setAbort();
        gcode.setReset();

        // Disable a bunch of UI
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
        //ui->btnOpenPort->setEnabled(false);
        ui->openFile->setEnabled(false);

        ui->tabAxisVisualizer->setEnabled(false);
        ui->groupBoxSendFile->setEnabled(false);
        ui->comboCommand->setEnabled(false);
        ui->labelCommand->setEnabled(false);
        //ui->cmbPort->setEnabled(false);
        //ui->comboBoxBaudRate->setEnabled(false);
        //ui->btnOpenPort->setEnabled(false);
        ui->btnGRBL->setEnabled(false);

        // Send event to close the port
        emit closePort(reopen);
    }
}

// slot telling us that port was closed successfully
// if 'reopen' is true, reopen our port to toggle
// so we reset the controller
void MainWindow::portIsClosed(bool reopen)
{
    SLEEP(100);

    ui->tabAxisVisualizer->setEnabled(false);
    ui->groupBoxSendFile->setEnabled(false);
    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
    ui->cmbPort->setEnabled(true);
    ui->comboBoxBaudRate->setEnabled(true);
    ui->btnOpenPort->setEnabled(true);
    ui->btnOpenPort->setText(open_button_text);
    ui->btnOpenPort->setStyleSheet(styleSheet);
    ui->btnGRBL->setEnabled(false);
    ui->btnSetHome->setEnabled(false);
    ui->btnResetGrbl->setEnabled(false);
    ui->btnUnlockGrbl->setEnabled(false);
    ui->btnGoHomeSafe->setEnabled(false);
    ui->pushButtonRefreshPos->setEnabled(false);

    if (reopen)
    {
        receiveList(tr("Resetting port to restart controller"));
        openPortCtl(false);
    }
}

// slot that tells us the gcode thread successfully opened the port
void MainWindow::portIsOpen(bool sendCode)
{
    // Comm port successfully opened
    if (sendCode)
        sendGcode("");
}

void MainWindow::adjustedAxis()
{
    ui->tabAxisVisualizer->setEnabled(true);
    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);

    if (ui->filePath->text().length() > 0)
        ui->Begin->setEnabled(true);

    ui->Stop->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);

    ui->btnOpenPort->setEnabled(true);
    ui->openFile->setEnabled(true);
    ui->btnGRBL->setEnabled(true);
    ui->btnSetHome->setEnabled(true);
    ui->btnResetGrbl->setEnabled(true);
    ui->btnUnlockGrbl->setEnabled(true);
    ui->btnGoHomeSafe->setEnabled(true);
    ui->pushButtonRefreshPos->setEnabled(true);
}

void MainWindow::disableAllButtons()
{
    //ui->tabAxisVisualizer->setEnabled(false);
    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
    ui->Begin->setEnabled(false);
    ui->Stop->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    ui->openFile->setEnabled(false);
    ui->btnGRBL->setEnabled(false);
    ui->btnSetHome->setEnabled(false);
    ui->btnResetGrbl->setEnabled(false);
    ui->btnUnlockGrbl->setEnabled(false);
    ui->btnGoHomeSafe->setEnabled(false);
    ui->pushButtonRefreshPos->setEnabled(false);
}

void MainWindow::enableGrblDialogButton()
{
    ui->openFile->setEnabled(true);
    ui->btnOpenPort->setEnabled(true);
    ui->btnOpenPort->setText(close_button_text);
    ui->btnOpenPort->setStyleSheet("* { background-color: rgb(255,125,100) }");
    ui->cmbPort->setEnabled(false);
    ui->comboBoxBaudRate->setEnabled(false);
    ui->tabAxisVisualizer->setEnabled(true);
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->lblFourthJog->setEnabled(controlParams.useFourAxis);
    ui->groupBoxSendFile->setEnabled(true);
    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);
    ui->btnSetHome->setEnabled(true);
    ui->btnResetGrbl->setEnabled(true);
    ui->btnUnlockGrbl->setEnabled(true);
    ui->btnGoHomeSafe->setEnabled(true);
    ui->pushButtonRefreshPos->setEnabled(true);

    if (ui->filePath->text().length() > 0)
    {
        ui->Begin->setEnabled(true);
        ui->Stop->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
    }
    else
    {
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
    }

    ui->btnGRBL->setEnabled(true);
}

void MainWindow::incX()
{
    disableAllButtons();
    emit axisAdj('X', jogStep, invX, absoluteAfterAxisAdj, 0);
}

void MainWindow::incY()
{
    disableAllButtons();
    emit axisAdj('Y', jogStep, invY, absoluteAfterAxisAdj, 0);
}

void MainWindow::incZ()
{
    disableAllButtons();
    emit axisAdj('Z', jogStep, invZ, absoluteAfterAxisAdj, sliderZCount++);
}

void MainWindow::decX()
{
    disableAllButtons();
    emit axisAdj('X', -jogStep, invX, absoluteAfterAxisAdj, 0);
}

void MainWindow::decY()
{
    disableAllButtons();
    emit axisAdj('Y', -jogStep, invY, absoluteAfterAxisAdj, 0);
}

void MainWindow::decZ()
{
    disableAllButtons();
    emit axisAdj('Z', -jogStep, invZ, absoluteAfterAxisAdj, sliderZCount++);
}

void MainWindow::decFourth()
{
/// LETARTARE 25-04-2014
	char four = controlParams.fourthAxisType;
	if (four == FOURTH_AXIS_A || four == FOURTH_AXIS_B || four == FOURTH_AXIS_C) {
		float actual_position = ui->lcdWorkNumberFourth->value() ;
		if (actual_position >= -360.0 + jogStep ) {
			disableAllButtons();
			emit axisAdj(controlParams.fourthAxisType, -jogStep, invFourth, absoluteAfterAxisAdj, 0);
		}
		else  {
			ui->DecFourthBtn->setEnabled(false) ;
			ui->IncFourthBtn->setEnabled(true) ;
		}
	}
/// <--
	else  {
		disableAllButtons();
		emit axisAdj(controlParams.fourthAxisType, -jogStep, invFourth, absoluteAfterAxisAdj, 0);
	}

}
void MainWindow::incFourth()
{
/// LETARTARE 25-04-2014
	char four = controlParams.fourthAxisType;
	if (four == FOURTH_AXIS_A || four == FOURTH_AXIS_B || four == FOURTH_AXIS_C) {
		float actual_position = ui->lcdWorkNumberFourth->value() ;
		if (actual_position <= 360.0 - jogStep ) {
			disableAllButtons();
			emit axisAdj(controlParams.fourthAxisType, jogStep, invFourth, absoluteAfterAxisAdj, 0);
		}
		else {
			ui->DecFourthBtn->setEnabled(true) ;
			ui->IncFourthBtn->setEnabled(false) ;
		}
	}
/// <-
	else  {
		disableAllButtons();
		emit axisAdj(controlParams.fourthAxisType, jogStep, invFourth, absoluteAfterAxisAdj, 0);
	}
}

void MainWindow::getOptions()
{
    Options opt(this);
    opt.exec();
}

void MainWindow::gotoXYZFourth()
{
    if (ui->comboCommand->lineEdit()->text().length() == 0)
        return;

    QString line = ui->comboCommand->lineEdit()->text().append("\r");

    emit gotoXYZFourth(line);
}

void MainWindow::openFile()
{
    QFileDialog dialog(this, tr("Open File"),
                       directory,
                       tr("NC (*.nc);;All Files (*.*)"));

    dialog.setFileMode(QFileDialog::ExistingFile);

    if (nameFilter.size() > 0)
        dialog.selectNameFilter(nameFilter);

    if (fileOpenDialogState.size() > 0)
        dialog.restoreState(fileOpenDialogState);

    QString fileName;
    QStringList fileNames;
    if (dialog.exec())
    {
        fileOpenDialogState = dialog.saveState();

        fileNames = dialog.selectedFiles();
        if (fileNames.length() > 0)
            fileName = fileNames.at(0);

        nameFilter = dialog.selectedNameFilter();

        resetProgress();
    }

    int slash = fileName.lastIndexOf('/');
    if (slash == -1)
    {
        slash = fileName.lastIndexOf('\\');
    }

    directory = "";
    if (slash != -1)
    {
        directory = fileName.left(slash);
    }

    ui->filePath->setText(fileName);
    if(ui->filePath->text().length() > 0 && ui->btnOpenPort->text() == close_button_text)
    {
        ui->Begin->setEnabled(true);
        ui->Stop->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
    }
    else
    {
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
    }

    if (ui->filePath->text().length() > 0)
    {
        // read in the file to process it
        preProcessFile(ui->filePath->text());

        if (ui->tabAxisVisualizer->currentIndex() != TAB_VISUALIZER_INDEX)
        {
            emit ui->tabAxisVisualizer->setCurrentIndex(TAB_VISUALIZER_INDEX);
        }
    }
}

void MainWindow::preProcessFile(QString filepath)
{
    QFile file(filepath);
    if (file.open(QFile::ReadOnly))
    {
        posList.clear();

        float totalLineCount = 0;
        QTextStream code(&file);
        while ((code.atEnd() == false))
        {
            totalLineCount++;
            code.readLine();
        }
        if (totalLineCount == 0)
            totalLineCount = 1;

        code.seek(0);

        double x = 0;
        double y = 0;
        double i = 0;
        double j = 0;
        bool arc = false;
        bool cw = false;
        bool mm = true;
        int index = 0;
        int g = 0;

        bool zeroInsert = false;
        do
        {
            QString strline = code.readLine();

            index++;

            GCode::trimToEnd(strline, '(');
            GCode::trimToEnd(strline, ';');
            GCode::trimToEnd(strline, '%');

            strline = strline.trimmed();

            if (strline.size() == 0)
            {}//ignore comments
            else
            {
                strline = strline.toUpper();
                strline.replace("M6", "M06");
                strline.replace(QRegExp("([A-Z])"), " \\1");
                strline.replace(QRegExp("\\s+"), " ");
                //if (strline.contains("G", Qt::CaseInsensitive))
                {
                    if (processGCode(strline, x, y, i, j, arc, cw, mm, g))
                    {
                        if (!zeroInsert)
                        {
                            // insert 0,0 position
                            posList.append(PosItem(0, 0, 0, 0, false, false, mm, 0));
                            zeroInsert = true;
                        }
                        posList.append(PosItem(x, y, i, j, arc, cw, mm, index));

                        //printf("Got G command:%s (%f,%f)\n", strline.toLocal8Bit().constData(), x, y);
                    }
                }
            }
        } while (code.atEnd() == false);

        file.close();

        emit setItems(posList);
    }
    else
        printf("Can't open file\n");
}

bool MainWindow::processGCode(QString inputLine, double& x, double& y, double& i, double& j, bool& arc, bool& cw, bool& mm, int& g)
{
    QString line = inputLine.toUpper();

    QStringList components = line.split(" ", QString::SkipEmptyParts);
    QString s;
    arc = false;
    bool valid = false;
    int nextIsValue = NO_ITEM;
    foreach (s, components)
    {
        if (s.at(0) == 'G')
        {
            int value = s.mid(1,-1).toInt();
            if (value >= 0 && value <= 3)
            {
                g = value;
                if (value == 2)
                    cw = true;
                else if (value == 3)
                    cw = false;
            }
            else if (value == 20)
                mm = false;
            else if (value == 21)
                mm = true;
        }
        else if (g >= 0 && g <= 3 && s.at(0) == 'X')
        {
            x = decodeLineItem(s, X_ITEM, valid, nextIsValue);
        }
        else if (g >= 0 && g <= 3 && s.at(0) == 'Y')
        {
            y = decodeLineItem(s, Y_ITEM, valid, nextIsValue);
        }
        else if ((g == 2 || g == 3) && s.at(0) == 'I')
        {
            i = decodeLineItem(s, I_ITEM, arc, nextIsValue);
        }
        else if ((g == 2 || g == 3) && s.at(0) == 'J')
        {
            j = decodeLineItem(s, J_ITEM, arc, nextIsValue);
        }
        else if (nextIsValue != NO_ITEM)
        {
            switch (nextIsValue)
            {
            case X_ITEM:
                x = decodeDouble(s, valid);
                break;
            case Y_ITEM:
                y = decodeDouble(s, valid);
                break;
            case I_ITEM:
                i = decodeDouble(s, arc);
                break;
            case J_ITEM:
                j = decodeDouble(s, arc);
                break;
            };
            nextIsValue = NO_ITEM;
        }
    }

    return valid;
}

double MainWindow::decodeLineItem(const QString& item, const int next, bool& valid, int& nextIsValue)
{
    if (item.size() == 1)
    {
        nextIsValue = next;
        return 0;
    }
    else
    {
        nextIsValue = NO_ITEM;
        return decodeDouble(item.mid(1,-1), valid);
    }
}

double MainWindow::decodeDouble(QString value, bool& valid)
{
    /*
    QDoubleValidator v;
    int pos = 0;
    QValidator::State s = v.validate(value, pos);
    if (s == QValidator::Invalid)
        return 0;
    */
    if (value.indexOf(QRegExp("^[+-]?[0-9]*\\.?[0-9]*$")) == -1)
        return 0;
    valid = true;
    return value.toDouble();
}

void MainWindow::readSettings()
{
    // use platform-independent settings storage, i.e. registry under Windows
    QSettings settings;

    fileOpenDialogState = settings.value(SETTINGS_FILE_OPEN_DIALOG_STATE).value<QByteArray>();
    directory = settings.value(SETTINGS_DIRECTORY).value<QString>();
    nameFilter = settings.value(SETTINGS_NAME_FILTER).value<QString>();
    lastOpenPort = settings.value(SETTINGS_PORT).value<QString>();
    lastBaudRate = settings.value(SETTINGS_BAUD, QString::number(BAUD9600)).value<QString>();

    promptedAggrPreload = settings.value(SETTINGS_PROMPTED_AGGR_PRELOAD, false).value<bool>();

    QString absAfterAdj = settings.value(SETTINGS_ABSOLUTE_AFTER_AXIS_ADJ, "false").value<QString>();
    absoluteAfterAxisAdj = (absAfterAdj == "true");
    ui->chkRestoreAbsolute->setChecked(absoluteAfterAxisAdj);

    jogStepStr = settings.value(SETTINGS_JOG_STEP, "1").value<QString>();
    jogStep = jogStepStr.toFloat();

    int indexDesired = 0;
    QString steps[] = { "0.01", "0.1", "1", "10", "100" };
    for (unsigned int i = 0; i < (sizeof (steps) / sizeof (steps[0])); i++) {
        ui->comboStep->addItem(steps[i]);
        if (jogStepStr == steps[i]) {
            indexDesired = i;
        }
    }
    ui->comboStep->setCurrentIndex(indexDesired);

    settings.beginGroup( "mainwindow" );

    restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray());
    restoreState(settings.value( "savestate", saveState() ).toByteArray());
    move(settings.value( "pos", pos() ).toPoint());
    resize(settings.value( "size", size() ).toSize());
    if ( settings.value( "maximized", isMaximized() ).toBool() )
        showMaximized();

    settings.endGroup();

    updateSettingsFromOptionDlg(settings);
}

// Slot called from settings dialog after user made a change. Reload settings from registry.
void MainWindow::setSettings()
{
    QSettings settings;

    updateSettingsFromOptionDlg(settings);

    // update gcode thread with latest values
    emit setResponseWait(controlParams);
}

void MainWindow::updateSettingsFromOptionDlg(QSettings& settings)
{
    ui->statusLog->setMaximumBlockCount( settings.value( SETTINGS_MAX_STATUS_LINES, 0 ).value<int>() );

    QString sinvX = settings.value(SETTINGS_INVERSE_X, "false").value<QString>();
    QString sinvY = settings.value(SETTINGS_INVERSE_Y, "false").value<QString>();
    QString sinvZ = settings.value(SETTINGS_INVERSE_Z, "false").value<QString>();
    //QString smm = settings.value(SETTINGS_USE_MM_FOR_MANUAL_CMDS,"false").value<QString>();
    QString sinvFourth = settings.value(SETTINGS_INVERSE_FOURTH, "false").value<QString>();
    QString sdbgLog = settings.value(SETTINGS_ENABLE_DEBUG_LOG, "true").value<QString>();
    g_enableDebugLog.set(sdbgLog == "true");

    // only enable/not enable file logging at startup. There are some kind of
    // multithreaded issues turning on or off file logging at runtime causing
    // crashes.
    if (!checkLogWrite)
    {
        checkLogWrite = true;

        if (g_enableDebugLog.get())
        {
            p_fappender->activateOptions();
            Log4Qt::Logger::rootLogger()->addAppender(p_fappender);
        }
    }

    invX = sinvX == "true";
    invY = sinvY == "true";
    invZ = sinvZ == "true";
    invFourth = sinvFourth == "true";

    controlParams.waitTime = settings.value(SETTINGS_RESPONSE_WAIT_TIME, DEFAULT_WAIT_TIME_SEC).value<int>();
    controlParams.zJogRate = settings.value(SETTINGS_Z_JOG_RATE, DEFAULT_Z_JOG_RATE).value<double>();
    QString useMmManualCmds = settings.value(SETTINGS_USE_MM_FOR_MANUAL_CMDS, "true").value<QString>();
    controlParams.useMm = useMmManualCmds == "true";
    QString useAggrPreload = settings.value(SETTINGS_USE_AGGRESSIVE_PRELOAD, "true").value<QString>();
    controlParams.useAggressivePreload = useAggrPreload == "true";
    QString waitForJogToComplete = settings.value(SETTINGS_WAIT_FOR_JOG_TO_COMPLETE, "true").value<QString>();
    controlParams.waitForJogToComplete = waitForJogToComplete == "true";

    QString useFourAxis = settings.value(SETTINGS_FOUR_AXIS_USE, "false").value<QString>();
    controlParams.useFourAxis = useFourAxis == "true";
    if (controlParams.useFourAxis)
    {
        char type = settings.value(SETTINGS_FOUR_AXIS_TYPE, FOURTH_AXIS_A).value<char>();
        controlParams.fourthAxisType = type;
    }

    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->lblFourthJog->setEnabled(controlParams.useFourAxis);

    if (!controlParams.useFourAxis)
    {
        ui->DecFourthBtn->hide();
        ui->IncFourthBtn->hide();
        ui->lblFourthJog->hide();
        ui->lcdWorkNumberFourth->hide();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lcdMachNumberFourth->hide();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lblFourth->hide();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
    }
    else
    {
        ui->DecFourthBtn->show();
        ui->IncFourthBtn->show();
        ui->lblFourthJog->show();
        ui->lcdWorkNumberFourth->show();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lcdMachNumberFourth->show();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lblFourth->show();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lblFourth->setText(QString(controlParams.fourthAxisType));

        QString axisJog(tr("Z Jog"));// not correct, but a default placeholder we have a translation for already
        char axis = controlParams.fourthAxisType;
        if (axis == FOURTH_AXIS_A)
            axisJog = tr("A Jog");
        else if (axis == FOURTH_AXIS_B)
            axisJog = tr("B Jog");
        else if (axis == FOURTH_AXIS_C)
            axisJog = tr("C Jog");
        else if (axis == FOURTH_AXIS_U)
            axisJog = tr("U Jog");
        else if (axis == FOURTH_AXIS_V)
            axisJog = tr("V Jog");
        else if (axis == FOURTH_AXIS_W)
            axisJog = tr("W Jog");

        ui->lblFourthJog->setText(axisJog);
    }

    QString zRateLimit = settings.value(SETTINGS_Z_RATE_LIMIT, "false").value<QString>();
    controlParams.zRateLimit = zRateLimit == "true";

    QString ffCommands = settings.value(SETTINGS_FILTER_FILE_COMMANDS, "false").value<QString>();
    controlParams.filterFileCommands = ffCommands == "true";
    QString rPrecision = settings.value(SETTINGS_REDUCE_PREC_FOR_LONG_LINES, "false").value<QString>();
    controlParams.reducePrecision = rPrecision == "true";
    controlParams.grblLineBufferLen = settings.value(SETTINGS_GRBL_LINE_BUFFER_LEN, DEFAULT_GRBL_LINE_BUFFER_LEN).value<int>();
    controlParams.charSendDelayMs = settings.value(SETTINGS_CHAR_SEND_DELAY_MS, DEFAULT_CHAR_SEND_DELAY_MS).value<int>();

    controlParams.zRateLimitAmount = settings.value(SETTINGS_Z_RATE_LIMIT_AMOUNT, DEFAULT_Z_LIMIT_RATE).value<double>();
    controlParams.xyRateAmount = settings.value(SETTINGS_XY_RATE_AMOUNT, DEFAULT_XY_RATE).value<double>();

    QString enPosReq = settings.value(SETTINGS_ENABLE_POS_REQ, "true").value<QString>();
    controlParams.usePositionRequest = enPosReq == "true";
    controlParams.positionRequestType = settings.value(SETTINGS_TYPE_POS_REQ, PREQ_ALWAYS_NO_IDLE_CHK).value<QString>();
    double posReqFreq = settings.value(SETTINGS_POS_REQ_FREQ_SEC, DEFAULT_POS_REQ_FREQ_SEC).value<double>();
    controlParams.postionRequestTimeMilliSec = static_cast<int>(posReqFreq) * 1000;

    setLcdState(controlParams.usePositionRequest);
}

// save last state of settings
void MainWindow::writeSettings()
{
    QSettings settings;

    settings.setValue(SETTINGS_FILE_OPEN_DIALOG_STATE, fileOpenDialogState);
    settings.setValue(SETTINGS_NAME_FILTER, nameFilter);
    settings.setValue(SETTINGS_DIRECTORY, directory);
    settings.setValue(SETTINGS_PORT, ui->cmbPort->currentText());
    settings.setValue(SETTINGS_BAUD, ui->comboBoxBaudRate->currentText());

    settings.setValue(SETTINGS_PROMPTED_AGGR_PRELOAD, promptedAggrPreload);
    settings.setValue(SETTINGS_ABSOLUTE_AFTER_AXIS_ADJ, ui->chkRestoreAbsolute->isChecked());
    settings.setValue(SETTINGS_JOG_STEP, ui->comboStep->currentText());

    // From http://stackoverflow.com/questions/74690/how-do-i-store-the-window-size-between-sessions-in-qt
    settings.beginGroup("mainwindow");

    settings.setValue( "geometry", saveGeometry() );
    settings.setValue( "savestate", saveState() );
    settings.setValue( "maximized", isMaximized() );
    if ( !isMaximized() ) {
        settings.setValue( "pos", pos() );
        settings.setValue( "size", size() );
    }

    settings.endGroup();
}

void MainWindow::receiveList(QString msg)
{
    addToStatusList(true, msg);
}

void MainWindow::receiveListFull(QStringList list)
{
    addToStatusList(list);
}

void MainWindow::receiveListOut(QString msg)
{
    addToStatusList(false, msg);
}

void MainWindow::addToStatusList(bool in, QString msg)
{
    msg = msg.trimmed();
    msg.remove('\r');
    msg.remove('\n');

    if (msg.length() == 0)
        return;

    QString nMsg(msg);
    if (!in)
        nMsg = "> " + msg;

    ui->statusLog->appendPlainText( msg );
}

void MainWindow::addToStatusList(QStringList& list)
{
    foreach (QString msg, list)
    {
        msg = msg.trimmed();
        msg.remove('\r');
        msg.remove('\n');

        if (msg.length() == 0)
            continue;

        ui->statusLog->appendPlainText( msg );
        status("%s", msg.toLocal8Bit().constData());
    }
}

void MainWindow::receiveMsg(QString msg)
{
    ui->centralWidget->setStatusTip(msg);
}

void MainWindow::setGRBL()
{
    GrblDialog dlg(this, &gcode);
    dlg.setParent(this);
    dlg.getSettings();
    dlg.exec();
}

void MainWindow::showAbout()
{
    About about(this);
    about.exec();
}

void MainWindow::toggleSpindle()
{
    if (ui->SpindleOn->QAbstractButton::isChecked())
    {
        sendGcode("M03\r");
        receiveList(tr("Spindle On."));
    }
    else
    {
        sendGcode("M05\r");
        receiveList(tr("Spindle Off."));
    }
}

void MainWindow::toggleRestoreAbsolute()
{
    absoluteAfterAxisAdj = ui->chkRestoreAbsolute->QAbstractButton::isChecked();
}

void MainWindow::updateCoordinates(Coord3D machineCoord, Coord3D workCoord)
{
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->lblFourthJog->setEnabled(controlParams.useFourAxis);
    machineCoordinates = machineCoord;
    workCoordinates = workCoord;
/*
    if (workCoordinates.stoppedZ == false)
    {
        int newPos = workCoordinates.z + sliderTo;

        QString to;
        to.sprintf("%d", newPos);

        ui->resultingZJogSliderPosition->setText(to);
    }
*/
    refreshLcd();
}

void MainWindow::refreshLcd()
{
    lcdDisplay('X', true, workCoordinates.x);
    lcdDisplay('Y', true, workCoordinates.y);
    lcdDisplay('Z', true, workCoordinates.z);
    lcdDisplay('X', false, machineCoordinates.x);
    lcdDisplay('Y', false, machineCoordinates.y);
    lcdDisplay('Z', false, machineCoordinates.z);
    if (controlParams.useFourAxis) {
        lcdDisplay(controlParams.fourthAxisType, true, workCoordinates.fourth);
        lcdDisplay(controlParams.fourthAxisType, false, machineCoordinates.fourth);
	}
	else {
        lcdDisplay(controlParams.fourthAxisType, true, 0);
        lcdDisplay(controlParams.fourthAxisType, false, 0);
	}
}

void MainWindow::lcdDisplay(char axis, bool workCoord, float floatVal)
{
    QString value = QString::number(floatVal, 'f', 3);
    switch (axis)
    {
    case 'X':
        if (workCoord)
            ui->lcdWorkNumberX->display(value);
        else
            ui->lcdMachNumberX->display(value);
        break;
    case 'Y':
        if (workCoord)
            ui->lcdWorkNumberY->display(value);
        else
            ui->lcdMachNumberY->display(value);
        break;
    case 'Z':
        if (workCoord)
            ui->lcdWorkNumberZ->display(value);
        else
            ui->lcdMachNumberZ->display(value);
        break;
    default:
        if (axis == FOURTH_AXIS_A || axis == FOURTH_AXIS_B || axis == FOURTH_AXIS_C
///  LETARTARE
			|| axis == FOURTH_AXIS_U || axis == FOURTH_AXIS_V || axis == FOURTH_AXIS_W
/// <-
			)
        {
            if (workCoord)
                ui->lcdWorkNumberFourth->display(value);
            else
                ui->lcdMachNumberFourth->display(value);
        }
        else
        {
            err("Unexpected type %c", axis);
        }
        break;
    }
}

void MainWindow::zJogSliderDisplay(int pos)
{
    QString str;

    pos -= CENTER_POS;

    if (pos > 0)
        if(controlParams.useMm)
            str.sprintf("+%d", pos);
        else
            str.sprintf("+%.1f",(double)pos/10);
    else if (pos < 0)
        if(controlParams.useMm)
            str.sprintf("%d", pos);
        else
            str.sprintf("%.1f", (double)pos/10);
    else
        str = "0";

    ui->currentZJogSliderDelta->setText(str);

    double newPos;
    QString to;
    if(controlParams.useMm)
        newPos = pos + sliderTo;
    else
        newPos = (double)pos/10+sliderTo;

    if(controlParams.useMm)
        to.sprintf("%.1f", newPos);
    else
        to.sprintf("%.1f", newPos);

    if (sliderPressed)
    {
        ui->resultingZJogSliderPosition->setText(to);
        if(controlParams.useMm)
            info("Usr chg: pos=%d new=%d\n", pos, newPos);
        else
            info("Usr chg: pos=%.1f new=%.1f\n", (double)pos/10, newPos);
    }
    else
    {
        ui->verticalSliderZJog->setSliderPosition(CENTER_POS);
        ui->currentZJogSliderDelta->setText("0");
        if(controlParams.useMm)
            info("Usr chg no slider: %d\n", pos);
        else
            info("Usr chg no slider: %.1f\n", (double) pos/10);
    }
}

void MainWindow::zJogSliderPressed()
{
    sliderPressed = true;
    if (workCoordinates.stoppedZ && workCoordinates.sliderZIndex == sliderZCount)
    {
        info("Pressed and stopped\n");
        sliderTo = workCoordinates.z;
    }
    else
    {
        info("Pressed not stopped\n");
    }
}

void MainWindow::zJogSliderReleased()
{
    info("Released\n");
    if (sliderPressed)
    {
        sliderPressed = false;
        int value = ui->verticalSliderZJog->value();

        ui->verticalSliderZJog->setSliderPosition(CENTER_POS);
        ui->currentZJogSliderDelta->setText("0");

        value -= CENTER_POS;

        if (value != 0)
        {
            if(controlParams.useMm)
                sliderTo += value;
            else
                sliderTo += (double)value/10;
            float setTo = value;
            if(controlParams.useMm)
                emit axisAdj('Z', setTo, invZ, absoluteAfterAxisAdj, sliderZCount++);
            else
                emit axisAdj('Z', setTo/10, invZ, absoluteAfterAxisAdj, sliderZCount++);
        }
    }


    //ui->resultingZJogSliderPosition->setText("0");
}

void MainWindow::setQueuedCommands(int commandCount, bool running)
{
    if (running)
    {
        switch (queuedCommandState)
        {
            case QCS_OK:
                if (lastQueueCount == 0)
                {
                    if (queuedCommandsEmptyTimer.elapsed() > 2000)
                    {
                        if (!queuedCommandsStarved)
                        {
                            //diag("DG >>>>Switch to red\n");

                            queuedCommandsStarved = true;

                            ui->labelQueuedCommands->setStyleSheet("QLabel { background-color : rgb(255,0,0); color : white; }");

                            queuedCommandState = QCS_WAITING_FOR_ITEMS;
                        }
                    }
                }
                break;
             case QCS_WAITING_FOR_ITEMS:
                if (commandCount > 0)
                {
                    if (queuedCommandsEmptyTimer.elapsed() > 3000)
                    {
                        if (queuedCommandsStarved)
                        {
                            //diag("DG >>>>Switch to green\n");

                            queuedCommandsStarved = false;

                            ui->labelQueuedCommands->setStyleSheet("");
                        }

                        queuedCommandsEmptyTimer.restart();

                        queuedCommandState = QCS_OK;
                    }
                }
                break;
        }

        if (queuedCommandsRefreshTimer.elapsed() > 1000)
        {
            ui->progressQueuedCommands->setValue(commandCount);
            queuedCommandsRefreshTimer.restart();
        }
    }
    else
    {
        queuedCommandsEmptyTimer.restart();
        queuedCommandState = QCS_OK;
        ui->progressQueuedCommands->setValue(commandCount);
    }

    lastQueueCount = commandCount;
}

void MainWindow::setLcdState(bool valid)
{
    if (lastLcdStateValid != valid)
    {
        QString ss = "";
        if (!valid)
        {
            ss = "QLCDNumber { background-color: #F8F8F8; color: #F0F0F0; }";
        }
        ui->lcdWorkNumberX->setStyleSheet(ss);
        ui->lcdMachNumberX->setStyleSheet(ss);
        ui->lcdWorkNumberY->setStyleSheet(ss);
        ui->lcdMachNumberY->setStyleSheet(ss);
        ui->lcdWorkNumberZ->setStyleSheet(ss);
        ui->lcdMachNumberZ->setStyleSheet(ss);
        ui->lcdWorkNumberFourth->setStyleSheet(ss);
        ui->lcdMachNumberFourth->setStyleSheet(ss);

        lastLcdStateValid = valid;
    }
}

void MainWindow::refreshPosition()
{
    gotoXYZFourth(REQUEST_CURRENT_POS);
}

void MainWindow::comboStepChanged(const QString& text)
{
    jogStepStr = text;
    jogStep = jogStepStr.toFloat();
}
