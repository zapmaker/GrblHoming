/****************************************************************
 * mainwindow.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include <QCloseEvent>
#include <QItemDelegate>
/// T4
#include <QListView>
#include "about.h"
#include "definitions.h"
#include "grbldialog.h"
#include "options.h"
#include "timer.h"
#include "positem.h"
#include "gcode.h"
#include "renderarea.h"
#include "visu3D\viewer3D.h"

#define COMPANY_NAME "zapmaker"
#define APPLICATION_NAME "GrblController"
#define DOMAIN_NAME "org.zapmaker"

/// T4
#define TAB_VISUALIZER_INDEX    0
#define TAB_VISU3D_INDEX        1

#define TAB_CONSOLE_INDEX       0
#define TAB_VISUGCODE_INDEX     1

#define CENTER_POS              40

#define MAX_STATUS_LINES_WHEN_ACTIVE        200

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

    //variables
    int delete_nr;

signals:
    //threads
    void openPort(QString port, QString baudRate);
    void closePort(bool reopen);
    void shutdown();
    void sendGcode(QString line, bool recordResponseOnFail = false, int waitCount = SHORT_WAIT_SEC);
/// T3
    void sendFile(QString path, bool);
    void gotoXYZFourth(QString line);
    void axisAdj(char axis, float coord, bool inv, bool absoluteAfterAxisAdj, int sliderZCount);
    void setResponseWait(ControlParams controlParams);
    void setProgress(int percent);
    void setRuntime(QString runtime);
    void sendSetHome();
/// T3, T4
  //  void sendGrblPause(bool);
    void sendGrblHelp();
    void sendGrblParserState();
    void sendGrblParameters();
    void sendGrblBuildInfo();
    void sendGrblStartupBlocks();
    void sendGrblCheck(bool);
    void sendGrblUnlock();
    void sendGrblHomingCycle();
    void sendGrblCycleStart();
    void sendGrblFeedHold() ;
    void sendGrblStatus();
    void sendGrblReset();

    void goToHome();
/// T4
    void goToHomeAxis(char axis);
    void setLineCode(QString) ;
    void setItems(QList<PosItem>);
    void setTotalNumLine(QString);
    void setNumLine(QString);
    void setLivePoint(QVector3D, bool) ;
    void setLiveRelPoint(QVector3D) ;
/// T4
    void setFeedRateToLine(QList<double>) ;
    void setSpeedSpindleToLine(QList<double>) ;
    void runCode(bool, int);
    void setVisual(bool);
    void setPause(bool);
    void setTol(double);
    void setPosReqKind(int);
/// <-

private slots:
/// T4
    void pauseSend(bool);   // suspend sendFile()
    void grblHelp();
    void grblSettings();
    void grblParameters() ;
    void grblParserState() ;
    void grblBuildInfo();
    void grblStartupBlocks();
    void grblCheck(bool);
    void grblUnlock();
    void grblHomingCycle() ;
// not used
void grblCycleStart();
void grblFeedHold();
    void grblStatus();
    void grblReset();

    //buttons
    void openPort();
    //Adjust
    void decX();
    void decY();
    void decZ();
    void decFourth();
    void incFourth();
    void incX();
    void incY();
    void incZ();
/// T5
    void homeX();
    void homeY();
    void homeZ();
    void homeFourth();

    void endHomeAxis();
    void setHome();
     //manualhomeFourth()
    void gotoXYZFourth();

/// T3
    void begin();
    void openFile();
    void stop();
    void stopSending();
    //
    void portIsOpen(bool sendCode);
    void portIsClosed(bool reopen);
    void adjustedAxis();

    void toggleSpindle(bool);
    //check boxes
    void toggleRestoreAbsolute();

    //communications
        //options
    void setSettingsOptions();
    void setSettingsOptionsUseMm();
        //thread
    void receiveList(QString msg);
    void receiveListFull(QStringList list);
    void receiveListOut(QString msg);
    void receiveMsgSatusBar(QString msg);
    //menu bar
    void getOptions();
    void showAbout();
    void enableGrblDialogButton();

    void updateCoordinates(Coord3D machineCoord, Coord3D workCoord);

    void goHomeSafe();
    void zJogSliderDisplay(int pos);
    void zJogSliderPressed();
    void zJogSliderReleased();

    void setQueuedCommands(int commandCount, bool running);
/// T4
    void setQueueClear();
    void setLcdState(bool valid);
  //  void refreshPosition();

/// T2
    void setLinesFile(QString linesFile, bool check);
/// T4 3D
    void updateLCD(QVector3D);
/// T4  for 'visuGcode'
    void toVisual(bool);
    void toPause(bool);
    void on_cursorVisuGcode();
    void setActiveLineVisuGcode(int, bool);
    void setLCDValue(int value);
    // change  text "mm" <=> "in"
    void setUnitMmAll(bool);
    void stepChanged(int);
    void enableManualControl(bool);
    void enableTabVisuControls(bool);
    void enableButtonGrblControls(bool);

    void toClearSatusList();
    void toPrintStatusList();
    void toPrintVisual();

    void setLastState(QString state);

private:
    // enums
    enum
    {
        NO_ITEM = 0, X_ITEM, Y_ITEM, Z_ITEM, I_ITEM, J_ITEM, K_ITEM,
        P_ITEM, F_ITEM, S_ITEM
    };
    enum
    {
        QCS_OK = 0, QCS_WAITING_FOR_ITEMS
    };
    //objects
    Ui::MainWindow *ui;
    //FileSender fileSender;
    //QThread fileSenderThread;
    GCode gcode;
    QThread gcodeThread;

    Timer runtimeTimer;
    QThread runtimeTimerThread;

    Options opt;

    //variables
    bool invX;
    bool invY;
    bool invZ;
    bool invFourth;
	/// for translation
	QString open_button_text ;
	QString close_button_text ;
    bool mm;
    QString styleSheet;
    QString directory;
    QString nameFilter;
    QString lastOpenPort;
    QString lastBaudRate;
    QByteArray fileOpenDialogState;
    Coord3D machineCoordinates;
    Coord3D workCoordinates;
    bool absoluteAfterAxisAdj;
    bool checkLogWrite;
/// T4
    QTime queuedCommandsEmptyTimer;
    QTime queuedCommandsRefreshTimer;
    QList<PosItem> posList;
    bool sliderPressed;
    double sliderTo;
    int sliderZCount;
    bool promptedAggrPreload;
    ControlParams controlParams;

    bool queuedCommandsStarved;
    int lastQueueCount;
    int queuedCommandState;
    QStringList fullStatus;
    bool lastLcdStateValid;
    float jogStep;
   // QString jogStepStr;
///  T3
    bool checkState;
    bool sendButtonCheck;
    bool openState;
    int totalLinesFile;
/// T4 for 'visuGcode'
    int activeLine;
    bool runFile, cmdMan;
    /// mode display request
    int posReqKind;

private:
// methods
    void setUseMm(bool);
    int SendJog(QString strline);
    void readSettings();
    void writeSettings();
    void addToStatusList(bool in, QString msg);
    void addToStatusList(QStringList& list);
    void enableAllButtons(bool);
    void openPortCtl(bool reopen);
    void resetProgress();
    void refreshLcd();
    void lcdDisplay(char axis, bool workCoord, float value);
    void updateSettingsFromOptionDlg(QSettings& settings);
    int computeListViewMinimumWidth(QAbstractItemView* view);
    void preProcessFile(QString filepath);

/// T4  3 axes + plane
    bool processGCode(QString inputLine,
                        double& x, double& y, double& z,
                        double& i, double& j, double& k,
                        int& p, bool& arc, bool& cw, bool& mm,
                        int& g, int& plane, bool& helix,
                        double& f, double& ss
                        );
/// <-
    double decodeLineItem(const QString& item, const int next, bool& valid, int& nextIsValue);
    double decodeDouble(QString value, bool& valid);
};

#endif // MAINWINDOW_H
