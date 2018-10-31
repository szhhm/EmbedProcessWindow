#ifndef SLogHelper_H
#define SLogHelper_H
/*
 *日志帮助
 *
*/
#include "SLogWrapper.h"
namespace Log4Qt
{
    class Logger;
    class RollingFileAppender;
    class TTCCLayout;
}

class SLogHelper : public SLogBase
{
public:
    explicit SLogHelper(const QString& logName);
    virtual ~SLogHelper(){}

    virtual void setLogPath(const QString& logDirectory);//设置log文件目录
    virtual void setLogFileName(const QString& fileName);//设置log文件名字
    virtual void setMaxFileSize(const int& fileSize);//设置log文件大小
    virtual void setMaxBackupIndex(const int& maxBackupIndex);//设置log文件最大数量
    virtual void setLogLevel(const QString& level);//设置log文件类型
    virtual void setAppenderName(const QString& myAppenderName);//设置Appender名字
    virtual void initLog();

    virtual bool writeLog(const LogLevel level, const QString &logMsg);//写log文件
    virtual bool writeLog(const LogLevel level, const QString &logMsg, const char* fileName, const int line);

private:
    Log4Qt::Logger *m_directLogger;//打印日志
    Log4Qt::RollingFileAppender *m_rollingFileAppender;//日志文件
    Log4Qt::TTCCLayout *m_layout;

    int m_maxFileSize;
    int m_maxBackupIndex;
    LogLevel m_logLevel;
    QString m_logDirPath;
    QString m_logFileName;
    QString m_appenderName;


};

#endif // SLogHelper_H
