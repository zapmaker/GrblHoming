/****************************************************************
 * options.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    connect(ui->checkBoxUseMmManualCmds,SIGNAL(toggled(bool)),this,SLOT(toggleUseMm(bool)));
    connect(ui->chkLimitZRate,SIGNAL(toggled(bool)),this,SLOT(toggleLimitZRate(bool)));
    connect(ui->checkBoxFourAxis,SIGNAL(toggled(bool)),this,SLOT(toggleFourAxis(bool)));

    QSettings settings;

    QString invX = settings.value(SETTINGS_INVERSE_X, "false").value<QString>();
    QString invY = settings.value(SETTINGS_INVERSE_Y, "false").value<QString>();
    QString invZ = settings.value(SETTINGS_INVERSE_Z, "false").value<QString>();

	QString invC = settings.value(SETTINGS_INVERSE_C, "false").value<QString>();
	ui->chkInvC->setChecked(invC == "true");
    ui->chkInvX->setChecked(invX == "true");
    ui->chkInvY->setChecked(invY == "true");
    ui->chkInvZ->setChecked(invZ == "true");

    // enable logging by default
    QString enDebugLog = settings.value(SETTINGS_ENABLE_DEBUG_LOG, "true").value<QString>();
    // default aggressive preload behavior to 'true'!
    QString enAggressivePreload = settings.value(SETTINGS_USE_AGGRESSIVE_PRELOAD, "true").value<QString>();
    QString useMmManualCmds = settings.value(SETTINGS_USE_MM_FOR_MANUAL_CMDS, "true").value<QString>();
    QString enFourAxis = settings.value(SETTINGS_FOUR_AXIS, "false").value<QString>();

    if (enFourAxis == "false")
    {
        ui->chkInvC->hide();
        ui->chkInvC->setAttribute(Qt::WA_DontShowOnScreen, true);
    }
    else
    {
        ui->chkInvC->show();
        ui->chkInvC->setAttribute(Qt::WA_DontShowOnScreen, false);
    }

    ui->checkBoxEnableDebugLog->setChecked(enDebugLog == "true");
    ui->chkAggressivePreload->setChecked(enAggressivePreload == "true");
    ui->checkBoxUseMmManualCmds->setChecked(useMmManualCmds == "true");
    ui->checkBoxFourAxis->setChecked(enFourAxis == "true");

    int waitTime = settings.value(SETTINGS_RESPONSE_WAIT_TIME, DEFAULT_WAIT_TIME_SEC).value<int>();
    ui->spinResponseWaitSec->setValue(waitTime);

    double zJogRate = settings.value(SETTINGS_Z_JOG_RATE, DEFAULT_Z_JOG_RATE).value<double>();
    ui->doubleSpinZJogRate->setValue(zJogRate);

    QString zRateLimit = settings.value(SETTINGS_Z_RATE_LIMIT, "false").value<QString>();
    ui->chkLimitZRate->setChecked(zRateLimit == "true");

    double zRateLimitAmount = settings.value(SETTINGS_Z_RATE_LIMIT_AMOUNT, DEFAULT_Z_LIMIT_RATE).value<double>();
    ui->doubleSpinZRateLimit->setValue(zRateLimitAmount);
    double xyRateAmount = settings.value(SETTINGS_XY_RATE_AMOUNT, DEFAULT_XY_RATE).value<double>();
    ui->doubleSpinXYRate->setValue(xyRateAmount);

    if (!ui->chkLimitZRate->isChecked())
    {
        ui->doubleSpinZRateLimit->setEnabled(false);
        ui->doubleSpinXYRate->setEnabled(false);
    }

    QString ffCmd = settings.value(SETTINGS_FILTER_FILE_COMMANDS, "false").value<QString>();
    ui->chkFilterFileCommands->setChecked(ffCmd == "true");
    QString rPrecision = settings.value(SETTINGS_REDUCE_PREC_FOR_LONG_LINES, "false").value<QString>();
    ui->checkBoxReducePrecForLongLines->setChecked(rPrecision == "true");
    ui->spinBoxGrblLineBufferSize->setValue(settings.value(SETTINGS_GRBL_LINE_BUFFER_LEN, DEFAULT_GRBL_LINE_BUFFER_LEN).value<int>());
    ui->spinBoxCharSendDelay->setValue(settings.value(SETTINGS_CHAR_SEND_DELAY_MS, DEFAULT_CHAR_SEND_DELAY_MS).value<int>());
}

Options::~Options()
{
    delete ui;
}

void Options::accept()
{
    QSettings settings;

    settings.setValue(SETTINGS_INVERSE_X, ui->chkInvX->isChecked());
    settings.setValue(SETTINGS_INVERSE_Y, ui->chkInvY->isChecked());
    settings.setValue(SETTINGS_INVERSE_Z, ui->chkInvZ->isChecked());
	settings.setValue(SETTINGS_INVERSE_C, ui->chkInvC->isChecked());
    settings.setValue(SETTINGS_ENABLE_DEBUG_LOG, ui->checkBoxEnableDebugLog->isChecked());
    settings.setValue(SETTINGS_USE_AGGRESSIVE_PRELOAD, ui->chkAggressivePreload->isChecked());
    settings.setValue(SETTINGS_USE_MM_FOR_MANUAL_CMDS, ui->checkBoxUseMmManualCmds->isChecked());
    settings.setValue(SETTINGS_FOUR_AXIS, ui->checkBoxFourAxis->isChecked());

    settings.setValue(SETTINGS_RESPONSE_WAIT_TIME, ui->spinResponseWaitSec->value());
    settings.setValue(SETTINGS_Z_JOG_RATE, ui->doubleSpinZJogRate->value());

    settings.setValue(SETTINGS_Z_RATE_LIMIT, ui->chkLimitZRate->isChecked());
    settings.setValue(SETTINGS_Z_RATE_LIMIT_AMOUNT, ui->doubleSpinZRateLimit->value());
    settings.setValue(SETTINGS_XY_RATE_AMOUNT, ui->doubleSpinXYRate->value());

    settings.setValue(SETTINGS_FILTER_FILE_COMMANDS, ui->chkFilterFileCommands->isChecked());
    settings.setValue(SETTINGS_REDUCE_PREC_FOR_LONG_LINES, ui->checkBoxReducePrecForLongLines->isChecked());
    settings.setValue(SETTINGS_GRBL_LINE_BUFFER_LEN, ui->spinBoxGrblLineBufferSize->value());
    settings.setValue(SETTINGS_CHAR_SEND_DELAY_MS, ui->spinBoxCharSendDelay->value());

    connect(this, SIGNAL(setSettings()), parentWidget(), SLOT(setSettings()));

    emit setSettings();
    this->close();
}

void Options::toggleUseMm(bool useMm)
{
    double zJogRate = ui->doubleSpinZJogRate->value();
    double zRateLimit = ui->doubleSpinZRateLimit->value();
    double xyRate = ui->doubleSpinXYRate->value();

    if (useMm)
    {
        ui->doubleSpinZJogRate->setValue(zJogRate * MM_IN_AN_INCH);
        ui->doubleSpinZRateLimit->setValue(zRateLimit * MM_IN_AN_INCH);
        ui->doubleSpinXYRate->setValue(xyRate * MM_IN_AN_INCH);
    }
    else
    {
        ui->doubleSpinZJogRate->setValue(zJogRate / MM_IN_AN_INCH);
        ui->doubleSpinZRateLimit->setValue(zRateLimit / MM_IN_AN_INCH);
        ui->doubleSpinXYRate->setValue(xyRate / MM_IN_AN_INCH);
    }
}

void Options::toggleLimitZRate(bool limitZ)
{
    ui->doubleSpinZRateLimit->setEnabled(limitZ);
    ui->doubleSpinXYRate->setEnabled(limitZ);
}

void Options::toggleFourAxis(bool four)
{
    if (four)
    {
        ui->chkInvC->show();
        ui->chkInvC->setAttribute(Qt::WA_DontShowOnScreen, false);
    }
    else
    {
        ui->chkInvC->hide();
        ui->chkInvC->setAttribute(Qt::WA_DontShowOnScreen, true);
    }

}
