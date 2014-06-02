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
#include <QScrollBar>
#include <QListView>
#include "about.h"
#include "definitions.h"
#include "grbldialog.h"
#include "options.h"
//#include "filesender.h"
#include "timer.h"
#include "positem.h"
#include "gcode.h"
#include "renderarea.h"

#define COMPANY_NAME "zapmaker"
#define APPLICATION_NAME "GrblController"
#define DOMAIN_NAME "org.zapmaker"

#define TAB_AXIS_INDEX          0
#define TAB_VISUALIZER_INDEX    1
#define TAB_ADVANCED_INDEX      2

#define CENTER_POS              40

#define MAX_STATUS_LINES_WHEN_ACTIVE        200

/* testing optimizing scrollbar, doesn't work right
class MyItemDelegate : public QItemDelegate
{
private:
    int width;
    QAbstractItemView *parentWidget;

public:

    MyItemDelegate(QAbstractItemView *p) : parentWidget(p) {}

    void setWidth(int w)
    {
        width = w;
    }

    void drawDisplay(QPainter *painter,const
    QStyleOptionViewItem &option,const QRect &rect,const QString &text) const{

        QRect tempRect(rect);
        tempRect.setWidth(parentWidget->width());
        QItemDelegate::drawDisplay(painter,option,tempRect,text);

    }

    QSize sizeHint(const QStyleOptionViewItem & option, const
    QModelIndex & index ) const  {

        QListView *list = qobject_cast<QListView*>(parentWidget);
        QSize newSize(QItemDelegate::sizeHint(option,index));
        if( list ) newSize.setWidth( width );
        return newSize;
    }
};
*/

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
    void sendFile(QString path);
    void gotoXYZFourth(QString line);
    void axisAdj(char axis, float coord, bool inv, bool absoluteAfterAxisAdj, int sliderZCount);
    void setResponseWait(ControlParams controlParams);
    void setProgress(int percent);
    void setRuntime(QString runtime);
    void sendSetHome();
    void sendGrblReset();
    void sendGrblUnlock();
    void goToHome();
    void setItems(QList<PosItem>);

private slots:
    //buttons
    void openPort();
    void setGRBL();
        //Adjust
    void decX();
    void decY();
    void decZ();
    void decFourth();
    void incFourth();
    void incX();
    void incY();
    void incZ();
    void setHome();
        //manual
    void gotoXYZFourth();
        //send Gcode
    void begin();
    void openFile();
    void stop();
    void stopSending();
    //
    void portIsOpen(bool sendCode);
    void portIsClosed(bool reopen);
    void adjustedAxis();

    //check boxes
    void toggleSpindle();
    void toggleRestoreAbsolute();

    //communications
        //options
    void setSettings();
        //thread
    void receiveList(QString msg);
    void receiveListFull(QStringList list);
    void receiveListOut(QString msg);
    void receiveMsg(QString msg);
    //menu bar
    void getOptions();
    void showAbout();
    void enableGrblDialogButton();
    void grblReset();
    void grblUnlock();
    void updateCoordinates(Coord3D machineCoord, Coord3D workCoord);
    void goHomeSafe();
    void zJogSliderDisplay(int pos);
    void zJogSliderPressed();
    void zJogSliderReleased();
    void doScroll();
    void statusSliderPressed();
    void statusSliderReleased();
    void setQueuedCommands(int commandCount, bool running);
    void setLcdState(bool valid);
    void refreshPosition();
    void comboStepChanged(const QString& text);

private:
    // enums
    enum
    {
        NO_ITEM = 0,
        X_ITEM,
        Y_ITEM,
        I_ITEM,
        J_ITEM,
    };
    enum
    {
        QCS_OK = 0,
        QCS_WAITING_FOR_ITEMS
    };
    //objects
    Ui::MainWindow *ui;
    //FileSender fileSender;
    //QThread fileSenderThread;
    GCode gcode;
    QThread gcodeThread;

    Timer runtimeTimer;
    QThread runtimeTimerThread;

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
    QTime scrollStatusTimer;
    QTime queuedCommandsEmptyTimer;
    QTime queuedCommandsRefreshTimer;
    QList<PosItem> posList;
    bool sliderPressed;
    double sliderTo;
    int sliderZCount;
    bool promptedAggrPreload;
    ControlParams controlParams;
    QTimer *scrollTimer;
    bool scrollRequireMove;
    bool scrollPressed;
    bool queuedCommandsStarved;
    int lastQueueCount;
    int queuedCommandState;
    QStringList fullStatus;
    bool lastLcdStateValid;
    float jogStep;
    QString jogStepStr;

    //methods
    int SendJog(QString strline);
    void readSettings();
    void writeSettings();
    void addToStatusList(bool in, QString msg);
    void addToStatusList(QStringList& list);
    void disableAllButtons();
    void openPortCtl(bool reopen);
    void resetProgress();
    void refreshLcd();
    void lcdDisplay(char axis, bool workCoord, float value);
    void updateSettingsFromOptionDlg(QSettings& settings);
    int computeListViewMinimumWidth(QAbstractItemView* view);
    void preProcessFile(QString filepath);
    bool processGCode(QString inputLine, double& x, double& y, double& i, double& j, bool& arc, bool& cw, bool& mm, int& g);
    double decodeLineItem(const QString& item, const int next, bool& valid, int& nextIsValue);
    double decodeDouble(QString value, bool& valid);
};


#endif // MAINWINDOW_H
