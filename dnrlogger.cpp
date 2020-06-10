#include "dnrlogger.h"
#include <QDebug>
#include <QCoreApplication>


#include <QTime>
#include <QFileInfo>
#include <syslog.h>

DNRLogger* DNRLogger::_singleton = NULL;


DNRLogger::~DNRLogger()
{
    free();
}

DNRLogger::DNRLogger() : QObject(NULL)
{
    _outputDebug = false;
    _logName = QFileInfo( QCoreApplication::applicationFilePath() ).fileName().toLatin1().data();
    openlog(_logName.toStdString().c_str(), LOG_PID, LOG_SYSLOG);

}


DNRLogger *DNRLogger::instance()
{
    if( NULL == _singleton )
    {
       _singleton = new DNRLogger();
    }
    return _singleton;
}

void DNRLogger::free()
{
    if( NULL != _singleton )
    {
        closelog();
        delete _singleton;
        _singleton = NULL;

    }
}

std::string DNRLogger::levelToStr(int level)
{
    switch(level)
    {
        case LOG_INFO:
            return "Info";
        case LOG_ERR:
            return "Error";
        case LOG_WARNING:
            return "Warning";
        case LOG_NOTICE:
            return "Notice";
        case LOG_CRIT:
            return "Critical";
        default:
            return "DK";
    }
}

void DNRLogger::logInfoQ(const QString& message)
{
    logMessage(LOG_INFO, message.toStdString());
}

void DNRLogger::logErrorQ(const QString& message)
{
    logMessage(LOG_ERR, message.toStdString());
}

void DNRLogger::logDebugQ(const QString& message)
{
    outputDebug(message.toStdString());
}

void DNRLogger::logWarningQ(const QString& message)
{
    logMessage(LOG_WARNING, message.toStdString());
}

void DNRLogger::logNoticeQ(const QString& message)
{
    logMessage(LOG_NOTICE, message.toStdString());
}

void DNRLogger::logCriticalQ(const QString& message)
{
    logMessage(LOG_CRIT, message.toStdString());
}

void DNRLogger::logInfo(const std::string& message)
{
    logMessage(LOG_INFO, message);
}

void DNRLogger::logError(const std::string& message)
{
    logMessage(LOG_ERR, message);
}

void DNRLogger::logDebug(const std::string& message)
{
    outputDebug(message);
}

void DNRLogger::logWarning(const std::string& message)
{
    logMessage(LOG_WARNING, message);
}

void DNRLogger::logNotice(const std::string& message)
{
    logMessage(LOG_NOTICE, message);
}

void DNRLogger::logCritical(const std::string& message)
{
    logMessage(LOG_CRIT, message);
}


void DNRLogger::outputDebug(const std::string& message)
{
    QTime rightNow = QTime::currentTime();
    qDebug() << rightNow.toString() << "**" << message.c_str();

}


void DNRLogger::logMessage(int level, const std::string& message)
{


    if (message.length())
    {
        QTime rightNow = QTime::currentTime();
        if(_outputDebug)
        {
            qDebug() << rightNow.toString() << "|- " << levelToStr(level).c_str() << " - " << message.c_str();
        }
//        openlog(_logName.toStdString().c_str(), (LOG_CONS|LOG_PERROR|LOG_PID), LOG_SYSLOG);
    //      openlog(_logName.toStdString().c_str(), LOG_PID, LOG_SYSLOG);

        syslog(level, "%s", message.c_str());
       // closelog();
    }

}
