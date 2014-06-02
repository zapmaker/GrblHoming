/****************************************************************
 * main.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/
#include "mainwindow.h"
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtGui/QApplication>
#else
#include <QtWidgets/QApplication>
#endif

enum GC_LOG_TYPES
{
    LOG_DEBUG_TYPE = 1,
    LOG_ERROR_TYPE,
    LOG_WARN_TYPE,
    LOG_INFO_TYPE,
    LOG_STATUS_TYPE,
};

void logit(GC_LOG_TYPES type, const char *str, va_list args);

FILE *pDebugLogFile = NULL;
AtomicIntBool g_enableDebugLog;
Log4Qt::PatternLayout *p_layout;
Log4Qt::FileAppender *p_fappender;

int main(int argc, char *argv[])
{
    // setup logging
    Log4Qt::LogManager::rootLogger();
    //Log4Qt::TTCCLayout *p_layout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601);
    //Log4Qt::PatternLayout *p_layout = new Log4Qt::PatternLayout(Log4Qt::PatternLayout::TTCC_CONVERSION_PATTERN);
    p_layout = new Log4Qt::PatternLayout("%d %p (%c) - %m%n");
    p_layout->setName(QLatin1String("GC Basic Layout"));
    p_layout->activateOptions();

    // Create a console appender
    Log4Qt::ConsoleAppender *p_appender = new Log4Qt::ConsoleAppender(p_layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
    p_appender->setName(QLatin1String("GC Basic Console Appender"));
#ifdef QT_DEBUG
    p_appender->setThreshold(Log4Qt::Level::TRACE_INT);
#else
    p_appender->setThreshold(Log4Qt::Level::WARN_INT);
#endif
    p_appender->activateOptions();
    Log4Qt::Logger::rootLogger()->addAppender(p_appender);

    // Create a file appender
    p_fappender = new Log4Qt::FileAppender();
    p_fappender->setLayout(p_layout);
    p_fappender->setThreshold(Log4Qt::Level::TRACE_INT);
    p_fappender->setFile(QDir::homePath() + "/GrblController.log");
    p_fappender->setName(QLatin1String("GC Basic File Appender"));
    // don't open until ready (later during startup)
    //p_fappender->activateOptions();
    //Log4Qt::Logger::rootLogger()->addAppender(p_fappender);

    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QString dir = QDir::currentPath() + "/trlocale";
    QString file = QString("GrblController_") + locale;
	QTranslator translator;
    bool r = translator.load(file, dir);
    if (!r)
    {
        dir = QDir::currentPath() + "/../GrblHoming/trlocale";
        translator.load(file, dir);
    }
    a.installTranslator(&translator);

    QString xlatpath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    file = QString("qt_") + locale ;
    QTranslator qtTranslator;
    r = qtTranslator.load(file , xlatpath);
    if (!r)
    {
        xlatpath = QDir::currentPath() + "/trlocale";
        qtTranslator.load(file, xlatpath);
    }
    a.installTranslator(&qtTranslator);

    MainWindow w;
    w.show();

    int result = a.exec();

    if (pDebugLogFile != NULL)
    {
        fclose(pDebugLogFile);
        pDebugLogFile = NULL;
    }
    return result;
}


//------------------------------
void status(const char *str, ...)
{
#ifndef QT_DEBUG
    if (g_enableDebugLog.get()) {
#endif
    va_list args;

    va_start(args, str );
    logit(LOG_STATUS_TYPE, str, args);
    va_end(args);
#ifndef QT_DEBUG
    }
#endif
}

void err(const char *str, ...)
{
    va_list args;

    va_start(args, str );
    logit(LOG_ERROR_TYPE, str, args);
    va_end(args);
}

void warn(const char *str, ...)
{
    va_list args;

    va_start(args, str );
    logit(LOG_WARN_TYPE, str, args);
    va_end(args);
}

void info(const char *str, ...)
{
    va_list args;

    va_start(args, str );
    logit(LOG_INFO_TYPE, str, args);
    va_end(args);
}

void diag(const char *str, ...)
{
#ifndef QT_DEBUG
    if (g_enableDebugLog.get()) {
#endif
    va_list args;

    va_start(args, str );
    logit(LOG_DEBUG_TYPE, str, args);
    va_end(args);
#ifndef QT_DEBUG
    }
#endif
}

void logit(GC_LOG_TYPES type, const char *str, va_list args)
{
#define PRNTBUFSIZE 500
    char buf[PRNTBUFSIZE];
    buf[PRNTBUFSIZE-1] = '\0';

    vsnprintf(buf, sizeof(buf) - 1, str, args);

    int len = strlen(buf);
    if (len > 0)
    {
        if (len == 1 && (buf[0] == '\r' || buf[0] == '\n'))
        {
            buf[0] = '\0';
        }
        else if (len > 1)
        {
            if (buf[len - 2] == '\r' || buf[len - 2] == '\n')
                buf[len - 2] = '\0';
            else if (buf[len - 1] == '\r' || buf[len - 1] == '\n')
                buf[len - 1] = '\0';
        }
    }
    else if (len == 0)
        return;

    switch (type)
    {
        case LOG_STATUS_TYPE:
            Log4Qt::Logger::logger(LOG_MSG_TYPE_STATUS)->info(buf);
            break;
        case LOG_DEBUG_TYPE:
            Log4Qt::Logger::logger(LOG_MSG_TYPE_DIAG)->debug(buf);
            break;
        case LOG_ERROR_TYPE:
            Log4Qt::Logger::logger(LOG_MSG_TYPE_DIAG)->error(buf);
            break;
        case LOG_WARN_TYPE:
            Log4Qt::Logger::logger(LOG_MSG_TYPE_DIAG)->warn(buf);
            break;
        case LOG_INFO_TYPE:
            Log4Qt::Logger::logger(LOG_MSG_TYPE_DIAG)->info(buf);
            break;
    }
}
