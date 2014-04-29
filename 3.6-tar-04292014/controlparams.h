#ifndef CONTROLPARAMS_H
#define CONTROLPARAMS_H

#include "definitions.h"

#define SHORT_WAIT_SEC 2
#define LONG_WAIT_SEC  100

class ControlParams
{
public:
    ControlParams();

public:
    int waitTime;
    double zJogRate;
    bool useMm;
    bool zRateLimit;
    double zRateLimitAmount;
    double xyRateAmount;
    bool useAggressivePreload;
    bool filterFileCommands;
    bool reducePrecision;
    int grblLineBufferLen;
    bool useFourAxis;
    int charSendDelayMs;
    char fourthAxisType;
    bool usePositionRequest;
    QString positionRequestType;
    int postionRequestTimeMilliSec;
    bool waitForJogToComplete;
};

#endif // CONTROLPARAMS_H
