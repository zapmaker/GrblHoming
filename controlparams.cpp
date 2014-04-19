#include "controlparams.h"

ControlParams::ControlParams()
    :    waitTime(LONG_WAIT_SEC), zJogRate(DEFAULT_Z_JOG_RATE),
            useMm(true), zRateLimit(false), zRateLimitAmount(DEFAULT_Z_LIMIT_RATE),
            xyRateAmount(DEFAULT_XY_RATE),
            useAggressivePreload(false), filterFileCommands(false),
            reducePrecision(false), grblLineBufferLen(DEFAULT_GRBL_LINE_BUFFER_LEN),
            useFourAxis(false), charSendDelayMs(DEFAULT_CHAR_SEND_DELAY_MS)
{
}
