#ifndef SLOGWRAPPER_H
#define SLOGWRAPPER_H

#include <QMap>
#include <QString>

class SLogBase
{
public:
    typedef enum _LogLevel
    {
        S_ALL,
        S_TRACE,
        S_DEBUG,
        S_INFO,
        S_WARN,
        S_ERROR,
        S_FATAL,
        S_OFF
    }LogLevel;

    explicit SLogBase(){}
    virtual ~SLogBase(){}
    virtual bool writeLog(const LogLevel level, const QString& logMsg) = 0;
    virtual bool writeLog(const LogLevel level, const QString &logMsg, const char* fileName, const int line) = 0;
};

class Q_DECL_EXPORT SLogWrapper
{
public:
    static SLogWrapper* getInstance();
    SLogBase* getLogHelperObj(QString logPath);
private:
    explicit SLogWrapper(){}
    virtual ~SLogWrapper(){}
private:
    QMap<QString, SLogBase*> m_map;
};

#define S_WRITE_LOG(logPath,level,logMsg) SLogWrapper::getInstance()->getLogHelperObj(logPath)->writeLog(level,logMsg);
#endif // SLOGWRAPPER_H
