/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 29. Apr 17:15:07 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "renderarea.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionOptions;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *layoutComPort;
    QLabel *lblPort;
    QComboBox *cmbPort;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnOpenPort;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_br;
    QComboBox *comboBoxBaudRate;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelLastState;
    QLabel *outputLastState;
    QGroupBox *groupBoxSendFile;
    QVBoxLayout *verticalLayout_12;
    QGridLayout *gridLayout_2;
    QPushButton *Stop;
    QSpacerItem *horizontalSpacer;
    QPushButton *openFile;
    QPushButton *Begin;
    QLineEdit *filePath;
    QGridLayout *gridLayout_5;
    QProgressBar *progressFileSend;
    QProgressBar *progressQueuedCommands;
    QLabel *labelFileSendProgress;
    QLabel *labelQueuedCommands;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelRuntime;
    QLabel *outputRuntime;
    QHBoxLayout *layoutManualGCode;
    QLabel *labelCommand;
    QComboBox *comboCommand;
    QListWidget *statusList;
    QVBoxLayout *verticalLayout_RightControls;
    QGridLayout *gridLayout_CoodPositions;
    QLabel *lblX;
    QLCDNumber *lcdMachNumberY;
    QHBoxLayout *horizontalLayout;
    QLabel *labelWorkCoord;
    QLabel *outputUnitsWork;
    QLCDNumber *lcdWorkNumberY;
    QLabel *lblY;
    QLCDNumber *lcdMachNumberX;
    QLCDNumber *lcdWorkNumberZ;
    QLCDNumber *lcdMachNumberZ;
    QLCDNumber *lcdWorkNumberX;
    QLabel *lblZ;
    QLabel *lblFourth;
    QLCDNumber *lcdWorkNumberFourth;
    QLCDNumber *lcdMachNumberFourth;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelMachCoord;
    QLabel *outputUnitsMachine;
    QTabWidget *tabAxisVisualizer;
    QWidget *tabAxis;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_13;
    QGridLayout *gridLayout;
    QPushButton *DecXBtn;
    QPushButton *IncYBtn;
    QPushButton *DecYBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *IncXBtn;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblFourthJog;
    QPushButton *DecFourthBtn;
    QPushButton *IncFourthBtn;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QSlider *verticalSliderZJog;
    QLabel *currentZJogSliderDelta;
    QLabel *resultingZJogSliderPosition;
    QVBoxLayout *layoutZJog;
    QPushButton *IncZBtn;
    QLabel *lblZJog;
    QPushButton *DecZBtn;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkRestoreAbsolute;
    QCheckBox *SpindleOn;
    QVBoxLayout *verticalLayoutStepSize;
    QLabel *lblStep;
    QComboBox *comboStep;
    QWidget *tabVisualizer;
    QVBoxLayout *verticalLayout_5;
    RenderArea *wgtVisualizer;
    QWidget *tab;
    QGroupBox *groupBoxReset;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnResetGrbl;
    QPushButton *btnUnlockGrbl;
    QPushButton *btnGRBL;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnSetHome;
    QPushButton *btnGoHomeSafe;
    QPushButton *pushButtonRefreshPos;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(972, 668);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(7);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(10000000, 10000000));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_8 = new QHBoxLayout(centralWidget);
        horizontalLayout_8->setSpacing(10);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 1, -1, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(-1, 2, -1, -1);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        layoutComPort = new QHBoxLayout();
        layoutComPort->setSpacing(6);
        layoutComPort->setObjectName(QString::fromUtf8("layoutComPort"));
        layoutComPort->setContentsMargins(0, -1, -1, -1);
        lblPort = new QLabel(centralWidget);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblPort->sizePolicy().hasHeightForWidth());
        lblPort->setSizePolicy(sizePolicy1);
        lblPort->setMaximumSize(QSize(16777215, 16777215));

        layoutComPort->addWidget(lblPort);

        cmbPort = new QComboBox(centralWidget);
        cmbPort->setObjectName(QString::fromUtf8("cmbPort"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmbPort->sizePolicy().hasHeightForWidth());
        cmbPort->setSizePolicy(sizePolicy2);
        cmbPort->setMinimumSize(QSize(140, 0));
        cmbPort->setEditable(true);

        layoutComPort->addWidget(cmbPort);

        layoutComPort->setStretch(0, 1);
        layoutComPort->setStretch(1, 6);

        verticalLayout_10->addLayout(layoutComPort);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnOpenPort = new QPushButton(centralWidget);
        btnOpenPort->setObjectName(QString::fromUtf8("btnOpenPort"));
        sizePolicy2.setHeightForWidth(btnOpenPort->sizePolicy().hasHeightForWidth());
        btnOpenPort->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(btnOpenPort);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_br = new QLabel(centralWidget);
        label_br->setObjectName(QString::fromUtf8("label_br"));
        label_br->setFrameShape(QFrame::NoFrame);

        horizontalLayout_6->addWidget(label_br);

        comboBoxBaudRate = new QComboBox(centralWidget);
        comboBoxBaudRate->setObjectName(QString::fromUtf8("comboBoxBaudRate"));

        horizontalLayout_6->addWidget(comboBoxBaudRate);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 3);

        verticalLayout_11->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelLastState = new QLabel(centralWidget);
        labelLastState->setObjectName(QString::fromUtf8("labelLastState"));

        horizontalLayout_4->addWidget(labelLastState);

        outputLastState = new QLabel(centralWidget);
        outputLastState->setObjectName(QString::fromUtf8("outputLastState"));

        horizontalLayout_4->addWidget(outputLastState);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 3);

        verticalLayout_11->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_11);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(2, 3);

        verticalLayout_10->addLayout(horizontalLayout_2);


        verticalLayout_14->addLayout(verticalLayout_10);

        groupBoxSendFile = new QGroupBox(centralWidget);
        groupBoxSendFile->setObjectName(QString::fromUtf8("groupBoxSendFile"));
        groupBoxSendFile->setEnabled(false);
        verticalLayout_12 = new QVBoxLayout(groupBoxSendFile);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        Stop = new QPushButton(groupBoxSendFile);
        Stop->setObjectName(QString::fromUtf8("Stop"));

        gridLayout_2->addWidget(Stop, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(2, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        openFile = new QPushButton(groupBoxSendFile);
        openFile->setObjectName(QString::fromUtf8("openFile"));

        gridLayout_2->addWidget(openFile, 1, 0, 1, 1);

        Begin = new QPushButton(groupBoxSendFile);
        Begin->setObjectName(QString::fromUtf8("Begin"));

        gridLayout_2->addWidget(Begin, 1, 2, 1, 1);

        filePath = new QLineEdit(groupBoxSendFile);
        filePath->setObjectName(QString::fromUtf8("filePath"));

        gridLayout_2->addWidget(filePath, 0, 0, 1, 4);


        verticalLayout_12->addLayout(gridLayout_2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        progressFileSend = new QProgressBar(groupBoxSendFile);
        progressFileSend->setObjectName(QString::fromUtf8("progressFileSend"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(progressFileSend->sizePolicy().hasHeightForWidth());
        progressFileSend->setSizePolicy(sizePolicy3);
        progressFileSend->setValue(0);

        gridLayout_5->addWidget(progressFileSend, 0, 1, 1, 1);

        progressQueuedCommands = new QProgressBar(groupBoxSendFile);
        progressQueuedCommands->setObjectName(QString::fromUtf8("progressQueuedCommands"));
        sizePolicy3.setHeightForWidth(progressQueuedCommands->sizePolicy().hasHeightForWidth());
        progressQueuedCommands->setSizePolicy(sizePolicy3);
        progressQueuedCommands->setMaximum(10);
        progressQueuedCommands->setValue(0);

        gridLayout_5->addWidget(progressQueuedCommands, 1, 1, 1, 1);

        labelFileSendProgress = new QLabel(groupBoxSendFile);
        labelFileSendProgress->setObjectName(QString::fromUtf8("labelFileSendProgress"));
        sizePolicy1.setHeightForWidth(labelFileSendProgress->sizePolicy().hasHeightForWidth());
        labelFileSendProgress->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(labelFileSendProgress, 0, 0, 1, 1);

        labelQueuedCommands = new QLabel(groupBoxSendFile);
        labelQueuedCommands->setObjectName(QString::fromUtf8("labelQueuedCommands"));
        sizePolicy1.setHeightForWidth(labelQueuedCommands->sizePolicy().hasHeightForWidth());
        labelQueuedCommands->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(labelQueuedCommands, 1, 0, 1, 1);


        verticalLayout_12->addLayout(gridLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelRuntime = new QLabel(groupBoxSendFile);
        labelRuntime->setObjectName(QString::fromUtf8("labelRuntime"));
        labelRuntime->setEnabled(false);

        horizontalLayout_3->addWidget(labelRuntime);

        outputRuntime = new QLabel(groupBoxSendFile);
        outputRuntime->setObjectName(QString::fromUtf8("outputRuntime"));
        outputRuntime->setEnabled(false);

        horizontalLayout_3->addWidget(outputRuntime);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 4);

        verticalLayout_12->addLayout(horizontalLayout_3);


        verticalLayout_14->addWidget(groupBoxSendFile);

        layoutManualGCode = new QHBoxLayout();
        layoutManualGCode->setSpacing(6);
        layoutManualGCode->setObjectName(QString::fromUtf8("layoutManualGCode"));
        labelCommand = new QLabel(centralWidget);
        labelCommand->setObjectName(QString::fromUtf8("labelCommand"));
        labelCommand->setAlignment(Qt::AlignCenter);

        layoutManualGCode->addWidget(labelCommand);

        comboCommand = new QComboBox(centralWidget);
        comboCommand->setObjectName(QString::fromUtf8("comboCommand"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboCommand->sizePolicy().hasHeightForWidth());
        comboCommand->setSizePolicy(sizePolicy4);
        comboCommand->setMinimumSize(QSize(140, 0));
        comboCommand->setEditable(true);
        comboCommand->setMaxVisibleItems(12);

        layoutManualGCode->addWidget(comboCommand);


        verticalLayout_14->addLayout(layoutManualGCode);

        statusList = new QListWidget(centralWidget);
        statusList->setObjectName(QString::fromUtf8("statusList"));
        statusList->setEnabled(false);
        statusList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        statusList->setAutoScrollMargin(16);
        statusList->setSelectionMode(QAbstractItemView::NoSelection);
        statusList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        statusList->setMovement(QListView::Static);
        statusList->setProperty("isWrapping", QVariant(false));
        statusList->setResizeMode(QListView::Adjust);
        statusList->setLayoutMode(QListView::SinglePass);
        statusList->setWordWrap(false);

        verticalLayout_14->addWidget(statusList);


        horizontalLayout_8->addLayout(verticalLayout_14);

        verticalLayout_RightControls = new QVBoxLayout();
        verticalLayout_RightControls->setSpacing(6);
        verticalLayout_RightControls->setObjectName(QString::fromUtf8("verticalLayout_RightControls"));
        verticalLayout_RightControls->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_RightControls->setContentsMargins(-1, 2, -1, -1);
        gridLayout_CoodPositions = new QGridLayout();
        gridLayout_CoodPositions->setSpacing(6);
        gridLayout_CoodPositions->setObjectName(QString::fromUtf8("gridLayout_CoodPositions"));
        gridLayout_CoodPositions->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_CoodPositions->setContentsMargins(-1, 0, -1, -1);
        lblX = new QLabel(centralWidget);
        lblX->setObjectName(QString::fromUtf8("lblX"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lblX->sizePolicy().hasHeightForWidth());
        lblX->setSizePolicy(sizePolicy5);
        lblX->setMinimumSize(QSize(29, 0));
        lblX->setMaximumSize(QSize(16777215, 53));
        QFont font;
        font.setPointSize(18);
        lblX->setFont(font);
        lblX->setAlignment(Qt::AlignCenter);

        gridLayout_CoodPositions->addWidget(lblX, 1, 0, 1, 1);

        lcdMachNumberY = new QLCDNumber(centralWidget);
        lcdMachNumberY->setObjectName(QString::fromUtf8("lcdMachNumberY"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(lcdMachNumberY->sizePolicy().hasHeightForWidth());
        lcdMachNumberY->setSizePolicy(sizePolicy6);
        lcdMachNumberY->setMinimumSize(QSize(0, 40));
        lcdMachNumberY->setMaximumSize(QSize(16777215, 52));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdMachNumberY->setPalette(palette);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        lcdMachNumberY->setFont(font1);
        lcdMachNumberY->setFrameShadow(QFrame::Raised);
        lcdMachNumberY->setSmallDecimalPoint(true);
        lcdMachNumberY->setDigitCount(7);
        lcdMachNumberY->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdMachNumberY, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelWorkCoord = new QLabel(centralWidget);
        labelWorkCoord->setObjectName(QString::fromUtf8("labelWorkCoord"));

        horizontalLayout->addWidget(labelWorkCoord);

        outputUnitsWork = new QLabel(centralWidget);
        outputUnitsWork->setObjectName(QString::fromUtf8("outputUnitsWork"));

        horizontalLayout->addWidget(outputUnitsWork);


        gridLayout_CoodPositions->addLayout(horizontalLayout, 0, 2, 1, 1);

        lcdWorkNumberY = new QLCDNumber(centralWidget);
        lcdWorkNumberY->setObjectName(QString::fromUtf8("lcdWorkNumberY"));
        lcdWorkNumberY->setMaximumSize(QSize(16777215, 52));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdWorkNumberY->setPalette(palette1);
        lcdWorkNumberY->setFont(font1);
        lcdWorkNumberY->setFrameShadow(QFrame::Raised);
        lcdWorkNumberY->setSmallDecimalPoint(true);
        lcdWorkNumberY->setDigitCount(7);
        lcdWorkNumberY->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdWorkNumberY, 2, 2, 1, 1);

        lblY = new QLabel(centralWidget);
        lblY->setObjectName(QString::fromUtf8("lblY"));
        sizePolicy5.setHeightForWidth(lblY->sizePolicy().hasHeightForWidth());
        lblY->setSizePolicy(sizePolicy5);
        lblY->setMinimumSize(QSize(29, 0));
        lblY->setMaximumSize(QSize(16777215, 52));
        lblY->setFont(font);
        lblY->setAlignment(Qt::AlignCenter);

        gridLayout_CoodPositions->addWidget(lblY, 2, 0, 1, 1);

        lcdMachNumberX = new QLCDNumber(centralWidget);
        lcdMachNumberX->setObjectName(QString::fromUtf8("lcdMachNumberX"));
        sizePolicy6.setHeightForWidth(lcdMachNumberX->sizePolicy().hasHeightForWidth());
        lcdMachNumberX->setSizePolicy(sizePolicy6);
        lcdMachNumberX->setMinimumSize(QSize(0, 40));
        lcdMachNumberX->setMaximumSize(QSize(16777215, 52));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Light, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdMachNumberX->setPalette(palette2);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        font2.setKerning(true);
        lcdMachNumberX->setFont(font2);
        lcdMachNumberX->setFrameShadow(QFrame::Raised);
        lcdMachNumberX->setSmallDecimalPoint(true);
        lcdMachNumberX->setDigitCount(7);
        lcdMachNumberX->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdMachNumberX, 1, 1, 1, 1);

        lcdWorkNumberZ = new QLCDNumber(centralWidget);
        lcdWorkNumberZ->setObjectName(QString::fromUtf8("lcdWorkNumberZ"));
        lcdWorkNumberZ->setMaximumSize(QSize(16777215, 53));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Light, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdWorkNumberZ->setPalette(palette3);
        lcdWorkNumberZ->setFont(font1);
        lcdWorkNumberZ->setFrameShadow(QFrame::Raised);
        lcdWorkNumberZ->setSmallDecimalPoint(true);
        lcdWorkNumberZ->setDigitCount(7);
        lcdWorkNumberZ->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdWorkNumberZ, 3, 2, 1, 1);

        lcdMachNumberZ = new QLCDNumber(centralWidget);
        lcdMachNumberZ->setObjectName(QString::fromUtf8("lcdMachNumberZ"));
        sizePolicy6.setHeightForWidth(lcdMachNumberZ->sizePolicy().hasHeightForWidth());
        lcdMachNumberZ->setSizePolicy(sizePolicy6);
        lcdMachNumberZ->setMinimumSize(QSize(0, 40));
        lcdMachNumberZ->setMaximumSize(QSize(16777215, 52));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Light, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdMachNumberZ->setPalette(palette4);
        lcdMachNumberZ->setFont(font1);
        lcdMachNumberZ->setFrameShadow(QFrame::Raised);
        lcdMachNumberZ->setSmallDecimalPoint(true);
        lcdMachNumberZ->setDigitCount(7);
        lcdMachNumberZ->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdMachNumberZ, 3, 1, 1, 1);

        lcdWorkNumberX = new QLCDNumber(centralWidget);
        lcdWorkNumberX->setObjectName(QString::fromUtf8("lcdWorkNumberX"));
        lcdWorkNumberX->setMaximumSize(QSize(16777215, 53));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Light, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdWorkNumberX->setPalette(palette5);
        lcdWorkNumberX->setFont(font1);
        lcdWorkNumberX->setFrameShape(QFrame::Box);
        lcdWorkNumberX->setFrameShadow(QFrame::Raised);
        lcdWorkNumberX->setSmallDecimalPoint(true);
        lcdWorkNumberX->setDigitCount(7);
        lcdWorkNumberX->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdWorkNumberX, 1, 2, 1, 1);

        lblZ = new QLabel(centralWidget);
        lblZ->setObjectName(QString::fromUtf8("lblZ"));
        sizePolicy5.setHeightForWidth(lblZ->sizePolicy().hasHeightForWidth());
        lblZ->setSizePolicy(sizePolicy5);
        lblZ->setMinimumSize(QSize(29, 0));
        lblZ->setMaximumSize(QSize(16777215, 53));
        lblZ->setFont(font);
        lblZ->setAlignment(Qt::AlignCenter);

        gridLayout_CoodPositions->addWidget(lblZ, 3, 0, 1, 1);

        lblFourth = new QLabel(centralWidget);
        lblFourth->setObjectName(QString::fromUtf8("lblFourth"));
        sizePolicy5.setHeightForWidth(lblFourth->sizePolicy().hasHeightForWidth());
        lblFourth->setSizePolicy(sizePolicy5);
        lblFourth->setMinimumSize(QSize(29, 0));
        lblFourth->setMaximumSize(QSize(16777215, 52));
        lblFourth->setFont(font);
        lblFourth->setAlignment(Qt::AlignCenter);

        gridLayout_CoodPositions->addWidget(lblFourth, 4, 0, 1, 1);

        lcdWorkNumberFourth = new QLCDNumber(centralWidget);
        lcdWorkNumberFourth->setObjectName(QString::fromUtf8("lcdWorkNumberFourth"));
        lcdWorkNumberFourth->setMaximumSize(QSize(16777215, 52));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Light, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdWorkNumberFourth->setPalette(palette6);
        lcdWorkNumberFourth->setFont(font1);
        lcdWorkNumberFourth->setFrameShadow(QFrame::Raised);
        lcdWorkNumberFourth->setSmallDecimalPoint(true);
        lcdWorkNumberFourth->setDigitCount(7);
        lcdWorkNumberFourth->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdWorkNumberFourth, 4, 2, 1, 1);

        lcdMachNumberFourth = new QLCDNumber(centralWidget);
        lcdMachNumberFourth->setObjectName(QString::fromUtf8("lcdMachNumberFourth"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(lcdMachNumberFourth->sizePolicy().hasHeightForWidth());
        lcdMachNumberFourth->setSizePolicy(sizePolicy7);
        lcdMachNumberFourth->setMinimumSize(QSize(0, 40));
        lcdMachNumberFourth->setMaximumSize(QSize(16777215, 52));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Light, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Light, brush);
        lcdMachNumberFourth->setPalette(palette7);
        lcdMachNumberFourth->setFont(font1);
        lcdMachNumberFourth->setFrameShadow(QFrame::Raised);
        lcdMachNumberFourth->setLineWidth(1);
        lcdMachNumberFourth->setMidLineWidth(0);
        lcdMachNumberFourth->setSmallDecimalPoint(true);
        lcdMachNumberFourth->setDigitCount(7);
        lcdMachNumberFourth->setSegmentStyle(QLCDNumber::Filled);

        gridLayout_CoodPositions->addWidget(lcdMachNumberFourth, 4, 1, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        labelMachCoord = new QLabel(centralWidget);
        labelMachCoord->setObjectName(QString::fromUtf8("labelMachCoord"));

        horizontalLayout_11->addWidget(labelMachCoord);

        outputUnitsMachine = new QLabel(centralWidget);
        outputUnitsMachine->setObjectName(QString::fromUtf8("outputUnitsMachine"));
        outputUnitsMachine->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_11->addWidget(outputUnitsMachine);


        gridLayout_CoodPositions->addLayout(horizontalLayout_11, 0, 1, 1, 1);


        verticalLayout_RightControls->addLayout(gridLayout_CoodPositions);

        tabAxisVisualizer = new QTabWidget(centralWidget);
        tabAxisVisualizer->setObjectName(QString::fromUtf8("tabAxisVisualizer"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(tabAxisVisualizer->sizePolicy().hasHeightForWidth());
        tabAxisVisualizer->setSizePolicy(sizePolicy8);
        tabAxis = new QWidget();
        tabAxis->setObjectName(QString::fromUtf8("tabAxis"));
        verticalLayout_6 = new QVBoxLayout(tabAxis);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        DecXBtn = new QPushButton(tabAxis);
        DecXBtn->setObjectName(QString::fromUtf8("DecXBtn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/left.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        DecXBtn->setIcon(icon);
        DecXBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(DecXBtn, 3, 0, 1, 1);

        IncYBtn = new QPushButton(tabAxis);
        IncYBtn->setObjectName(QString::fromUtf8("IncYBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/up.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        IncYBtn->setIcon(icon1);
        IncYBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(IncYBtn, 0, 1, 1, 1);

        DecYBtn = new QPushButton(tabAxis);
        DecYBtn->setObjectName(QString::fromUtf8("DecYBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/down.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        DecYBtn->setIcon(icon2);
        DecYBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(DecYBtn, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(18, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        IncXBtn = new QPushButton(tabAxis);
        IncXBtn->setObjectName(QString::fromUtf8("IncXBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/right.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        IncXBtn->setIcon(icon3);
        IncXBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(IncXBtn, 3, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblFourthJog = new QLabel(tabAxis);
        lblFourthJog->setObjectName(QString::fromUtf8("lblFourthJog"));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        lblFourthJog->setFont(font3);
        lblFourthJog->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(lblFourthJog);


        gridLayout->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        DecFourthBtn = new QPushButton(tabAxis);
        DecFourthBtn->setObjectName(QString::fromUtf8("DecFourthBtn"));
        DecFourthBtn->setIcon(icon);
        DecFourthBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(DecFourthBtn, 5, 0, 1, 1);

        IncFourthBtn = new QPushButton(tabAxis);
        IncFourthBtn->setObjectName(QString::fromUtf8("IncFourthBtn"));
        IncFourthBtn->setIcon(icon3);
        IncFourthBtn->setIconSize(QSize(24, 24));

        gridLayout->addWidget(IncFourthBtn, 5, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 1, 1, 1);

        gridLayout->setColumnMinimumWidth(0, 50);
        gridLayout->setColumnMinimumWidth(1, 50);
        gridLayout->setColumnMinimumWidth(2, 50);

        horizontalLayout_13->addLayout(gridLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(30, -1, 30, -1);
        verticalSliderZJog = new QSlider(tabAxis);
        verticalSliderZJog->setObjectName(QString::fromUtf8("verticalSliderZJog"));
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(verticalSliderZJog->sizePolicy().hasHeightForWidth());
        verticalSliderZJog->setSizePolicy(sizePolicy9);
        verticalSliderZJog->setMaximum(80);
        verticalSliderZJog->setValue(40);
        verticalSliderZJog->setSliderPosition(40);
        verticalSliderZJog->setOrientation(Qt::Vertical);
        verticalSliderZJog->setInvertedAppearance(false);
        verticalSliderZJog->setInvertedControls(false);
        verticalSliderZJog->setTickPosition(QSlider::TicksBelow);

        verticalLayout_3->addWidget(verticalSliderZJog);

        currentZJogSliderDelta = new QLabel(tabAxis);
        currentZJogSliderDelta->setObjectName(QString::fromUtf8("currentZJogSliderDelta"));
        currentZJogSliderDelta->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(currentZJogSliderDelta);

        resultingZJogSliderPosition = new QLabel(tabAxis);
        resultingZJogSliderPosition->setObjectName(QString::fromUtf8("resultingZJogSliderPosition"));
        resultingZJogSliderPosition->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(resultingZJogSliderPosition);


        horizontalLayout_13->addLayout(verticalLayout_3);

        layoutZJog = new QVBoxLayout();
        layoutZJog->setSpacing(6);
        layoutZJog->setObjectName(QString::fromUtf8("layoutZJog"));
        IncZBtn = new QPushButton(tabAxis);
        IncZBtn->setObjectName(QString::fromUtf8("IncZBtn"));
        IncZBtn->setIcon(icon1);
        IncZBtn->setIconSize(QSize(24, 24));

        layoutZJog->addWidget(IncZBtn);

        lblZJog = new QLabel(tabAxis);
        lblZJog->setObjectName(QString::fromUtf8("lblZJog"));
        lblZJog->setFont(font3);
        lblZJog->setAlignment(Qt::AlignCenter);

        layoutZJog->addWidget(lblZJog);

        DecZBtn = new QPushButton(tabAxis);
        DecZBtn->setObjectName(QString::fromUtf8("DecZBtn"));
        DecZBtn->setIcon(icon2);
        DecZBtn->setIconSize(QSize(24, 24));

        layoutZJog->addWidget(DecZBtn);


        horizontalLayout_13->addLayout(layoutZJog);

        horizontalLayout_13->setStretch(0, 150);
        horizontalLayout_13->setStretch(2, 50);

        verticalLayout_6->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        chkRestoreAbsolute = new QCheckBox(tabAxis);
        chkRestoreAbsolute->setObjectName(QString::fromUtf8("chkRestoreAbsolute"));
        sizePolicy7.setHeightForWidth(chkRestoreAbsolute->sizePolicy().hasHeightForWidth());
        chkRestoreAbsolute->setSizePolicy(sizePolicy7);

        verticalLayout->addWidget(chkRestoreAbsolute);

        SpindleOn = new QCheckBox(tabAxis);
        SpindleOn->setObjectName(QString::fromUtf8("SpindleOn"));
        sizePolicy7.setHeightForWidth(SpindleOn->sizePolicy().hasHeightForWidth());
        SpindleOn->setSizePolicy(sizePolicy7);
        SpindleOn->setChecked(false);

        verticalLayout->addWidget(SpindleOn);


        horizontalLayout_12->addLayout(verticalLayout);

        verticalLayoutStepSize = new QVBoxLayout();
        verticalLayoutStepSize->setSpacing(6);
        verticalLayoutStepSize->setObjectName(QString::fromUtf8("verticalLayoutStepSize"));
        verticalLayoutStepSize->setContentsMargins(0, 4, 0, 5);
        lblStep = new QLabel(tabAxis);
        lblStep->setObjectName(QString::fromUtf8("lblStep"));
        QSizePolicy sizePolicy10(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(lblStep->sizePolicy().hasHeightForWidth());
        lblStep->setSizePolicy(sizePolicy10);

        verticalLayoutStepSize->addWidget(lblStep);

        comboStep = new QComboBox(tabAxis);
        comboStep->setObjectName(QString::fromUtf8("comboStep"));
        QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(comboStep->sizePolicy().hasHeightForWidth());
        comboStep->setSizePolicy(sizePolicy11);

        verticalLayoutStepSize->addWidget(comboStep);


        horizontalLayout_12->addLayout(verticalLayoutStepSize);

        horizontalLayout_12->setStretch(0, 200);

        verticalLayout_6->addLayout(horizontalLayout_12);

        tabAxisVisualizer->addTab(tabAxis, QString());
        tabVisualizer = new QWidget();
        tabVisualizer->setObjectName(QString::fromUtf8("tabVisualizer"));
        verticalLayout_5 = new QVBoxLayout(tabVisualizer);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        wgtVisualizer = new RenderArea(tabVisualizer);
        wgtVisualizer->setObjectName(QString::fromUtf8("wgtVisualizer"));
        wgtVisualizer->setEnabled(true);
        sizePolicy1.setHeightForWidth(wgtVisualizer->sizePolicy().hasHeightForWidth());
        wgtVisualizer->setSizePolicy(sizePolicy1);
        QPalette palette8;
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(244, 237, 187, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        wgtVisualizer->setPalette(palette8);
        wgtVisualizer->setAutoFillBackground(true);

        verticalLayout_5->addWidget(wgtVisualizer);

        tabAxisVisualizer->addTab(tabVisualizer, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBoxReset = new QGroupBox(tab);
        groupBoxReset->setObjectName(QString::fromUtf8("groupBoxReset"));
        groupBoxReset->setGeometry(QRect(10, 10, 152, 87));
        verticalLayout_9 = new QVBoxLayout(groupBoxReset);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btnResetGrbl = new QPushButton(groupBoxReset);
        btnResetGrbl->setObjectName(QString::fromUtf8("btnResetGrbl"));
        sizePolicy7.setHeightForWidth(btnResetGrbl->sizePolicy().hasHeightForWidth());
        btnResetGrbl->setSizePolicy(sizePolicy7);

        verticalLayout_2->addWidget(btnResetGrbl);

        btnUnlockGrbl = new QPushButton(groupBoxReset);
        btnUnlockGrbl->setObjectName(QString::fromUtf8("btnUnlockGrbl"));
        sizePolicy7.setHeightForWidth(btnUnlockGrbl->sizePolicy().hasHeightForWidth());
        btnUnlockGrbl->setSizePolicy(sizePolicy7);

        verticalLayout_2->addWidget(btnUnlockGrbl);


        verticalLayout_9->addLayout(verticalLayout_2);

        btnGRBL = new QPushButton(tab);
        btnGRBL->setObjectName(QString::fromUtf8("btnGRBL"));
        btnGRBL->setGeometry(QRect(170, 30, 131, 41));
        sizePolicy7.setHeightForWidth(btnGRBL->sizePolicy().hasHeightForWidth());
        btnGRBL->setSizePolicy(sizePolicy7);
        QFont font4;
        font4.setPointSize(8);
        btnGRBL->setFont(font4);
        tabAxisVisualizer->addTab(tab, QString());

        verticalLayout_RightControls->addWidget(tabAxisVisualizer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        btnSetHome = new QPushButton(centralWidget);
        btnSetHome->setObjectName(QString::fromUtf8("btnSetHome"));
        sizePolicy7.setHeightForWidth(btnSetHome->sizePolicy().hasHeightForWidth());
        btnSetHome->setSizePolicy(sizePolicy7);
        btnSetHome->setFont(font4);
        btnSetHome->setAutoFillBackground(false);

        horizontalLayout_7->addWidget(btnSetHome);

        btnGoHomeSafe = new QPushButton(centralWidget);
        btnGoHomeSafe->setObjectName(QString::fromUtf8("btnGoHomeSafe"));
        sizePolicy7.setHeightForWidth(btnGoHomeSafe->sizePolicy().hasHeightForWidth());
        btnGoHomeSafe->setSizePolicy(sizePolicy7);

        horizontalLayout_7->addWidget(btnGoHomeSafe);

        pushButtonRefreshPos = new QPushButton(centralWidget);
        pushButtonRefreshPos->setObjectName(QString::fromUtf8("pushButtonRefreshPos"));

        horizontalLayout_7->addWidget(pushButtonRefreshPos);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_RightControls->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_RightControls);

        horizontalLayout_8->setStretch(0, 4);
        horizontalLayout_8->setStretch(1, 5);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 972, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menuTools->addAction(actionOptions);
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabAxisVisualizer->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Grbl Controller", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        lblPort->setText(QApplication::translate("MainWindow", "Port name", 0, QApplication::UnicodeUTF8));
        btnOpenPort->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        label_br->setText(QApplication::translate("MainWindow", "Baud Rate", 0, QApplication::UnicodeUTF8));
        labelLastState->setText(QApplication::translate("MainWindow", "Last State:", 0, QApplication::UnicodeUTF8));
        outputLastState->setText(QString());
        groupBoxSendFile->setTitle(QApplication::translate("MainWindow", "Send File", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        openFile->setText(QApplication::translate("MainWindow", "Choose file", 0, QApplication::UnicodeUTF8));
        Begin->setText(QApplication::translate("MainWindow", "Begin", 0, QApplication::UnicodeUTF8));
        progressQueuedCommands->setFormat(QApplication::translate("MainWindow", "%v", 0, QApplication::UnicodeUTF8));
        labelFileSendProgress->setText(QApplication::translate("MainWindow", "File progress", 0, QApplication::UnicodeUTF8));
        labelQueuedCommands->setText(QApplication::translate("MainWindow", "Queued Commands", 0, QApplication::UnicodeUTF8));
        labelRuntime->setText(QApplication::translate("MainWindow", "Runtime:", 0, QApplication::UnicodeUTF8));
        outputRuntime->setText(QString());
        labelCommand->setText(QApplication::translate("MainWindow", "Command", 0, QApplication::UnicodeUTF8));
        lblX->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        labelWorkCoord->setText(QApplication::translate("MainWindow", "Work Coordinates", 0, QApplication::UnicodeUTF8));
        outputUnitsWork->setText(QString());
        lblY->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        lblZ->setText(QApplication::translate("MainWindow", "Z", 0, QApplication::UnicodeUTF8));
        lblFourth->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        labelMachCoord->setText(QApplication::translate("MainWindow", "Machine Coordinates", 0, QApplication::UnicodeUTF8));
        outputUnitsMachine->setText(QString());
        DecXBtn->setText(QString());
        IncYBtn->setText(QString());
        DecYBtn->setText(QString());
        IncXBtn->setText(QString());
        lblFourthJog->setText(QApplication::translate("MainWindow", "C Jog", 0, QApplication::UnicodeUTF8));
        DecFourthBtn->setText(QString());
        IncFourthBtn->setText(QString());
        currentZJogSliderDelta->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        resultingZJogSliderPosition->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        IncZBtn->setText(QString());
        lblZJog->setText(QApplication::translate("MainWindow", "Z Jog", 0, QApplication::UnicodeUTF8));
        DecZBtn->setText(QString());
        chkRestoreAbsolute->setText(QApplication::translate("MainWindow", "Absolute coordinates after adjust", 0, QApplication::UnicodeUTF8));
        SpindleOn->setText(QApplication::translate("MainWindow", "Spindle On", 0, QApplication::UnicodeUTF8));
        lblStep->setText(QApplication::translate("MainWindow", "Step Size           ", 0, QApplication::UnicodeUTF8));
        tabAxisVisualizer->setTabText(tabAxisVisualizer->indexOf(tabAxis), QApplication::translate("MainWindow", "Axis Control", 0, QApplication::UnicodeUTF8));
        tabAxisVisualizer->setTabText(tabAxisVisualizer->indexOf(tabVisualizer), QApplication::translate("MainWindow", "Visualizer", 0, QApplication::UnicodeUTF8));
        groupBoxReset->setTitle(QApplication::translate("MainWindow", "Reset Control", 0, QApplication::UnicodeUTF8));
        btnResetGrbl->setText(QApplication::translate("MainWindow", "Soft Reset Grbl", 0, QApplication::UnicodeUTF8));
        btnUnlockGrbl->setText(QApplication::translate("MainWindow", "Unlock Grbl", 0, QApplication::UnicodeUTF8));
        btnGRBL->setText(QApplication::translate("MainWindow", "GRBL Settings", 0, QApplication::UnicodeUTF8));
        tabAxisVisualizer->setTabText(tabAxisVisualizer->indexOf(tab), QApplication::translate("MainWindow", "Advanced", 0, QApplication::UnicodeUTF8));
        btnSetHome->setText(QApplication::translate("MainWindow", "Zero Position", 0, QApplication::UnicodeUTF8));
        btnGoHomeSafe->setText(QApplication::translate("MainWindow", "Go Home", 0, QApplication::UnicodeUTF8));
        pushButtonRefreshPos->setText(QApplication::translate("MainWindow", "Refresh Pos", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
