/****************************************************************
 * mainwindow.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include <QDataStream>
#include "mainwindow.h"
#include "version.h"
#include "ui_mainwindow.h"

extern Log4Qt::FileAppender *p_fappender;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), opt(this),
    open_button_text(tr("Open")),
    close_button_text(tr("Close / Reset")),
    absoluteAfterAxisAdj(false),
    checkLogWrite(false),
    sliderPressed(false),
    sliderTo(0.0),
    sliderZCount(0),
/// T4
 //   scrollRequireMove(true), scrollPressed(false),
    queuedCommandsStarved(false), lastQueueCount(0), queuedCommandState(QCS_OK),
    lastLcdStateValid(true),
    activeLine(0), cmdMan(false)
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
/// T3
    checkState = ui->btnCheck->isChecked() ;
/// T4 to display the comma correctly : before read 'sliderStep->value'
    connect(ui->sliderStep, SIGNAL(valueChanged(int)), this, SLOT(stepChanged(int)) );
    // 'Options'
    opt.init();

    readSettings();
    

    info(qPrintable(tr("%s has started")), GRBL_CONTROLLER_NAME_AND_VERSION);

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
        ui->HomeFourthBtn->hide();
        ui->lcdWorkNumberFourth->hide();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lcdMachNumberFourth->hide();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lblFourth->hide();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
/// T4
        ui->unitFourth->hide();
        ui->unitFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
    }
///************************ connect ***********************************
///T4
    connect(ui->btnPause,SIGNAL(toggled(bool)),this,SLOT(pauseSend(bool)));
    // GRbl command
    connect(ui->btnHelp,SIGNAL(clicked()),this,SLOT(grblHelp()));
    connect(ui->btnGrblSettings,SIGNAL(clicked()),this,SLOT(grblSettings()));
    connect(ui->btnParameters, SIGNAL(clicked()),this, SLOT(grblParameters()));
    connect(ui->btnParserState, SIGNAL(clicked()),this, SLOT(grblParserState()));
    connect(ui->btnBuildInfo, SIGNAL(clicked()),this, SLOT(grblBuildInfo()));
    connect(ui->btnStartupBlocks, SIGNAL(clicked()),this, SLOT(grblStartupBlocks()));
    connect(ui->btnCheck,SIGNAL(toggled(bool)),this,SLOT(grblCheck(bool) ));
    connect(ui->btnUnlockGrbl,SIGNAL(clicked()),this,SLOT(grblUnlock()));
    connect(ui->btnHomingCycle, SIGNAL(clicked()),this,SLOT(grblHomingCycle()));
  //  connect(ui->btnCycleStart, SIGNAL(clicked()),this, SLOT(grblCycleStart()));
  //  connect(ui->btnFeedHold, SIGNAL(clicked()),this, SLOT(grblFeedHold()));
    connect(ui->btnStatus, SIGNAL(clicked()),this,SLOT(grblStatus()));
    connect(ui->btnResetGrbl,SIGNAL(clicked()),this,SLOT(grblReset()));
    /// to gcode
  //  connect(this, SIGNAL(sendGrblPause(bool)), &gcode, SLOT(sendGrblPause(bool)));
    connect(this, SIGNAL(sendGrblHelp()), &gcode, SLOT(sendGrblHelp()));

    connect(this, SIGNAL(sendGrblParameters()), &gcode, SLOT(sendGrblParameters()));
    connect(this, SIGNAL(sendGrblParserState()), &gcode, SLOT(sendGrblParserState()));
    connect(this, SIGNAL(sendGrblBuildInfo()), &gcode, SLOT(sendGrblBuildInfo()));
    connect(this, SIGNAL(sendGrblStartupBlocks()), &gcode, SLOT(sendGrblStartupBlocks()));
   // connect(this, SIGNAL(sendGrblCheck(bool)), &gcode, SLOT(grblCheck(bool)));
    connect(this, SIGNAL(sendGrblCheck(bool)), &gcode, SLOT(sendGrblCheck(bool)));
    connect(this, SIGNAL(sendGrblUnlock()), &gcode, SLOT(sendGrblUnlock()));
    connect(this, SIGNAL(sendGrblHomingCycle()), &gcode, SLOT(sendGrblHomingCycle()));
    connect(this, SIGNAL(sendGrblCycleStart()), &gcode, SLOT(sendGrblCycleStart()));
    connect(this, SIGNAL(sendGrblFeedHold()), &gcode, SLOT(sendGrblFeedHold()));
    connect(this, SIGNAL(sendGrblStatus()), &gcode, SLOT(sendGrblStatus()));
    connect(this, SIGNAL(sendGrblReset()), &gcode, SLOT(sendGrblReset()));
    //buttons
    connect(ui->btnOpenPort,SIGNAL(clicked()),this,SLOT(openPort()));
    connect(ui->DecXBtn,SIGNAL(clicked()),this,SLOT(decX()));
    connect(ui->DecYBtn,SIGNAL(clicked()),this,SLOT(decY()));
    connect(ui->DecZBtn,SIGNAL(clicked()),this,SLOT(decZ()));
    connect(ui->IncXBtn,SIGNAL(clicked()),this,SLOT(incX()));
    connect(ui->IncYBtn,SIGNAL(clicked()),this,SLOT(incY()));
    connect(ui->IncZBtn,SIGNAL(clicked()),this,SLOT(incZ()));
    connect(ui->DecFourthBtn,SIGNAL(clicked()),this,SLOT(decFourth()));
    connect(ui->IncFourthBtn,SIGNAL(clicked()),this,SLOT(incFourth()));
/// T4
    connect(ui->HomeXBtn,SIGNAL(clicked()),this,SLOT(homeX()));
    connect(ui->HomeYBtn,SIGNAL(clicked()),this,SLOT(homeY()));
    connect(ui->HomeZBtn,SIGNAL(clicked()),this,SLOT(homeZ()));
    connect(ui->HomeFourthBtn,SIGNAL(clicked()),this,SLOT(homeFourth()));
    connect(this, SIGNAL(goToHomeAxis(char)), &gcode, SLOT(goToHomeAxis(char) ));
    connect(&gcode, SIGNAL(endHomeAxis()), this, SLOT(endHomeAxis() ));

    connect(ui->btnSetHome,SIGNAL(clicked()),this,SLOT(setHome()));
    connect(ui->comboCommand->lineEdit(), SIGNAL(editingFinished()),this, SLOT(gotoXYZFourth()));
/// T3
    connect(ui->Begin,SIGNAL(clicked()),this,SLOT(begin()));
    connect(ui->openFile,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(ui->Stop,SIGNAL(clicked()),this,SLOT(stop()));

/// T4
    connect(ui->spindleButton,SIGNAL(toggled(bool)),this,SLOT(toggleSpindle(bool)));
    connect(ui->chkRestoreAbsolute,SIGNAL(toggled(bool)),this,SLOT(toggleRestoreAbsolute()));
    connect(ui->actionOptions,SIGNAL(triggered()),this,SLOT(getOptions()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));

    connect(ui->btnGoHomeSafe,SIGNAL(clicked()),this,SLOT(goHomeSafe()));
    connect(ui->verticalSliderZJog,SIGNAL(valueChanged(int)),this,SLOT(zJogSliderDisplay(int)));
    connect(ui->verticalSliderZJog,SIGNAL(sliderPressed()),this,SLOT(zJogSliderPressed()));
    connect(ui->verticalSliderZJog,SIGNAL(sliderReleased()),this,SLOT(zJogSliderReleased()));
  //  connect(ui->pushButtonRefreshPos,SIGNAL(clicked()),this,SLOT(refreshPosition()));

/// T3
    connect(this, SIGNAL(sendFile(QString, bool)), &gcode, SLOT(sendFile(QString, bool)));
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

/// T3
    connect(this, SIGNAL(goToHome()), &gcode, SLOT(goToHome()));
    connect(this, SIGNAL(setItems(QList<PosItem>)), ui->wgtVisualizer, SLOT(setItems(QList<PosItem>)));
/// T4
    connect(this, SIGNAL(setItems(QList<PosItem>)), ui->visu3D, SLOT(setItems(QList<PosItem>)));
    connect(ui->View3DButton, SIGNAL(clicked()), ui->visu3D, SLOT(set3DView()) ) ;
    connect(ui->FrontViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setFrontView()) ) ;
    connect(ui->BackViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setBackView()) ) ;
    connect(ui->LeftViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setLeftView()) ) ;
    connect(ui->RightViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setRightView()) ) ;
    connect(ui->TopViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setTopView()) ) ;
    connect(ui->BottomViewButton, SIGNAL(clicked()), ui->visu3D, SLOT(setBottomView()) ) ;
    connect(ui->VectorUpButton, SIGNAL(clicked()), ui->visu3D, SLOT(setVectorUp()) ) ;
    connect(ui->Help3DButton, SIGNAL(clicked()), ui->visu3D, SLOT(Help3D()) ) ;

    connect(ui->BBcheckBox, SIGNAL(clicked(bool)), ui->visu3D, SLOT(setBbox(bool)) ) ;
    connect(ui->G0checkBox, SIGNAL(clicked(bool)), ui->visu3D, SLOT(setG0(bool)) ) ;
/// ==> undetected by gcc 4.7.1 error                                           --->
   // connect(ui->BBcheckBox, SIGNAL(clicked(bool)), ui->visu3D, SLOT(setBbox(bool)() ) ) ;

    connect(&gcode, SIGNAL(sendMsgSatusBar(QString)),this,SLOT(receiveMsgSatusBar(QString)));
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
/// T4  3D animator
    connect(ui->visu3D, SIGNAL(updateLCD(QVector3D)), this, SLOT(updateLCD(QVector3D)));
    connect(&gcode, SIGNAL(setLastState(QString)), ui->outputLastState, SLOT(setText(QString)));
    connect(&gcode, SIGNAL(setUnitMmAll(bool)), this, SLOT(setUnitMmAll(bool)));

    /// 2D
    connect(&gcode, SIGNAL(setLivePoint(double, double, bool, bool)), ui->wgtVisualizer, SLOT(setLivePoint(double, double, bool, bool)));
    connect(&gcode, SIGNAL(setVisualLivenessCurrPos(bool)), ui->wgtVisualizer, SLOT(setVisualLivenessCurrPos(bool)));
    connect(&gcode, SIGNAL(setVisCurrLine(int)), ui->wgtVisualizer, SLOT(setVisCurrLine(int)));
/// T4  for visu3D
    connect(&gcode, SIGNAL(setLivePoint(QVector3D)), ui->visu3D, SLOT(setLivePoint(QVector3D)));
  //  connect(this, SIGNAL(setLiveRelPoint(QVector3D)), ui->visu3D, SLOT(setLiveRelPoint(QVector3D)));
    connect(this, SIGNAL(setLivePoint(QVector3D, bool)), ui->visu3D, SLOT(setLivePoint(QVector3D, bool)));

    connect(&gcode, SIGNAL(setLcdState(bool)), this, SLOT(setLcdState(bool)));
    connect(&runtimeTimer, SIGNAL(setRuntime(QString)), ui->outputRuntime, SLOT(setText(QString)));
/// T2
	connect(&gcode, SIGNAL(setVersionGrbl(QString)), ui->GrblVersion, SLOT(setText(QString)));
/// T3
    connect(&gcode, SIGNAL(setLinesFile(QString, bool)), this, SLOT(setLinesFile(QString, bool)));
/// T4 for visuGcode
    connect(ui->visuGcode, SIGNAL(cursorPositionChanged() ), this, SLOT(on_cursorVisuGcode()) ) ;
    connect(this, SIGNAL(setLineCode(QString) ), ui->lineCode, SLOT(setText(QString)) ) ;
    connect(this, SIGNAL(setNumLine(QString) ), ui->visu3D, SLOT(setNumLine(QString)) ) ;
    connect(&gcode, SIGNAL(setNumLine(QString) ), ui->visu3D, SLOT(setNumLine(QString)) ) ;
    connect(ui->visu3D, SIGNAL(setLineNum(QString) ), ui->lineCode, SLOT(setText(QString)) ) ;
    connect(this, SIGNAL(setTotalNumLine(QString) ), ui->visu3D, SLOT(setTotalNumLine(QString)) ) ;
    connect(this, SIGNAL(setFeedRateToLine(QList<double>)), ui->visu3D, SLOT(setFeedRateToLine(QList<double>))) ;
    connect(this, SIGNAL(setSpeedSpindleToLine(QList<double>)), ui->visu3D, SLOT(setSpeedSpindleToLine(QList<double>))) ;
    connect(ui->visu3D, SIGNAL(setActiveLineVisuGcode(int, bool)), this, SLOT(setActiveLineVisuGcode(int, bool)) );
/// T4 for animator
    connect(ui->visualButton, SIGNAL(toggled(bool) ), this, SLOT(toVisual(bool)) ) ;
    connect(this, SIGNAL(setVisual(bool) ), ui->visu3D, SLOT(setVisual(bool)) ) ;
    connect(ui->pauseButton, SIGNAL(toggled(bool) ), this, SLOT(toPause(bool)) ) ;
    connect(this, SIGNAL(setPause(bool) ), ui->visu3D, SLOT(setPause(bool)) ) ;
    connect(ui->prevButton, SIGNAL(clicked() ), ui->visu3D, SLOT(setPrev()) ) ;
    connect(ui->nextButton, SIGNAL(clicked() ), ui->visu3D, SLOT(setNext()) ) ;
    connect(this, SIGNAL(runCode(bool, int) ), ui->visu3D, SLOT(runCode(bool, int)) ) ;
    connect(this, SIGNAL(setPosReqKind(int)), &gcode, SLOT(setPosReqKind(int)) );

    connect(ui->dialPeriodRepeat, SIGNAL(valueChanged(int)),ui->visu3D,SLOT(setPeriod(int)));
    connect(ui->dialPeriodRepeat, SIGNAL(valueChanged(int)),ui->lcdPeriodAnim, SLOT(display(int)));

    connect(ui->visu3D, SIGNAL(setPauseVisual(bool)), ui->pauseButton, SLOT(setChecked(bool)) );

    connect(ui->visu3D, SIGNAL(setFeedRateGcode(double)), ui->lcdFeedRateGcode, SLOT(display(double)) );
    connect(ui->visu3D, SIGNAL(setSpeedSpindleGcode(double)), ui->lcdSpeedSpindleGcode, SLOT(display(double)) );

    connect(ui->visu3D, SIGNAL(setSegments(int)), ui->lcdSegments, SLOT(display(int)) );
    connect (ui->doubleSpinBoxTol, SIGNAL(valueChanged(double)), ui->visu3D, SLOT(setTolerance(double) ));

    connect(ui->btnClearStatusList, SIGNAL(clicked() ), this, SLOT(toClearSatusList()) ) ;
    connect(ui->btnPrintStatusList, SIGNAL(clicked() ), this, SLOT(toPrintStatusList()) ) ;
    connect(ui->btnPrintVisual, SIGNAL(clicked() ), this, SLOT(toPrintVisual()) ) ;

/// end connect
    /// start threads
    runtimeTimerThread.start();
    gcodeThread.start();

    queuedCommandsEmptyTimer.start();
    queuedCommandsRefreshTimer.start();

    // Cool utility class off Google code that enumerates COM ports in platform-independent manner
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    int portIndex = -1;
    for (int i = 0; i < ports.size(); i++)
    {
        ui->cmbPort->addItem(qPrintable(ports.at(i).portName));

        if (ports.at(i).portName == lastOpenPort)
            portIndex = i;

//diag("port name: %s\n", qPrintable(ports.at(i).portName));
//diag("friendly name: %s\n", qPrintable(ports.at(i).friendName));
//diag("physical name: %s\n", qPrintable(ports.at(i).physName)));
//diag("enumerator name: %s\n", qPrintable(ports.at(i).enumName)));
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
        ui->cmbPort->addItem(qPrintable(lastOpenPort));
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
/// T4
    // manual controls
    enableManualControl(false);

    if (!controlParams.useFourAxis)
    {
        ui->lcdWorkNumberFourth->setEnabled(false);;
        ui->lcdMachNumberFourth->setEnabled(false);;
        ui->IncFourthBtn->setEnabled(false);
        ui->DecFourthBtn->setEnabled(false);
        ui->HomeFourthBtn->setEnabled(false);
    }
    ui->groupBoxSendFile->setEnabled(true);
    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
/// T2
    ui->labelLines->setEnabled(false);
    ui->outputLines->setEnabled(false);
/// T3
    {
    ui->Begin->setEnabled(false);
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    }
/// T4
    // Grbl commands
    enableButtonGrblControls(false);

    styleSheet = ui->btnOpenPort->styleSheet();
    ui->statusList->setEnabled(true);
    ui->openFile->setEnabled(true);
/// T4 animator
    ui->tabGcode->setEnabled(false);

    this->setWindowTitle(GRBL_CONTROLLER_NAME_AND_VERSION VERSION_BUILD);
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

/// --> T4  associate to 'QToolButton toolButton'
    /// actions
    QAction * noToolAction = new QAction(tr("No tool"), this);
        connect(noToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(noTool()));
    QAction * miniToolAction = new QAction(tr("Mini 1 mm"), this);
        connect(miniToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(miniTool()));
    QAction * hemiToolAction = new QAction(tr("Hemi 3 mm"), this);
        connect(hemiToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(hemiTool()));
    QAction * rightToolAction = new QAction(tr("Right 3 mm"), this);
        connect(rightToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(rightTool()));
    QAction * sharpToolAction = new QAction(tr("Sharp 3 mm"), this);
        connect(sharpToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(sharpTool()) );
    QAction * shortToolAction = new QAction(tr("Short 3 mm"), this);
        connect(shortToolAction, SIGNAL(triggered()), ui->visu3D, SLOT(shortTool()) );
    /// menus

    QMenu * menuTool = new QMenu(this);
        menuTool->addAction(noToolAction);
        menuTool->addAction(miniToolAction);
        menuTool->addAction(hemiToolAction);
        menuTool->addAction(rightToolAction);
        menuTool->addAction(sharpToolAction);
        menuTool->addAction(shortToolAction);
    /// associate 'menuTool' and 'toolButton'
    ui->toolButton->setMenu(menuTool);
/// T4
    // period animation mS
    ui->dialPeriodRepeat->setValue(100);

/// <-- T4  call 'setUnitMmAll(..)'
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

    info(qPrintable(tr("%s has stopped")), GRBL_CONTROLLER_NAME_AND_VERSION);

    SLEEP(300);

    emit shutdown();

    event->accept();
}

void MainWindow::begin()
{
    // TODO : verify 'ui->filePath->text()'
    // ...
    if (!checkState)
        setLcdState(controlParams.usePositionRequest);
    else
        setLcdState(false);

    // 2D
    ui->wgtVisualizer->setEnabled(!checkState);
    ui->wgtVisualizer->setAutoFillBackground(!checkState);

/// T4  3D
    /// -> ui->visu3D::runCode(true, posRegKind);
    runFile = true;
    cmdMan = false;
    emit runCode(runFile, posReqKind);

    // -> 'gcode::setPosReqKind(posRegKind)'
    emit setPosReqKind(posReqKind);

    ui->visualButton->setChecked(false);
    ui->pauseButton->setChecked(true);
    // invalid manual controls
    enableManualControl(false);
    if (!checkState)
    {
        ui->tabAxisVisualizer->setTabEnabled(TAB_VISU3D_INDEX, true);
        if (ui->tabAxisVisualizer->currentIndex() != TAB_VISU3D_INDEX)
        {
             emit ui->tabAxisVisualizer->setCurrentIndex(TAB_VISU3D_INDEX);
        }
    }
    if (ui->tabVisu->currentIndex() != TAB_CONSOLE_INDEX)
    {
         emit ui->tabVisu->setCurrentIndex(TAB_CONSOLE_INDEX);
    }

    //receiveList("Starting File Send.");
    resetProgress();

    int ret = QMessageBox::No;
    if (!checkState) {
        if((ui->lcdWorkNumberX->value()!=0)||(ui->lcdWorkNumberY->value()!=0)||(ui->lcdWorkNumberZ->value()!=0)
            || (ui->lcdWorkNumberFourth->value()!=0))
        {
            QMessageBox msgBox;
            msgBox.setText(tr("Do you want to zero the displayed position before proceeding?"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Yes);
            ret = msgBox.exec();
            if(ret == QMessageBox::Yes)
                setHome();
        }
    }
    if(ret!=QMessageBox::Cancel)
    {
        ui->btnClearStatusList->setEnabled(false);
        ui->btnPrintStatusList->setEnabled(false);
        ui->btnPrintVisual->setEnabled(false) ;

        ui->comboCommand->setEnabled(false);
        ui->labelCommand->setEnabled(false);
/// T3
        ui->openFile->setEnabled(false);
        {
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(true);
        ui->btnPause->setEnabled(true);
        ui->progressFileSend->setEnabled(true);
        ui->progressQueuedCommands->setEnabled(true);
        ui->labelFileSendProgress->setEnabled(true);
        ui->labelQueuedCommands->setEnabled(true);
        ui->outputRuntime->setEnabled(true);
        ui->labelRuntime->setEnabled(true);
        }

/// T4
        // Grbl commands
        enableButtonGrblControls(false);
        // commands 'tabVisu'
        enableTabVisuControls(false);

        emit sendFile(ui->filePath->text(), checkState);
    }
}

void MainWindow::stop()
{
    setLcdState(controlParams.usePositionRequest);
    ui->wgtVisualizer->setEnabled(true);
    ui->wgtVisualizer->setAutoFillBackground(true);
/// T4
    runFile = false;
    emit runCode(runFile, posReqKind);
    ui->visu3D->setEnabled(true);
    ui->tabGcode->setEnabled(true);
    ui->tabVisu->setTabEnabled(TAB_VISUGCODE_INDEX, true);

    gcode.setAbort();
/// T4
    if (!ui->btnPause->isChecked())
        ui->btnPause->setChecked(true);

    // Reenable a bunch of UI
/// T3
    ui->Begin->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->openFile->setEnabled(true);

    ui->btnClearStatusList->setEnabled(true);
    ui->btnPrintStatusList->setEnabled(true);
    ui->btnPrintVisual->setEnabled(true) ;
/// T4
    // valid commands 'tabVisu'
    enableTabVisuControls(true);

    // valid manual controls
    enableManualControl(true);

    // Grbl commands
    enableButtonGrblControls(true);
}
//------------------------------------------
/// T4    suspend/resume 'gcode::sendFile(...)'
// calls : 'ui->btnPause'
void MainWindow::pauseSend(bool valid)
{
    // to gcode
    gcode.setPause(!valid);

    QPalette palette;
    if (ui->btnPause->isChecked())  {
        ui->btnPause->setText(tr("Pause")) ;
        palette.setColor(QPalette::Button,Qt::gray) ;
    }
    else {
        ui->btnPause->setText(tr("Resume")) ;
        palette.setColor(QPalette::Button,Qt::yellow) ;
    }
    // color 'pauseButton'
    ui->btnPause->setPalette(palette);
}

void MainWindow::grblHelp()
{
    emit sendGrblHelp();
}
void MainWindow::grblParameters()
{
    emit sendGrblParameters();
}
void MainWindow::grblParserState()
{
    emit sendGrblParserState();
}

void MainWindow::grblBuildInfo()
{
    emit sendGrblBuildInfo();
}
void MainWindow::grblStartupBlocks()
{
    emit sendGrblStartupBlocks();
}

// calls : 'ui->btnCheck::toggled(valid)'
void  MainWindow::grblCheck(bool valid)
{
/// TODO : fix bug with command '$C'
    checkState = ui->btnCheck->isChecked();
    if (checkState)
    {
        QString txt(tr("During the mode 'Check 'does not use the command '$C' please"));
        receiveMsgSatusBar(txt);
        info(qPrintable(txt));
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(txt);
        msgBox.exec();

        addToStatusList(true, txt);

        ui->btnCheck->setText(tr("No check")) ;
    }
    else  {
        ui->btnCheck->setText(tr("Check")) ;
    }

    ui->tabAxisVisualizer->setEnabled(valid);

    enableButtonGrblControls(!valid);
    if(valid) {
        ui->btnCheck->setEnabled(true);
        ui->btnStatus->setEnabled(true);
        ui->btnResetGrbl->setEnabled(true);
        ui->btnUnlockGrbl->setEnabled(true);
    }
     // (in)valid manual controls
    enableManualControl(!valid);
    ui->tabVisu->setTabEnabled(TAB_VISUGCODE_INDEX, !valid);

    /// send '$C' to Grbl
    emit sendGrblCheck(checkState) ;
}

void MainWindow::grblUnlock()
{
    emit sendGrblUnlock();
}
void MainWindow::grblHomingCycle()
{
    // user message
    QString msg(tr("With 'Grbl Settings' you must validate the homing cycle" ));
    info(qPrintable(msg));
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(msg);
    msgBox.exec();

    addToStatusList(true, msg);

    emit sendGrblHomingCycle();
}
///---- not used
void MainWindow::grblCycleStart()
{
    emit sendGrblCycleStart() ;
}
void MainWindow::grblFeedHold()
{
    emit sendGrblFeedHold() ;
}
//--
void MainWindow::grblStatus()
{
    emit sendGrblStatus();
}
void MainWindow::grblReset()
{
    gcode.setAbort();
    gcode.setReset();
    emit sendGrblReset();
}
//-------------------------------------------

void MainWindow::goHomeSafe()
{
    /// tool position  !!
    cmdMan = true;
    emit goToHome();
}

// slot called from GCode class to update our state
void MainWindow::stopSending()
{
    ui->tabAxisVisualizer->setEnabled(true);
    // valid manual controls
    enableManualControl(true);
    if (!ui->btnPause->isChecked())
        ui->btnPause->setChecked(true);
    // lcd
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->HomeFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);
/// T3
    {
    ui->Begin->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    }
    ui->btnOpenPort->setEnabled(true);
/// T4
    // Grbl commands
    enableButtonGrblControls(true);

    ui->openFile->setEnabled(true);
/// T4
    // commands 'tabVisu'
    enableTabVisuControls(true);
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
   // sendSetHome();  // ?
    cmdMan = true;
    emit sendSetHome();
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
/// T2
        ui->labelLines->setEnabled(false);
        ui->outputLines->setEnabled(false);

        ui->btnOpenPort->setEnabled(false);
        ui->comboBoxBaudRate->setEnabled(false);

        ui->btnClearStatusList->setEnabled(true);
        ui->btnPrintStatusList->setEnabled(true);
/// T4
        if (ui->tabVisu->currentIndex() != TAB_CONSOLE_INDEX)
        {
            emit ui->tabVisu->setCurrentIndex(TAB_CONSOLE_INDEX);
        }

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
/// T2
        ui->labelLines->setEnabled(false);
        ui->outputLines->setEnabled(false);
/// T3
         ui->openFile->setEnabled(true);
        {
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->btnPause->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
        }
/// T4
        ui->tabAxisVisualizer->setEnabled(ui->visualButton->isChecked());
        ui->comboCommand->setEnabled(false);
        ui->labelCommand->setEnabled(false);

        enableButtonGrblControls(false) ;
        // invalid manual controls
        enableManualControl(false);
/// T2
		ui->GrblVersion->setText(tr("none"));
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

    ui->btnClearStatusList->setEnabled(false);
    ui->btnPrintStatusList->setEnabled(false);

/// T4
     // invalid manual controls
    enableManualControl(false);

    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
    ui->labelLines->setEnabled(false);
    ui->outputLines->setEnabled(false);

    ui->openFile->setEnabled(true);

    {
    ui->Begin->setEnabled(false);
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    }
/// T4
    // Grbl commands
    enableButtonGrblControls(false);

    styleSheet = ui->btnOpenPort->styleSheet();
    ui->statusList->setEnabled(true);
    ui->tabGcode->setEnabled(true);
///<--
    ui->comboCommand->setEnabled(false);
    ui->labelCommand->setEnabled(false);
    ui->cmbPort->setEnabled(true);
    ui->comboBoxBaudRate->setEnabled(true);
    ui->btnOpenPort->setEnabled(true);
    ui->btnOpenPort->setText(open_button_text);
    ui->btnOpenPort->setStyleSheet(styleSheet);
/// T4
    // Grbl commands
    enableButtonGrblControls(false);

    if (reopen)
    {
        receiveList(tr("Resetting port to restart controller"));
        openPortCtl(false);
    }
/// T4
    openState =  false;
}

// slot that tells us the gcode thread successfully opened the port
void MainWindow::portIsOpen(bool sendCode)
{
    // Comm port successfully opened
    if (sendCode)
        sendGcode("");
    openState = sendCode;
}
// called by 'GCode::axisAdj(...)'
void MainWindow::adjustedAxis()
{
    cmdMan = false;
    ui->tabAxisVisualizer->setEnabled(true);
/// T4
    // valid manual controls
    enableManualControl(true);

    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);

    if (ui->filePath->text().length() > 0)
    {
       ui->Begin->setEnabled(true);
    }
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);

    ui->btnOpenPort->setEnabled(true);
    ui->openFile->setEnabled(true);
/// T4
    // Grbl commands
    enableButtonGrblControls(true);
}

void MainWindow::enableAllButtons(bool v)
{
    ui->comboCommand->setEnabled(v);
    ui->labelCommand->setEnabled(v);
/// T2
    ui->labelLines->setEnabled(v);
    ui->outputLines->setEnabled(v);
/// T3
    ui->openFile->setEnabled(v);
    {  // enableBlockFile
    ui->Begin->setEnabled(v);
    ui->Stop->setEnabled(v);
    ui->btnPause->setEnabled(v);
    ui->progressFileSend->setEnabled(v);
    ui->progressQueuedCommands->setEnabled(v);
    ui->labelFileSendProgress->setEnabled(v);
    ui->labelQueuedCommands->setEnabled(v);
    ui->outputRuntime->setEnabled(v);
    ui->labelRuntime->setEnabled(v);
    }
/// T4
    // Grbl commands
    enableButtonGrblControls(v);
/// T4
     // manual controls
    enableManualControl(v);
}
// called by 'GCode::waitForStartupBanner( ...)'
void MainWindow::enableGrblDialogButton()
{
    ui->openFile->setEnabled(true);
    ui->btnOpenPort->setEnabled(true);
    ui->btnOpenPort->setText(close_button_text);
    ui->btnOpenPort->setStyleSheet("* { background-color: rgb(255,125,100) }");
    ui->cmbPort->setEnabled(false);
    ui->comboBoxBaudRate->setEnabled(false);

    ui->tabAxisVisualizer->setEnabled(true);
    // valid manual controls
    enableManualControl(true);
    {  // blockCoordinate
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->HomeFourthBtn->setEnabled(controlParams.useFourAxis);
    }
    ui->groupBoxSendFile->setEnabled(true);

    ui->comboCommand->setEnabled(true);
    ui->labelCommand->setEnabled(true);

    ui->btnSetHome->setEnabled(true);
///  T4
    // Grbl commands
    enableButtonGrblControls(true);

    if (ui->filePath->text().length() > 0)
    {
/// T2
        ui->labelLines->setEnabled(true);
        ui->outputLines->setEnabled(true);
/// T3
        if (!ui->visualButton->isChecked()) {
            ui->btnCheck->setEnabled(true);
            ui->Begin->setEnabled(true);
        }
         ui->Stop->setEnabled(false);
         ui->btnPause->setEnabled(false);

        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
    }
    else
    {
/// T2
        ui->labelLines->setEnabled(false);
        ui->outputLines->setEnabled(false);
/// T3
        {
        ui->Begin->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->btnPause->setEnabled(false);
        ui->progressFileSend->setEnabled(false);
        ui->progressQueuedCommands->setEnabled(false);
        ui->labelFileSendProgress->setEnabled(false);
        ui->labelQueuedCommands->setEnabled(false);
        ui->outputRuntime->setEnabled(false);
        ui->labelRuntime->setEnabled(false);
        }
    }
}

void MainWindow::incX()
{
    enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit axisAdj('X', jogStep, invX, absoluteAfterAxisAdj, 0);
}

void MainWindow::incY()
{
    enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit axisAdj('Y', jogStep, invY, absoluteAfterAxisAdj, 0);
}

void MainWindow::incZ()
{
    enableAllButtons(false);
/// T4
    cmdMan = true;
    ui->lcdFeedRateGcode->display(controlParams.zJogRate);
    emit axisAdj('Z', jogStep, invZ, absoluteAfterAxisAdj, sliderZCount++);
}

void MainWindow::decX()
{
    enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit axisAdj('X', -jogStep, invX, absoluteAfterAxisAdj, 0);
}

void MainWindow::decY()
{
    enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit axisAdj('Y', -jogStep, invY, absoluteAfterAxisAdj, 0);
}

void MainWindow::decZ()
{
    enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.zJogRate);
    cmdMan = true;
    emit axisAdj('Z', -jogStep, invZ, absoluteAfterAxisAdj, sliderZCount++);
}

void MainWindow::decFourth()
{
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
	emit axisAdj(controlParams.fourthAxisName, -jogStep, invFourth, absoluteAfterAxisAdj, 0);
}
void MainWindow::incFourth()
{
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit axisAdj(controlParams.fourthAxisName, jogStep, invFourth, absoluteAfterAxisAdj, 0);
}

// ui->HomeXBtn->clicked() -> homeX()
void MainWindow::homeX()
{
    if (ui->lcdWorkNumberX->value()==0)
        return;
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit goToHomeAxis('X');
}
void MainWindow::homeY()
{
    if (ui->lcdWorkNumberY->value()==0)
        return;
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit goToHomeAxis('Y');
}

void MainWindow::homeZ()
{
    if (ui->lcdWorkNumberZ->value()==0)
        return;
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.zJogRate);
    cmdMan = true;
    emit goToHomeAxis('Z');
}

void MainWindow::homeFourth()
{
    if (ui->lcdWorkNumberFourth->value()==0)
        return;
	enableAllButtons(false);
/// T4
    ui->lcdFeedRateGcode->display(controlParams.xyRateAmount);
    cmdMan = true;
    emit goToHomeAxis(controlParams.fourthAxisName);
}

// calls : 'GCode::goToHomeAxis()':1,
void MainWindow::endHomeAxis()
{
    cmdMan = false;
    enableManualControl(true);
    enableButtonGrblControls(true);
    ui->comboCommand->setEnabled(true);
    ui->openFile->setEnabled(true);
    if (ui->filePath->text().length() > 0)
        ui->Begin->setEnabled(true);
    /// others  ... TODO
}

void MainWindow::getOptions()
{
/// T4
   // Options opt(this);
    opt.move(geometry().x(), geometry().y());
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
/// T4
    else
        return ;

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
/// T3   // cpmport open
    if (ui->btnOpenPort->text() == close_button_text)
    {
        ui->Begin->setEnabled(true);
    }
    else  // close
    {
        ui->Begin->setEnabled(false);
    }

    {
    ui->Stop->setEnabled(false);
    ui->btnPause->setEnabled(false);
    ui->progressFileSend->setEnabled(false);
    ui->progressQueuedCommands->setEnabled(false);
    ui->labelFileSendProgress->setEnabled(false);
    ui->labelQueuedCommands->setEnabled(false);
    ui->outputRuntime->setEnabled(false);
    ui->labelRuntime->setEnabled(false);
    }

    if (ui->filePath->text().length() > 0)
    {
        ui->labelLines->setEnabled(true);
        ui->outputLines->setEnabled(true);
        ui->btnPrintVisual->setEnabled(true) ;
/// T4    visu3D  and visuGcode
        if (ui->tabAxisVisualizer->currentIndex() != TAB_VISU3D_INDEX)
        {
             emit ui->tabAxisVisualizer->setCurrentIndex(TAB_VISU3D_INDEX);
        }
        if (ui->tabVisu->currentIndex() != TAB_VISUGCODE_INDEX)
        {
             emit ui->tabVisu->setCurrentIndex(TAB_VISUGCODE_INDEX);
        }
        ui->tabGcode->setEnabled(true);
    // read in the file to process it
        preProcessFile(ui->filePath->text());
    }
    else
    {
        ui->labelLines->setEnabled(false);
        ui->outputLines->setEnabled(false);
    }
}

void MainWindow::preProcessFile(QString filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream code(&file);
        posList.clear();
/// T4
        ui->visuGcode->clear() ;
        int plane = NO_PLANE;
        double x = 0, y = 0, z = 0;
        double i = 0,  j = 0, k = 0;
        QVector3D xyz, ijk;
        int p =0;    // arc revolutions
        int g;
        bool helix = false;
    // feedrate 'Fxxxx'
        double fr, prevfr = 0.0;
        QList<double> feedRateToLine;
        feedRateToLine.append(prevfr);// case 0
    // Spindle Speed   Sxxxxx
        double ss, prevss = 0.0;
        QList<double> speedSpindleToLine;
        speedSpindleToLine.append(prevss); // case 0

/// T4 animator
        QString codeText;
        QString line;

        bool arc = false;
        bool cw = false;
        bool mm = true;
        int index = 0;
       // bool zeroInsert = false;  // ???
        bool zeroInsert = true;
        QString strline;
        /// total lines
        QString alltext = code.readAll() ;
        totalLinesFile = alltext.count(QChar('\n')) ;
        QString strmax = QString().number(totalLinesFile);
        int n = strmax.size();

        code.seek(0);
        do
        {
            strline = code.readLine();

/// T4 test line analyze    TODO ...
         //   line = gcode.removeUnsupportedCommands(strline);
//diag("gcode:line = %s", qPrintable(line));
///<--
            index++;
/// T4      construct strline with index
            line = "%1";
            line = line.arg(index, n , 10 , QChar(' ') ) + " : " + strline;
            codeText.append(line + "\n");
/// <--
            GCode::trimToEnd(strline, '(');
            GCode::trimToEnd(strline, ';');
            GCode::trimToEnd(strline, '%');

            strline = strline.trimmed();
            p = 0; fr=0.0; ss = 0.0;
            if (strline.size() == 0)
            {   // ignore the white lines
            }
            else
            {
                strline = strline.toUpper();
                strline.replace("M6", "M06");
                strline.replace(QRegExp("([A-Z])"), " \\1");
                strline.replace(QRegExp("\\s+"), " ");
/// T4
                if (processGCode(strline, x, y, z, i, j, k,
                                  p, arc, cw, mm, g,
                                  plane, helix, fr, ss
                                  )
                    )
                {
                    if (!zeroInsert)
                    {
                        // insert 0,0 position
                        posList.append(PosItem());
                        zeroInsert = true;
                    }
                    xyz = QVector3D(x, y, z); ijk = QVector3D(i,j,k);
                    posList.append(PosItem(strline, xyz, ijk, p, arc, cw, mm, g, plane, helix, index, fr, ss));
                }
            }
            /// Fxxxx
            if (fr > 0)
                prevfr = fr;
            feedRateToLine.append(prevfr);
            /// Sxxxx
            if (ss > 0)
                prevss = ss;
            speedSpindleToLine.append(prevss);

        } while (code.atEnd() == false);

        /// number of lines
        strline = QString().setNum(index) ;
        ui->outputLines->setText(strline);
        /// write all lines
        ui->visuGcode->setPlainText(codeText);

        file.close();

        /// to 'ui-visu3D::setTotalNumLine(QString)'
        emit setTotalNumLine(strline)  ;
        /// to 'ui->wgtVisualizer::setItems(posList)' and 'ui->visu3D::setItems(posList)'
        emit setItems(posList);
        /// to to 'ui-visu3D::setFeedRateToLine(QList<double>)'
        emit setFeedRateToLine(feedRateToLine);
        /// to to 'ui-visu3D::setSpeedSpindleToLine(QList<double>)'
        emit setSpeedSpindleToLine(speedSpindleToLine);
        // the correct unit
        setUseMm(mm);
    }
    else
        printf("Can't open file\n");
}

/// T4
bool MainWindow::processGCode(QString inputLine,
                            double& x, double& y, double& z,
                            double& i, double& j, double& k,
                            int& p, bool& arc, bool& cw, bool& mm, int& g,
                            int& plane, bool& helix, double& f, double& sp
                            )
{
    QString line = inputLine.toUpper();
    QStringList components = line.split(" ", QString::SkipEmptyParts);
    QString s;
    arc = false;
    bool valid = false;
    f = 0.0;
    sp = 0.0;
    int nextIsValue = NO_ITEM;
    int value;
    bool bi(false), bj(false), bk(false);
  //  bool bx(false), by(false), bz(false);
    foreach (s, components)
    {
//diag("s= %s", qPrintable(s) );
        if (s.at(0) == 'F') {
            f = decodeLineItem(s, F_ITEM, valid, nextIsValue);
        }
        else
        if (s.at(0) == 'S') {
            sp = decodeLineItem(s, S_ITEM, valid, nextIsValue);
        }
        else
        if (s.at(0) == 'G')
        {
            value = s.mid(1).toInt();
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
/// T4   for arcs
            else if (value == 17)   // plane XY
                plane = PLANE_XY_G17;
            else if (value == 18)   // plane ZX
                plane = PLANE_ZX_G19;
            else if (value == 19)   // plane YZ
                plane = PLANE_YZ_G18;
        }
        else if (g >= 0 && g <= 3 && s.at(0) == 'X')
        {
            x = decodeLineItem(s, X_ITEM, valid, nextIsValue);
            helix = plane == PLANE_YZ_G18;
        }
        else if (g >= 0 && g <= 3 && s.at(0) == 'Y')
        {
            y = decodeLineItem(s, Y_ITEM, valid, nextIsValue);
            helix = plane == PLANE_ZX_G19;
        }
/// T4
        else if (g >= 0 && g <= 3 && s.at(0) == 'Z')
        {
            z = decodeLineItem(s, Z_ITEM, valid, nextIsValue);
            helix = plane == PLANE_XY_G17;
        }
        else if ((g == 2 || g == 3) && s.at(0) == 'I')
        {
            i = decodeLineItem(s, I_ITEM, arc, nextIsValue);
            bi = true;
        }
        else if ((g == 2 || g == 3) && s.at(0) == 'J')
        {
            j = decodeLineItem(s, J_ITEM, arc, nextIsValue);
            bj = true;
        }
/// T4
        else if ((g == 2 || g == 3) && s.at(0) == 'K')
        {
            k = decodeLineItem(s, K_ITEM, arc, nextIsValue);
            bk = true;
        }
        else if ((g == 2 || g == 3) && s.at(0) == 'P')
        {
            p = decodeLineItem(s, P_ITEM, valid, nextIsValue);
        }
/// Fxxxx
        else if ((g == 1 || g == 2 || g == 3) && s.at(0) == 'F')
        {
            f = decodeLineItem(s, F_ITEM, valid, nextIsValue);
        }
        else if ((g == 1 || g == 2 || g == 3) && s.at(0) == 'S')
        {
            sp = decodeLineItem(s, S_ITEM, valid, nextIsValue);
        }
/// <--
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
/// T4
            case Z_ITEM:
                z = decodeDouble(s, valid);
                break;
            case I_ITEM:
                i = decodeDouble(s, arc);
                break;
            case J_ITEM:
                j = decodeDouble(s, arc);
                break;
/// T4
            case K_ITEM:
                k = decodeDouble(s, arc);
                break;
            case P_ITEM:
                p = decodeDouble(s, valid);
                break;
            case F_ITEM:
                f = decodeDouble(s, valid);
                break;
            case S_ITEM:
                sp = decodeDouble(s, valid);
                break;

            };
            nextIsValue = NO_ITEM;
        }
        // plane if NO_PLANE
        if (!(plane == PLANE_XY_G17 || plane == PLANE_YZ_G18 || plane == PLANE_ZX_G19) )
        {
            if (bi && bj && !bk)
                plane = PLANE_XY_G17 ;
            else
            if (bi && !bj && bk)
                plane = PLANE_ZX_G19 ;
            else
            if (!bi && bj && bk)
                plane = PLANE_YZ_G18 ;
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

    QString jogStepStr = settings.value(SETTINGS_JOG_STEP, "10").value<QString>();
    jogStep = jogStepStr.toFloat() ;
    ui->sliderStep->setValue(int(jogStep*100));

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

// calls : 'Options::toggleUseMm(bool useMm'):1,
void MainWindow::setSettingsOptionsUseMm()
{
//diag(" MainWindow::setSettingsOptionsUseMm() ...");
    controlParams.useMm = opt.getUseMm();
    controlParams.zJogRate = opt.getZJogRate();
  //  controlParams.zRateLimit = opt.getzRateLimit();
    controlParams.xyRateAmount = opt.getXYRate();
    // update gcode thread with latest values
    emit setResponseWait(controlParams);
}

// Slot called from settings 'Options' dialog after user made a change.
// Reload settings from registry.
// calls: 'Options::accept()':1,
void MainWindow::setSettingsOptions()
{
    QSettings settings;
    updateSettingsFromOptionDlg(settings);
    // update gcode thread with latest values
    emit setResponseWait(controlParams);
}

// calls : 'setSettingsOptions()':1,
void MainWindow::updateSettingsFromOptionDlg(QSettings& settings)
{
/// T4
    ui->statusList->setMaximumBlockCount( settings.value( SETTINGS_MAX_STATUS_LINES, 0 ).value<int>() );

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

    char name = settings.value(SETTINGS_FOUR_AXIS_NAME, FOURTH_AXIS_A).value<char>();
    controlParams.fourthAxisName = name;
    bool rot = settings.value(SETTINGS_FOUR_AXIS_ROTATE, true).value<bool>();
    controlParams.fourthAxisRotate = rot;

    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->HomeFourthBtn->setEnabled(controlParams.useFourAxis);

    if (!controlParams.useFourAxis)
    {
        ui->DecFourthBtn->hide();
        ui->IncFourthBtn->hide();
        ui->HomeFourthBtn->hide();
        ui->lcdWorkNumberFourth->hide();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lcdMachNumberFourth->hide();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->lblFourth->hide();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
/// T4 ui->chkRestoreAbsolute->setEnabled(v);
        ui->unitFourth->hide();
        ui->unitFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
    }
    else
    {
        ui->DecFourthBtn->show();
        ui->IncFourthBtn->show();
        ui->HomeFourthBtn->show();
        ui->lcdWorkNumberFourth->show();
        ui->lcdWorkNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lcdMachNumberFourth->show();
        ui->lcdMachNumberFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lblFourth->show();
        ui->lblFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->lblFourth->setText(QString(controlParams.fourthAxisName));
        ui->unitFourth->setText(controlParams.fourthAxisRotate == true ?QString("deg."):QString("mm") );
/// T4
        ui->unitFourth->show();
        ui->unitFourth->setAttribute(Qt::WA_DontShowOnScreen, false);

        QString axisJog(tr("Z Jog"));// not correct, but a default placeholder we have a translation for already
        char axis = controlParams.fourthAxisName;
        if (axis == FOURTH_AXIS_A)  {
            axisJog = tr("A Jog");
        }
        else if (axis == FOURTH_AXIS_B){
            axisJog = tr("B Jog");
        }
        else if (axis == FOURTH_AXIS_C) {
            axisJog = tr("C Jog");
        }
        else if (axis == FOURTH_AXIS_U) {
            axisJog = tr("U Jog");
        }
        else if (axis == FOURTH_AXIS_V) {
            axisJog = tr("V Jog");
        }
        else if (axis == FOURTH_AXIS_W){
            axisJog = tr("W Jog");
        }
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
   // controlParams.usePositionRequest = enPosReq == "true";
    controlParams.positionRequestType = settings.value(SETTINGS_TYPE_POS_REQ, PREQ_ALWAYS_NO_IDLE_CHK).value<QString>();
    double posReqFreq = settings.value(SETTINGS_POS_REQ_FREQ_SEC, DEFAULT_POS_REQ_FREQ_SEC).value<double>();
    controlParams.postionRequestTimeMilliSec = static_cast<int>(posReqFreq) * 1000;

    controlParams.posReqKind =  settings.value(SETTINGS_POS_REQ_KIND, POS_REQ).value<int>();

/// T4
    posReqKind = controlParams.posReqKind;
    switch (posReqKind) {
        case POS_REQ:
            controlParams.usePositionRequest = true;
            controlParams.positionSyncSimu = false;
            controlParams.positionNoDisplay = false;
            break;
        case POS_SYNC:
            controlParams.usePositionRequest = false;
            controlParams.positionSyncSimu = true;
            controlParams.positionNoDisplay = false;
            break;
        case POS_NO:
            controlParams.usePositionRequest = false;
            controlParams.positionSyncSimu = false;
            controlParams.positionNoDisplay = true;
            break;
    }
    // -> 'gcode::setPosReqKind(posRegKind)'
    emit setPosReqKind(posReqKind) ;

    setLcdState(controlParams.usePositionRequest /*|| controlParams.positionSyncSimu */ );
/// <--
}

// save last state of settings
// calls : 'MainWindow::closeEvent()':1,
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
    settings.setValue(SETTINGS_JOG_STEP, QString().number(jogStep));

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

    ui->statusList->appendPlainText( nMsg );

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

        ui->statusList->appendPlainText( msg );

        status("%s", qPrintable(msg) );
    }
}

void MainWindow::receiveMsgSatusBar(QString msg)
{
  //  ui->centralWidget->setStatusTip(msg);
/// T4  Status bar leaves old error displayed even after error corrected #57
    ui->statusBar->showMessage(msg);
}

void MainWindow::grblSettings()
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

// calls : 'ui->spindleButton::toggled(valid)'
void MainWindow::toggleSpindle(bool)
{
/// T4
    QPalette palette;
    QString stateon(tr("Spindle On")), stateoff(tr("Spindle Off"));
    if (ui->spindleButton->isChecked())
    {
        sendGcode("M05\r");
        receiveList(stateoff);

        ui->spindleButton->setText(stateon) ;
        palette.setColor(QPalette::Button,Qt::gray) ;
    }
    else
    {
        sendGcode("M03\r");
         receiveList(stateon);

        ui->spindleButton->setText(stateoff) ;
        palette.setColor(QPalette::Button,Qt::yellow) ;
    }
     // color 'spindleButton'
    ui->spindleButton->setPalette(palette);
}

void MainWindow::toggleRestoreAbsolute()
{
    absoluteAfterAxisAdj = ui->chkRestoreAbsolute->QAbstractButton::isChecked();
}

/// T4 animator,
// calls : 'Viewer::setLivePoint()':1, 'Viewer::setLiveRelPoint()':1,
void MainWindow::updateLCD(QVector3D coord)
{
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->HomeFourthBtn->setEnabled(controlParams.useFourAxis);
    //
    machineCoordinates = Coord3D();
    workCoordinates = Coord3D(coord);

// T4   !!!
    cmdMan = false;
    refreshLcd();
}
///<--

void MainWindow::updateCoordinates(Coord3D machineCoord, Coord3D workCoord)
{
    ui->lcdWorkNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->lcdMachNumberFourth->setEnabled(controlParams.useFourAxis);
    ui->IncFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->DecFourthBtn->setEnabled(controlParams.useFourAxis);
    ui->HomeFourthBtn->setEnabled(controlParams.useFourAxis);
    machineCoordinates = machineCoord;
    workCoordinates = workCoord;

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
        lcdDisplay(controlParams.fourthAxisName, true, workCoordinates.fourth);
        lcdDisplay(controlParams.fourthAxisName, false, machineCoordinates.fourth);
	}
	else {
        lcdDisplay(controlParams.fourthAxisName, true, 0);
        lcdDisplay(controlParams.fourthAxisName, false, 0);
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
			|| axis == FOURTH_AXIS_U || axis == FOURTH_AXIS_V || axis == FOURTH_AXIS_W
			)
        {
            if (workCoord)
                ui->lcdWorkNumberFourth->display(value);
            else
                ui->lcdMachNumberFourth->display(value);
        }
        else
        {
            err( qPrintable(tr("Unexpected type %c")), axis) ;
        }
        break;
    }
/// T4
    if (cmdMan && !runFile) {
        // tool
        float x = ui->lcdWorkNumberX->value(),
              y = ui->lcdWorkNumberY->value(),
              z = ui->lcdWorkNumberZ->value();
        emit setLivePoint(QVector3D(x, y, z), controlParams.useMm );
//diag(" =====>cmdMan = %s",  cmdMan==true ?"true" : "false");
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
            info(qPrintable(tr("Usr chg: pos=%d new=%d\n")), pos, newPos);
        else
            info(qPrintable(tr("Usr chg: pos=%.1f new=%.1f\n")), (double)pos/10, newPos);
    }
    else
    {
        ui->verticalSliderZJog->setSliderPosition(CENTER_POS);
        ui->currentZJogSliderDelta->setText("0");
        if(controlParams.useMm)
            info(qPrintable(tr("Usr chg no slider: %d\n")), pos);
        else
            info(qPrintable(tr("Usr chg no slider: %.1f\n")), (double) pos/10);
    }
}

void MainWindow::zJogSliderPressed()
{
    sliderPressed = true;
    if (workCoordinates.stoppedZ && workCoordinates.sliderZIndex == sliderZCount)
    {
        info(qPrintable(tr("Pressed and stopped\n")));
        sliderTo = workCoordinates.z;
    }
    else
    {
        info(qPrintable(tr("Pressed not stopped\n")));
    }
}

void MainWindow::zJogSliderReleased()
{
    info(qPrintable(tr("Released\n")));

    if (sliderPressed)
    {
        sliderPressed = false;
        int value = ui->verticalSliderZJog->value();

        ui->verticalSliderZJog->setSliderPosition(CENTER_POS);
        ui->currentZJogSliderDelta->setText("0");

        value -= CENTER_POS;

        if (value != 0)
        {
/// T4
            enableAllButtons(false);

            if(controlParams.useMm)
                sliderTo += value;
            else
                sliderTo += (double)value/10;
            float setTo = value;
            cmdMan = true;
            if(controlParams.useMm)
                emit axisAdj('Z', setTo, invZ, absoluteAfterAxisAdj, sliderZCount++);
            else
                emit axisAdj('Z', setTo/10, invZ, absoluteAfterAxisAdj, sliderZCount++);
        }
    }
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
            if (checkState)
                ss = "QLCDNumber { background-color: #F8F8F8; color: yellow; }";
            else
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
/*
void MainWindow::refreshPosition()
{
    // gotoXYZFourth(REQUEST_CURRENT_POS); ??
    emit gotoXYZFourth(REQUEST_CURRENT_POS);
}
*/

// calls : 'sliderStep::valueChanged(int)'
void MainWindow::stepChanged(int newstep)
{   // newstep into [0..10000]  mm*100
    float fs = newstep/100.0;
    if (!controlParams.useMm)
        fs /= MM_IN_AN_INCH ;
    ui->lcdStep->display(fs);
    jogStep = fs;
}

///-----------------------------------------------------------------------------
///  T2
// calls : 'GCode::sendGcodeInternal()':1,
void MainWindow::setLinesFile(QString linesFile, bool check)
{
    if (check)   /// T3
        linesFile +=  "/" + QString().setNum(totalLinesFile);;

    ui->outputLines->setText(linesFile);
}

///-----------------------------------------------------------------------------
/// for visuGode and visu3D
/// T4
//  calls : 'ui->visualButton::toggled(valid)'
void MainWindow::toVisual(bool valid)
{
    ui->prevButton->setEnabled(valid);
    ui->nextButton->setEnabled(valid);
    ui->pauseButton->setEnabled(valid);

    ui->btnClearStatusList->setEnabled(!valid);
    ui->btnPrintStatusList->setEnabled(!valid);
    ui->btnPrintVisual->setEnabled(!valid) ;

    if (ui->visualButton->isChecked())
        ui->visualButton->setText(tr("No animate")) ;
    else
        ui->visualButton->setText(tr("Animate")) ;
    // no openFile if valid
    ui->openFile->setEnabled(!valid);
    if (!valid) {  // no animate
        ui->btnCheck->setEnabled(openState);
        ui->Begin->setEnabled(openState);
    }
    else {
       ui->btnCheck->setEnabled(!valid);
       ui->Begin->setEnabled(!valid);
    }
    //  tab
    bool openport = ui->btnOpenPort->text() != open_button_text ;
    if (!openport) {
        ui->tabAxisVisualizer->setEnabled(valid);
        ui->tabVisu->setTabEnabled(TAB_CONSOLE_INDEX, !valid);
        // (in)valid manual controls
        enableManualControl(false);
    }
    else  {
        ui->tabAxisVisualizer->setEnabled(true);
        ui->tabAxisVisualizer->setTabEnabled(TAB_VISU3D_INDEX, true);
        // invalid manual controls
        enableManualControl(!valid);
    }
    ui->tabVisu->setTabEnabled(TAB_CONSOLE_INDEX, !valid);
    ui->tabAxisVisualizer->setTabEnabled(TAB_VISUALIZER_INDEX, !valid);
    // to ui->Viewer
    emit setVisual(valid);
}

// calls  :'ui->pauseButton::toggled(valid)'
void MainWindow::toPause(bool valid)
{
    QPalette palette;
    ui->prevButton->setEnabled(valid);
    ui->nextButton->setEnabled(valid);
    if (ui->pauseButton->isChecked())  {
        ui->pauseButton->setText(tr("Run")) ;
        palette.setColor(QPalette::Button,Qt::gray) ;
        // mouse and keyboard key
        connect(ui->visuGcode, SIGNAL(cursorPositionChanged() ), this, SLOT(on_cursorVisuGcode()) ) ;
    }
    else  {
        ui->pauseButton->setText(tr("Pause")) ;
        palette.setColor(QPalette::Button,Qt::yellow);
        // no mouse and no keyboard key
        disconnect(ui->visuGcode, SIGNAL(cursorPositionChanged() ), this, SLOT(on_cursorVisuGcode()) ) ;
    }
    // color 'pauseButton'
    ui->pauseButton->setPalette(palette);
    // to ui->Viewer
    emit setPause(valid);
}

// calls : 'ui->visuGcode::cursorPositionChanged()'
void MainWindow::on_cursorVisuGcode()
{
    int line = ui->visuGcode->textCursor().blockNumber();
    if (line <= totalLinesFile)
        setActiveLineVisuGcode(line +1, false);
}

// calls :  MainWindow::on_cursorVisuGcode()':1, 'Viewer::setLivePoint()':1,
//          'Viewer::setLiveRelPoint()':1
void MainWindow::setActiveLineVisuGcode( int line, bool visu )
{
    if (!line) return ;

    QTextBlock       block;
    QTextCursor      cursor;
    QTextBlockFormat blockFormat;

    block       = ui->visuGcode->document()->findBlockByNumber( activeLine - 1 );
    cursor      = QTextCursor( block );
    blockFormat = cursor.blockFormat();
    blockFormat.clearBackground();
    cursor.setBlockFormat( blockFormat );

    activeLine = line ;

    block       = ui->visuGcode->document()->findBlockByNumber( activeLine - 1 );
    cursor      = QTextCursor( block );
    blockFormat = cursor.blockFormat();
    blockFormat.setBackground( Qt::lightGray );
    cursor.setBlockFormat( blockFormat );
    ui->visuGcode->setTextCursor( cursor );
    /// emission line number
    QString strline = QString().setNum(activeLine) ;
    // to 'ui->lineCode'  (QLabel)
    emit  setLineCode(strline);
    // to  Viewer : 'ui->visu3D::setNumLine(activeLine)'
    if (!visu)  {
        emit setNumLine(strline);
    }
}

/// display timer period animation
// calls :  none ?
void MainWindow::setLCDValue(int value)
{
    ui->lcdPeriodAnim->display(value);
}

// display the correct unit
// calls : 'GCode::setResponseWait( )':1, 'GCode::checkGrbl()':0,
void MainWindow::setUnitMmAll (bool useMm )
{
//diag("MainWindow::setUnitMmAll (..) ...");
//1- display
    QString unit(tr("mm"));
    double val = ui->doubleSpinBoxTol->value();
    if (useMm) {
        ui->doubleSpinBoxTol->setDecimals(3);
        ui->doubleSpinBoxTol->setSingleStep(TOL_MM_STEP);
        ui->doubleSpinBoxTol->setMinimum(TOL_MM_MIN);
        ui->doubleSpinBoxTol->setMaximum(TOL_MM_MAX);
        if (ui->labelTolUnit->text() != unit)
           val = TOL_MM ;
    }
    else {
        ui->doubleSpinBoxTol->setDecimals(4);
        ui->doubleSpinBoxTol->setSingleStep(TOL_IN_STEP);
        ui->doubleSpinBoxTol->setMinimum(TOL_IN_MIN);
        ui->doubleSpinBoxTol->setMaximum(TOL_IN_MAX);
        unit = QString(tr("in"));
        if (ui->labelTolUnit->text() != unit)
          val = TOL_IN;
    }
    ui->doubleSpinBoxTol->setValue(val) ;

    ui->lcdFeedRateGcode->display(0.0);

    ui->labelFeedRateUnit->setText( unit +  "/" + tr("mn"));
    ui->labelTolUnit->setText(unit);
    unit += " ";
    ui->unitX->setText(unit);
    ui->unitY->setText(unit);
    ui->unitZ->setText(unit);
    if (controlParams.fourthAxisRotate)
        unit = tr("deg.");
    else
        unit = tr("mm");

    ui->unitFourth->setText(unit);
    // slider
    int step = ui->sliderStep->value();
    ui->sliderStep->setValue(0);
    ui->sliderStep->setValue(step);
// Grbl
    if (useMm) {

    }
    else {

    }
}

/// T4
void MainWindow::enableManualControl(bool v)
{
    ui->chkRestoreAbsolute->setEnabled(v);
    // step
    ui->sliderStep->setEnabled(v);
    ui->lcdStep->setEnabled(v);
    // dZ
    ui->verticalSliderZJog->setEnabled(v);
    ui->currentZJogSliderDelta->setEnabled(v);
    ui->resultingZJogSliderPosition->setEnabled(v);
    // axes buttons
    ui->DecXBtn->setEnabled(v); ui->IncXBtn->setEnabled(v); ui->HomeXBtn->setEnabled(v) ;
    if (ui->lcdWorkNumberX->value()==0)
        ui->HomeXBtn->setEnabled(false) ;
    ui->DecYBtn->setEnabled(v); ui->IncYBtn->setEnabled(v);ui->HomeYBtn->setEnabled(v);
    if (ui->lcdWorkNumberY->value()==0)
        ui->HomeYBtn->setEnabled(false);
    ui->DecZBtn->setEnabled(v); ui->IncZBtn->setEnabled(v); ui->HomeZBtn->setEnabled(v) ;
    if (ui->lcdWorkNumberZ->value()==0)
        ui->HomeZBtn->setEnabled(false) ;
    if (controlParams.useFourAxis ) {
        ui->DecFourthBtn->setEnabled(v); ui->IncFourthBtn->setEnabled(v);
        ui->HomeFourthBtn->setEnabled(v) ;
        if (ui->lcdWorkNumberFourth->value()==0)
            ui->HomeFourthBtn->setEnabled(false) ;
    }
    // spindle
    ui->spindleButton->setEnabled(v);
}

void MainWindow::enableTabVisuControls(bool v)
{
    // animation period
    ui->lcdPeriodAnim->setEnabled(v);
    ui->labelPeriod->setEnabled(v);
    ui->dialPeriodRepeat->setEnabled(v);
    // animation cursors
    ui->nextButton->setEnabled(v);
    ui->lineCode->setEnabled(v);
    ui->nline->setEnabled(v);
    ui->prevButton->setEnabled(v);
    // segments interpolation
    ui->lcdSegments->setEnabled(v);
    ui->labelSegments->setEnabled(v);
    // tolerance
    ui->doubleSpinBoxTol->setEnabled(v);
    ui->labelTol->setEnabled(v);
    ui->labelTolUnit->setEnabled(v);
    ui->lcdTolerance->setEnabled(v);
    // on off
    ui->pauseButton->setEnabled(v);
    ui->visualButton->setEnabled(v);
}

// Grbl commands
void MainWindow::enableButtonGrblControls(bool v)
{
    ui->btnHelp->setEnabled(v);
    ui->btnParameters->setEnabled(v);
    ui->btnParserState->setEnabled(v);
    ui->btnBuildInfo->setEnabled(v);
    ui->btnStartupBlocks->setEnabled(v);
    ui->btnCheck->setEnabled(v);
    ui->btnGrblSettings->setEnabled(v);
    ui->btnUnlockGrbl->setEnabled(v);
    ui->btnHomingCycle->setEnabled(v);
 //   ui->btnCycleStart->setEnabled(v);
 //   ui->btnFeedHold->setEnabled(v);
    ui->btnStatus->setEnabled(v);
    ui->btnResetGrbl->setEnabled(v);

    ui->btnSetHome->setEnabled(v);
    ui->btnGoHomeSafe->setEnabled(v);
    // = 'btnStatus'
  //  ui->pushButtonRefreshPos->setEnabled(v);
}

// calls : 'ui->btnClearStatusList'
void MainWindow::toClearSatusList()
{
    if (ui->statusList->textCursor().hasSelection())   {
         ui->statusList->textCursor().removeSelectedText();
    }
}

// calls : 'ui->btnPrintStatusList'
void MainWindow::toPrintStatusList()
{
    QPrinter printer;
    QString txt = GRBL_CONTROLLER_NAME_AND_VERSION VERSION_BUILD;
    txt += "\n\n";
    // file title
    txt += ui->filePath->text();
    txt += "\n\n";
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    if (ui->statusList->textCursor().hasSelection())   {
         dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
         printer.setPrintRange(QPrinter::Selection);
         txt += ui->statusList->textCursor().selectedText();
    }
    else {
        txt += ui->statusList->document()->toPlainText();
    }
    if (dialog->exec() == QDialog::Accepted)      {
       QTextDocument  doc(txt);
       doc.print(&printer);
    }
}

// calls : 'ui->btnPrintVisual'
void MainWindow::toPrintVisual()
{
    QPrinter printer;
    QString txt = GRBL_CONTROLLER_NAME_AND_VERSION VERSION_BUILD;
    txt += "\n\n";
    // file title
    txt += ui->filePath->text();
    txt += "\n\n";
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    if (ui->visuGcode->textCursor().hasSelection())  {
         dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
         printer.setPrintRange(QPrinter::Selection);
         txt += ui->visuGcode->textCursor().selectedText();
    }
    else {
        txt += ui->visuGcode->document()->toPlainText();
    }
    if (dialog->exec() == QDialog::Accepted)  {
       QTextDocument  doc(txt);
       doc.print(&printer);
    }
}

// calls : 'processGCode(...)':1,
void MainWindow::setUseMm(bool useMm)
{
    /// acces to "Options::checkBoxUseMmManualCmds"
    if (opt.getUseMm() != useMm ) {
//diag("MainWindow::setUseMm(..) ...");
        opt.setUseMm(useMm);
    }
}
//------------------------------------------------------------------------------
