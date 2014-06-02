/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created: Mon 2. Jun 09:04:53 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_general;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *labelZJogRate;
    QLabel *labelWaitForResp;
    QSpinBox *spinResponseWaitSec;
    QDoubleSpinBox *doubleSpinZJogRate;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayoutExtras;
    QCheckBox *checkBoxUseMmManualCmds;
    QCheckBox *chkAggressivePreload;
    QCheckBox *checkBoxWaitForJogToComplete;
    QCheckBox *checkBoxEnableDebugLog;
    QWidget *tab_filtering;
    QGroupBox *groupZRateLimit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayoutRateLimit;
    QCheckBox *chkLimitZRate;
    QDoubleSpinBox *doubleSpinZRateLimit;
    QSpacerItem *horizontalSpacer;
    QLabel *labelZRateLimit;
    QLabel *labelXYRate;
    QDoubleSpinBox *doubleSpinXYRate;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox;
    QCheckBox *chkFilterFileCommands;
    QCheckBox *checkBoxReducePrecForLongLines;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *spinBoxCharSendDelay;
    QSpinBox *spinBoxGrblLineBufferSize;
    QWidget *tab_axis;
    QGroupBox *groupBoxAxis;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkInvX;
    QCheckBox *chkInvY;
    QCheckBox *chkInvZ;
    QCheckBox *chkInvFourth;
    QGroupBox *groupBoxFourthAxis;
    QRadioButton *radioButtonFourthAxisA;
    QRadioButton *radioButtonFourthAxisB;
    QRadioButton *radioButtonFourthAxisC;
    QRadioButton *radioButtonFourthAxisU;
    QRadioButton *radioButtonFourthAxisV;
    QRadioButton *radioButtonFourthAxisW;
    QCheckBox *checkBoxFourAxis;
    QWidget *tab_display;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBoxPositionReportEnabled;
    QGroupBox *groupBox_ReqPos;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_ReqAlways;
    QRadioButton *radioButton_ReqAlwaysNoIdleCheck;
    QRadioButton *radioButton_ReqNotDuringManual;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ReqFreq;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *doubleSpinBoxPosRequestFreqSec;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QString::fromUtf8("Options"));
        Options->resize(521, 317);
        tabWidget = new QTabWidget(Options);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 501, 261));
        tab_general = new QWidget();
        tab_general->setObjectName(QString::fromUtf8("tab_general"));
        gridLayoutWidget_2 = new QWidget(tab_general);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 146, 451, 71));
        gridLayout = new QGridLayout(gridLayoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelZJogRate = new QLabel(gridLayoutWidget_2);
        labelZJogRate->setObjectName(QString::fromUtf8("labelZJogRate"));

        gridLayout->addWidget(labelZJogRate, 2, 0, 1, 1);

        labelWaitForResp = new QLabel(gridLayoutWidget_2);
        labelWaitForResp->setObjectName(QString::fromUtf8("labelWaitForResp"));

        gridLayout->addWidget(labelWaitForResp, 1, 0, 1, 1);

        spinResponseWaitSec = new QSpinBox(gridLayoutWidget_2);
        spinResponseWaitSec->setObjectName(QString::fromUtf8("spinResponseWaitSec"));
        spinResponseWaitSec->setMinimum(1);
        spinResponseWaitSec->setMaximum(1000);
        spinResponseWaitSec->setValue(60);

        gridLayout->addWidget(spinResponseWaitSec, 1, 1, 1, 1);

        doubleSpinZJogRate = new QDoubleSpinBox(gridLayoutWidget_2);
        doubleSpinZJogRate->setObjectName(QString::fromUtf8("doubleSpinZJogRate"));
        doubleSpinZJogRate->setAccelerated(true);
        doubleSpinZJogRate->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        doubleSpinZJogRate->setDecimals(3);
        doubleSpinZJogRate->setMinimum(0.1);
        doubleSpinZJogRate->setMaximum(9999.99);
        doubleSpinZJogRate->setSingleStep(1);
        doubleSpinZJogRate->setValue(260);

        gridLayout->addWidget(doubleSpinZJogRate, 2, 1, 1, 1);

        gridLayout->setColumnStretch(0, 2);
        gridLayout->setColumnStretch(1, 1);
        verticalLayoutWidget_2 = new QWidget(tab_general);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 451, 121));
        verticalLayoutExtras = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayoutExtras->setObjectName(QString::fromUtf8("verticalLayoutExtras"));
        verticalLayoutExtras->setContentsMargins(0, 0, 0, 0);
        checkBoxUseMmManualCmds = new QCheckBox(verticalLayoutWidget_2);
        checkBoxUseMmManualCmds->setObjectName(QString::fromUtf8("checkBoxUseMmManualCmds"));

        verticalLayoutExtras->addWidget(checkBoxUseMmManualCmds);

        chkAggressivePreload = new QCheckBox(verticalLayoutWidget_2);
        chkAggressivePreload->setObjectName(QString::fromUtf8("chkAggressivePreload"));

        verticalLayoutExtras->addWidget(chkAggressivePreload);

        checkBoxWaitForJogToComplete = new QCheckBox(verticalLayoutWidget_2);
        checkBoxWaitForJogToComplete->setObjectName(QString::fromUtf8("checkBoxWaitForJogToComplete"));
        checkBoxWaitForJogToComplete->setEnabled(false);

        verticalLayoutExtras->addWidget(checkBoxWaitForJogToComplete);

        checkBoxEnableDebugLog = new QCheckBox(verticalLayoutWidget_2);
        checkBoxEnableDebugLog->setObjectName(QString::fromUtf8("checkBoxEnableDebugLog"));

        verticalLayoutExtras->addWidget(checkBoxEnableDebugLog);

        tabWidget->addTab(tab_general, QString());
        tab_filtering = new QWidget();
        tab_filtering->setObjectName(QString::fromUtf8("tab_filtering"));
        groupZRateLimit = new QGroupBox(tab_filtering);
        groupZRateLimit->setObjectName(QString::fromUtf8("groupZRateLimit"));
        groupZRateLimit->setGeometry(QRect(10, 10, 471, 81));
        gridLayoutWidget = new QWidget(groupZRateLimit);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 451, 53));
        gridLayoutRateLimit = new QGridLayout(gridLayoutWidget);
        gridLayoutRateLimit->setObjectName(QString::fromUtf8("gridLayoutRateLimit"));
        gridLayoutRateLimit->setContentsMargins(0, 0, 0, 0);
        chkLimitZRate = new QCheckBox(gridLayoutWidget);
        chkLimitZRate->setObjectName(QString::fromUtf8("chkLimitZRate"));

        gridLayoutRateLimit->addWidget(chkLimitZRate, 0, 0, 1, 1);

        doubleSpinZRateLimit = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinZRateLimit->setObjectName(QString::fromUtf8("doubleSpinZRateLimit"));
        doubleSpinZRateLimit->setAccelerated(true);
        doubleSpinZRateLimit->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        doubleSpinZRateLimit->setDecimals(3);
        doubleSpinZRateLimit->setMinimum(0.1);
        doubleSpinZRateLimit->setMaximum(9999.99);
        doubleSpinZRateLimit->setSingleStep(1);
        doubleSpinZRateLimit->setValue(100);

        gridLayoutRateLimit->addWidget(doubleSpinZRateLimit, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutRateLimit->addItem(horizontalSpacer, 0, 1, 1, 1);

        labelZRateLimit = new QLabel(gridLayoutWidget);
        labelZRateLimit->setObjectName(QString::fromUtf8("labelZRateLimit"));

        gridLayoutRateLimit->addWidget(labelZRateLimit, 0, 2, 1, 1);

        labelXYRate = new QLabel(gridLayoutWidget);
        labelXYRate->setObjectName(QString::fromUtf8("labelXYRate"));

        gridLayoutRateLimit->addWidget(labelXYRate, 1, 2, 1, 1);

        doubleSpinXYRate = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinXYRate->setObjectName(QString::fromUtf8("doubleSpinXYRate"));
        doubleSpinXYRate->setDecimals(2);
        doubleSpinXYRate->setMinimum(0.1);
        doubleSpinXYRate->setMaximum(1e+06);
        doubleSpinXYRate->setValue(2000);

        gridLayoutRateLimit->addWidget(doubleSpinXYRate, 1, 3, 1, 1);

        layoutWidget_2 = new QWidget(tab_filtering);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 200, 261, 24));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        groupBox = new QGroupBox(tab_filtering);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 100, 461, 61));
        chkFilterFileCommands = new QCheckBox(groupBox);
        chkFilterFileCommands->setObjectName(QString::fromUtf8("chkFilterFileCommands"));
        chkFilterFileCommands->setGeometry(QRect(30, 20, 431, 17));
        checkBoxReducePrecForLongLines = new QCheckBox(groupBox);
        checkBoxReducePrecForLongLines->setObjectName(QString::fromUtf8("checkBoxReducePrecForLongLines"));
        checkBoxReducePrecForLongLines->setGeometry(QRect(30, 40, 431, 17));
        layoutWidget = new QWidget(tab_filtering);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 170, 261, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        spinBoxCharSendDelay = new QSpinBox(tab_filtering);
        spinBoxCharSendDelay->setObjectName(QString::fromUtf8("spinBoxCharSendDelay"));
        spinBoxCharSendDelay->setGeometry(QRect(270, 200, 50, 22));
        spinBoxCharSendDelay->setMaximum(20);
        spinBoxCharSendDelay->setValue(10);
        spinBoxGrblLineBufferSize = new QSpinBox(tab_filtering);
        spinBoxGrblLineBufferSize->setObjectName(QString::fromUtf8("spinBoxGrblLineBufferSize"));
        spinBoxGrblLineBufferSize->setGeometry(QRect(270, 170, 50, 22));
        spinBoxGrblLineBufferSize->setValue(50);
        tabWidget->addTab(tab_filtering, QString());
        tab_axis = new QWidget();
        tab_axis->setObjectName(QString::fromUtf8("tab_axis"));
        groupBoxAxis = new QGroupBox(tab_axis);
        groupBoxAxis->setObjectName(QString::fromUtf8("groupBoxAxis"));
        groupBoxAxis->setGeometry(QRect(10, 111, 451, 60));
        horizontalLayoutWidget = new QWidget(groupBoxAxis);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 431, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        chkInvX = new QCheckBox(horizontalLayoutWidget);
        chkInvX->setObjectName(QString::fromUtf8("chkInvX"));

        horizontalLayout->addWidget(chkInvX);

        chkInvY = new QCheckBox(horizontalLayoutWidget);
        chkInvY->setObjectName(QString::fromUtf8("chkInvY"));

        horizontalLayout->addWidget(chkInvY);

        chkInvZ = new QCheckBox(horizontalLayoutWidget);
        chkInvZ->setObjectName(QString::fromUtf8("chkInvZ"));

        horizontalLayout->addWidget(chkInvZ);

        chkInvFourth = new QCheckBox(horizontalLayoutWidget);
        chkInvFourth->setObjectName(QString::fromUtf8("chkInvFourth"));

        horizontalLayout->addWidget(chkInvFourth);

        groupBoxFourthAxis = new QGroupBox(tab_axis);
        groupBoxFourthAxis->setObjectName(QString::fromUtf8("groupBoxFourthAxis"));
        groupBoxFourthAxis->setGeometry(QRect(10, 41, 451, 51));
        radioButtonFourthAxisA = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisA->setObjectName(QString::fromUtf8("radioButtonFourthAxisA"));
        radioButtonFourthAxisA->setGeometry(QRect(10, 22, 50, 17));
        radioButtonFourthAxisA->setChecked(true);
        radioButtonFourthAxisB = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisB->setObjectName(QString::fromUtf8("radioButtonFourthAxisB"));
        radioButtonFourthAxisB->setGeometry(QRect(80, 22, 50, 17));
        radioButtonFourthAxisC = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisC->setObjectName(QString::fromUtf8("radioButtonFourthAxisC"));
        radioButtonFourthAxisC->setGeometry(QRect(150, 22, 50, 17));
        radioButtonFourthAxisC->setContextMenuPolicy(Qt::PreventContextMenu);
        radioButtonFourthAxisU = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisU->setObjectName(QString::fromUtf8("radioButtonFourthAxisU"));
        radioButtonFourthAxisU->setGeometry(QRect(240, 20, 50, 21));
        radioButtonFourthAxisU->setContextMenuPolicy(Qt::PreventContextMenu);
        radioButtonFourthAxisV = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisV->setObjectName(QString::fromUtf8("radioButtonFourthAxisV"));
        radioButtonFourthAxisV->setGeometry(QRect(310, 22, 50, 17));
        radioButtonFourthAxisV->setContextMenuPolicy(Qt::PreventContextMenu);
        radioButtonFourthAxisW = new QRadioButton(groupBoxFourthAxis);
        radioButtonFourthAxisW->setObjectName(QString::fromUtf8("radioButtonFourthAxisW"));
        radioButtonFourthAxisW->setGeometry(QRect(380, 22, 50, 17));
        radioButtonFourthAxisW->setContextMenuPolicy(Qt::PreventContextMenu);
        checkBoxFourAxis = new QCheckBox(tab_axis);
        checkBoxFourAxis->setObjectName(QString::fromUtf8("checkBoxFourAxis"));
        checkBoxFourAxis->setGeometry(QRect(10, 11, 421, 17));
        tabWidget->addTab(tab_axis, QString());
        tab_display = new QWidget();
        tab_display->setObjectName(QString::fromUtf8("tab_display"));
        verticalLayoutWidget_3 = new QWidget(tab_display);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 481, 141));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBoxPositionReportEnabled = new QCheckBox(verticalLayoutWidget_3);
        checkBoxPositionReportEnabled->setObjectName(QString::fromUtf8("checkBoxPositionReportEnabled"));

        verticalLayout_2->addWidget(checkBoxPositionReportEnabled);

        groupBox_ReqPos = new QGroupBox(verticalLayoutWidget_3);
        groupBox_ReqPos->setObjectName(QString::fromUtf8("groupBox_ReqPos"));
        verticalLayoutWidget = new QWidget(groupBox_ReqPos);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 461, 93));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_ReqAlways = new QRadioButton(verticalLayoutWidget);
        radioButton_ReqAlways->setObjectName(QString::fromUtf8("radioButton_ReqAlways"));

        verticalLayout->addWidget(radioButton_ReqAlways);

        radioButton_ReqAlwaysNoIdleCheck = new QRadioButton(verticalLayoutWidget);
        radioButton_ReqAlwaysNoIdleCheck->setObjectName(QString::fromUtf8("radioButton_ReqAlwaysNoIdleCheck"));

        verticalLayout->addWidget(radioButton_ReqAlwaysNoIdleCheck);

        radioButton_ReqNotDuringManual = new QRadioButton(verticalLayoutWidget);
        radioButton_ReqNotDuringManual->setObjectName(QString::fromUtf8("radioButton_ReqNotDuringManual"));

        verticalLayout->addWidget(radioButton_ReqNotDuringManual);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_ReqFreq = new QLabel(verticalLayoutWidget);
        label_ReqFreq->setObjectName(QString::fromUtf8("label_ReqFreq"));

        horizontalLayout_3->addWidget(label_ReqFreq);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        doubleSpinBoxPosRequestFreqSec = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBoxPosRequestFreqSec->setObjectName(QString::fromUtf8("doubleSpinBoxPosRequestFreqSec"));
        doubleSpinBoxPosRequestFreqSec->setMinimum(0.5);
        doubleSpinBoxPosRequestFreqSec->setMaximum(10);
        doubleSpinBoxPosRequestFreqSec->setSingleStep(0.5);
        doubleSpinBoxPosRequestFreqSec->setValue(1);

        horizontalLayout_3->addWidget(doubleSpinBoxPosRequestFreqSec);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBox_ReqPos);

        tabWidget->addTab(tab_display, QString());
        buttonBox = new QDialogButtonBox(Options);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(320, 280, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(Options);
        QObject::connect(buttonBox, SIGNAL(accepted()), Options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Options, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QDialog *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", 0, QApplication::UnicodeUTF8));
        labelZJogRate->setText(QApplication::translate("Options", "Z-Jog Rate (inches or mm/min)", 0, QApplication::UnicodeUTF8));
        labelWaitForResp->setText(QApplication::translate("Options", "Seconds to Wait for Response", 0, QApplication::UnicodeUTF8));
        checkBoxUseMmManualCmds->setText(QApplication::translate("Options", "Use millimeters when sending manual commands (v0.8c+ only)", 0, QApplication::UnicodeUTF8));
        chkAggressivePreload->setText(QApplication::translate("Options", "Use aggressive preload strategy for Grbl", 0, QApplication::UnicodeUTF8));
        checkBoxWaitForJogToComplete->setText(QApplication::translate("Options", "Wait for each jog/manual command to complete (future feature)", 0, QApplication::UnicodeUTF8));
        checkBoxEnableDebugLog->setText(QApplication::translate("Options", "Write debugging log to home folder (requires restart)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_general), QApplication::translate("Options", "General", 0, QApplication::UnicodeUTF8));
        groupZRateLimit->setTitle(QApplication::translate("Options", "Z Rate Limiting", 0, QApplication::UnicodeUTF8));
        chkLimitZRate->setText(QApplication::translate("Options", "Limit Z Rate", 0, QApplication::UnicodeUTF8));
        labelZRateLimit->setText(QApplication::translate("Options", "Z-Rate Limit (inches or mm/min)", 0, QApplication::UnicodeUTF8));
        labelXYRate->setText(QApplication::translate("Options", "XY Rate (inches or mm/min)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Options", "Character send delay ms", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Options", "Command Filtering", 0, QApplication::UnicodeUTF8));
        chkFilterFileCommands->setText(QApplication::translate("Options", "Filter file commands before sending", 0, QApplication::UnicodeUTF8));
        checkBoxReducePrecForLongLines->setText(QApplication::translate("Options", "Selectively reduce precision for excessively long lines", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Options", "Grbl Line Buffer Size", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_filtering), QApplication::translate("Options", "Filtering", 0, QApplication::UnicodeUTF8));
        groupBoxAxis->setTitle(QApplication::translate("Options", "Invert Axis", 0, QApplication::UnicodeUTF8));
        chkInvX->setText(QApplication::translate("Options", "X Axis", 0, QApplication::UnicodeUTF8));
        chkInvY->setText(QApplication::translate("Options", "Y Axis", 0, QApplication::UnicodeUTF8));
        chkInvZ->setText(QApplication::translate("Options", "Z Axis", 0, QApplication::UnicodeUTF8));
        chkInvFourth->setText(QApplication::translate("Options", "Fourth Axis", 0, QApplication::UnicodeUTF8));
        groupBoxFourthAxis->setTitle(QApplication::translate("Options", "Selecting the Fourth axis", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisA->setText(QApplication::translate("Options", "A", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisB->setText(QApplication::translate("Options", "B", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisC->setText(QApplication::translate("Options", "C", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisU->setText(QApplication::translate("Options", "U", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisV->setText(QApplication::translate("Options", "V", 0, QApplication::UnicodeUTF8));
        radioButtonFourthAxisW->setText(QApplication::translate("Options", "W", 0, QApplication::UnicodeUTF8));
        checkBoxFourAxis->setText(QApplication::translate("Options", "Enable 4-axis mode", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_axis), QApplication::translate("Options", "Axis", 0, QApplication::UnicodeUTF8));
        checkBoxPositionReportEnabled->setText(QApplication::translate("Options", "Enable position request and report", 0, QApplication::UnicodeUTF8));
        groupBox_ReqPos->setTitle(QApplication::translate("Options", "Position Request", 0, QApplication::UnicodeUTF8));
        radioButton_ReqAlways->setText(QApplication::translate("Options", "Always Request (most reliable/slightly slower jogging)", 0, QApplication::UnicodeUTF8));
        radioButton_ReqAlwaysNoIdleCheck->setText(QApplication::translate("Options", "Always Request but without Idle Check (fast jog/manual operations)", 0, QApplication::UnicodeUTF8));
        radioButton_ReqNotDuringManual->setText(QApplication::translate("Options", "Not during manual control (no position update during jog/manual)", 0, QApplication::UnicodeUTF8));
        label_ReqFreq->setText(QApplication::translate("Options", "Request frequency (seconds)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_display), QApplication::translate("Options", "Display", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
