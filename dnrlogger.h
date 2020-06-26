#ifndef DNRLOGGER_H
#define DNRLOGGER_H
#include <QObject>
#include <QString>
#include <syslog.h>


class  DNRLogger : public QObject
{
    Q_OBJECT

public:
    ~DNRLogger();
    static DNRLogger* instance();
    static void free();

    void setDebugOut(bool debugOut) { DNRLogger::_outputDebug = debugOut; }
    void logInfoQ(const QString& message);
    void logErrorQ(const QString& message);
    void logDebugQ(const QString& message);
    void logWarningQ(const QString& message);
    void logNoticeQ(const QString& message);
    void logCriticalQ(const QString& message);

    void logInfo(const std::string& message);
    void logError(const std::string& message);
    void logDebug(const std::string& message);
    void logWarning(const std::string& message);
    void logNotice(const std::string& message);
    void logCritical(const std::string& message);

private:
        DNRLogger();
        //void logMessage(int level,QString message);
        //void outputDebug(QString message);
        void logMessage(int level,const std::string&);
        void outputDebug(const std::string&);
        std::string levelToStr(int level);

private:
    static DNRLogger* _singleton;
    QString  _logName;
    bool     _outputDebug;

};

#endif // DNRLOGGER_H
