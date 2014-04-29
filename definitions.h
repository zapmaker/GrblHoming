/****************************************************************
 * definitions.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QtGlobal>
#include <QString>
#include <QDateTime>
#include "atomicintbool.h"

#define DEFAULT_WAIT_TIME_SEC   100

#define DEFAULT_Z_JOG_RATE      260.0
#define DEFAULT_Z_LIMIT_RATE    100.0
#define DEFAULT_XY_RATE         2000.0

#define DEFAULT_GRBL_LINE_BUFFER_LEN    50
#define DEFAULT_CHAR_SEND_DELAY_MS      0

#define MM_IN_AN_INCH           25.4
#define PRE_HOME_Z_ADJ_MM       5.0

#define REQUEST_CURRENT_POS             "?"
#define SETTINGS_COMMAND_V08a           "$"
#define SETTINGS_COMMAND_V08c           "$$"
#define REQUEST_PARSER_STATE_V08c       "$G"
#define SET_UNLOCK_STATE_V08c           "$X"

#define REGEXP_SETTINGS_LINE    "(\\d+)\\s*=\\s*([\\w\\.]+)\\s*\\(([^\\)]*)\\)"

#define OPEN_BUTTON_TEXT                "Open"
#define CLOSE_BUTTON_TEXT               "Close / Reset"

#define LOG_MSG_TYPE_DIAG       "DIAG"
#define LOG_MSG_TYPE_STATUS     "STATUS"

/// LETARTARE   : one axis choice U or V or W or A or B or C
#define FOURTH_AXIS_U   'U'
#define FOURTH_AXIS_V   'V'
#define FOURTH_AXIS_W   'W'
/// <--
#define FOURTH_AXIS_A   'A'
#define FOURTH_AXIS_B   'B'
#define FOURTH_AXIS_C   'C'

#define PREQ_ALWAYS                 "always"
#define PREQ_ALWAYS_NO_IDLE_CHK     "alwaysWithoutIdleChk"
#define PREQ_NOT_WHEN_MANUAL        "notWhenManual"

#define DEFAULT_POS_REQ_FREQ_SEC    1.0
#define DEFAULT_POS_REQ_FREQ_MSEC   1000

extern AtomicIntBool g_enableDebugLog;

void status(const char *str, ...);
void diag(const char *str, ...);
void err(const char *str, ...);
void warn(const char *str, ...);
void info(const char *str, ...);

#endif // DEFINITIONS_H
