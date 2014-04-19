/****************************************************************
 * rs232.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "rs232.h"
#include <QObject>

RS232::RS232()
    : port(NULL), detectedEOL(0), charSendDelayMs(DEFAULT_CHAR_SEND_DELAY_MS)
{
}

bool RS232::OpenComport(QString commPortStr, QString baudRate)
{
    if (port != NULL)
        CloseComport();

    bool ok;
    BaudRateType baud = (BaudRateType)baudRate.toInt(&ok);
    if (!ok)
    {
        baud = BAUD9600;
    }
    else
    {
        int possibleBaudRates[] = {BAUD110,BAUD300,BAUD600,BAUD1200,BAUD2400,BAUD4800,BAUD9600,BAUD19200,BAUD38400,BAUD57600,BAUD115200};
        int pbrCount = sizeof possibleBaudRates / sizeof possibleBaudRates[0];

        bool found = false;
        for (int i = 0; i < pbrCount; i++)
        {
            if (baud == possibleBaudRates[i])
            {
                found = true;
                break;
            }
        }
        if (!found)
            baud = BAUD9600;
    }

    PortSettings settings = {baud, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};

    port = new QextSerialPort(commPortStr, settings, QextSerialPort::Polling);

    port->open(QIODevice::ReadWrite);

    return port->isOpen();
}


int RS232::PollComport(char *buf, int size)
{
    if (port == NULL || !port->isOpen())
        return 0;

    int n = port->bytesAvailable();
    if (!n)
        return 0;

    n = port->read(buf, size);
    return(n);
}

// This is different than QIoDevice.readline() - this method only returns data if it has a full line in the
// input buffer by peeking at the buffer. It never removes items unless it can remove a full line.
int RS232::PollComportLine(char *buf, int size)
{
    if (port == NULL || !port->isOpen())
        return 0;

    int n = port->bytesAvailable();
    if (!n)
        return 0;

    n = port->peek(buf, size);
    if (n <= 0)
        return n;

    //printf("PEEK: %d out of %d\n", n, size);
    if (detectedEOL == 0)
    {
        // algorithm assumes we received both eol chars if there are two in this peek
        int pos = 0;
        char firstEOL = 0;
        char secondEOL = 0;
        for (int i = 0; i < n; i++)
        {
            char b = buf[i];
            if (b == '\n' || b == '\r')
            {
                if (firstEOL == 0)
                {
                    firstEOL = b;
                    pos = i;
                }
                else if ((pos + 1) == i)
                {
                    secondEOL = b;
                    break;
                }
                else
                    break;
            }
        }

        if (firstEOL != 0)
        {
            if (secondEOL != 0)
            {
                detectedEOL = secondEOL;
                detectedLineFeed = firstEOL;
                detectedLineFeed += secondEOL;
            }
            else
            {
                detectedEOL = firstEOL;
                detectedLineFeed = firstEOL;
            }
        }
    }

    int toRead = 0;
    if (detectedEOL)
    {
        for (int i = 0; i < n; i++)
        {
            char b = buf[i];
            if (b == detectedEOL)
            {
                toRead = i + 1;
                break;
            }
        }
    }

    // let's hope the serial subsystem's read buffer is big enough to find a linefeed
    if (!toRead)
    {
        return 0;
    }

    n = port->read(buf, toRead);

    return n;
}

int RS232::SendBuf(const char *buf, int size)
{
    if (port == NULL || !port->isOpen())
        return 0;
/// LETARTARE  for test
//err(buf) ;
    if (size <= 0)
    {
        err( qPrintable(QObject::tr("Unexpected: Told to send %d bytes\n")), size) ;
        return 1;
    }

    char b[300] = {0};
    memcpy(b, buf, size);
#ifdef DIAG
    printf("Sending to port %s [%s]:", port->portName().toLocal8Bit().constData(), b);
    for (int x= 0; x < size; x++)
    {
        printf("%02X ", buf[x]);
    }
    printf("\n");
    fflush(stdout);
#endif

    port->waitForBytesWritten(-1);// this usually doesn't do anything, but let's put it here in case

#if 1
    // On very fast PCs running Windows we have to slow down the sending of bytes to grbl
    // because grbl loses bytes due to its interrupt service routine (ISR) taking too many clock
    // cycles away from serial handling.
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result = port->write(&buf[i], 1);
        if (result == 0)
        {
            err("Unable to write bytes to port probably due to outgoing queue full. Write data lost!");
            break;
        }
        else if (result == -1)
        {
            err("Error writing to port. Write data lost!");
            result = 0;
            break;
        }

        if (charSendDelayMs > 0)
        {
            SLEEP(charSendDelayMs);
        }
    }

#else
    // DO NOT RUN THIS CODE
    int result = port->write(buf, size);
    if (result == 0)
    {
        err("Unable to write bytes to port probably due to outgoing queue full. Write data lost!");
        /* the following code doesn't seem to help. Generate an error instead
        int limit = 0;
        while (!result && limit < 100)
        {
            SLEEP(100);
            result = port->write(buf, size);
            limit++;
        }

        if (!result)
        {
            err("Unable to write %d bytes to port!", size);
        }
        else if (result != size)
            err("Unexpected: Retry send wrote %d bytes out of expected %d\n", result, size);
        */
    }
    else if (result == -1)
    {
        err("Error writing to port. Write data lost!");
        result = 0;
    }
#endif
    return result;
}


void RS232::CloseComport()
{
    if (port != NULL)
    {
        port->close();
        delete port;
        port = NULL;
    }
}

void RS232::Reset() //still to test
{
    if (port != NULL)
        port->reset();
}

void RS232::flush()
{
    int n=1;
    char buf[255];

    while (n > 0)
        n = PollComport(buf,255);
}

bool RS232::isPortOpen()
{
    if (port == NULL)
        return false;

    return port->isOpen();
}

QString RS232::getDetectedLineFeed()
{
    return detectedLineFeed;
}

int RS232::bytesAvailable()
{
    int n = port->bytesAvailable();
    return n;
}

void RS232::setCharSendDelayMs(int csd)
{
    charSendDelayMs = csd;
}
