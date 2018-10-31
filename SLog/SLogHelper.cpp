#include "SLogHelper.h"
#include "log4qt/level.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/fileappender.h"
#include "log4qt/rollingfileappender.h"

#include <QDir>
SLogHelper::SLogHelper(const QString &logName)
{
    m_directLogger = Log4Qt::Logger::logger(logName);
    m_rollingFileAppender = new Log4Qt::RollingFileAppender();
    m_layout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601);
}

void SLogHelper::setLogPath(const QString &logDirectory)
{
    m_logDirPath = logDirectory;
}

void SLogHelper::setLogFileName(const QString &fileName)
{
    m_logFileName = fileName;
}

void SLogHelper::setMaxFileSize(const int &fileSize)
{
    m_maxFileSize = fileSize;
}

void SLogHelper::setMaxBackupIndex(const int &maxBackupIndex)
{
    m_maxBackupIndex = maxBackupIndex;
}

void SLogHelper::setLogLevel(const QString &level)
{
    Log4Qt::Level myLevel;
    if(NULL == level)
    {
        myLevel = Log4Qt::Level::NULL_INT;
        m_logLevel = S_OFF;
    }
    else if("ALL" == level)
    {
        myLevel = Log4Qt::Level::ALL_INT;
        m_logLevel = S_ALL;
    }
    else if("TRACE" == level)
    {
        myLevel = Log4Qt::Level::TRACE_INT;
        m_logLevel = S_TRACE;
    }
    else if("DEBUG" == level)
    {
        myLevel = Log4Qt::Level::DEBUG_INT;
        m_logLevel = S_DEBUG;
    }
    else if("INFO" == level)
    {
        myLevel = Log4Qt::Level::INFO_INT;
        m_logLevel = S_INFO;
    }
    else if("WARN" == level)
    {
        myLevel = Log4Qt::Level::WARN_INT;
        m_logLevel = S_WARN;
    }
    else if("ERROR" == level)
    {
        myLevel = Log4Qt::Level::ERROR_INT;
        m_logLevel = S_ERROR;
    }
    else if("FATAL" == level)
    {
        myLevel = Log4Qt::Level::FATAL_INT;
        m_logLevel = S_FATAL;
    }
    else
    {
        myLevel = Log4Qt::Level::OFF_INT;
        m_logLevel = S_OFF;
    }
    m_directLogger->setLevel(myLevel);
}

void SLogHelper::setAppenderName(const QString &myAppenderName)
{
    m_appenderName = myAppenderName;
}

void SLogHelper::initLog()
{
    m_layout->setThreadPrinting(true);

    m_rollingFileAppender->setName(m_appenderName);
    QString logFile = m_logDirPath + QDir::separator() + m_logFileName;
    m_rollingFileAppender->setFile(logFile);
    m_rollingFileAppender->setAppendFile(true);
    m_rollingFileAppender->setImmediateFlush(true);
    m_rollingFileAppender->setMaxBackupIndex(m_maxBackupIndex);

    QString strFileSize = QString::number(m_maxFileSize);
    m_rollingFileAppender->setMaxFileSize(strFileSize);
    m_rollingFileAppender->setLayout(m_layout);
    m_rollingFileAppender->activateOptions();

    m_directLogger->addAppender(m_rollingFileAppender);
}

bool SLogHelper::writeLog(const SLogBase::LogLevel level, const QString &logMsg)
{
    if(NULL == m_rollingFileAppender)
    {
        return false;
    }
    if(S_OFF == m_logLevel || (int)level < (int)m_logLevel)
    {
        return false;
    }

    switch (level) {
    case S_FATAL:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->fatal("%1", logMsg);
        }
        break;
    case S_ERROR:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->error("%1", logMsg);
        }
        break;
    case S_WARN:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->warn("%1", logMsg);
        }
        break;
    case S_INFO:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->info("%1", logMsg);
        }
        break;
    case S_DEBUG:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->debug("%1", logMsg);
        }
        break;
    case S_TRACE:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->trace("%1", logMsg);
        }
        break;
    default:
        break;
    }
    return true;
}

bool SLogHelper::writeLog(const SLogBase::LogLevel level, const QString &logMsg, const char *fileName, const int line)
{
    if(NULL == m_directLogger)
    {
        return false;
    }

    if(S_OFF == m_logLevel || (int)level < (int)m_logLevel)
    {
        return false;
    }
    switch (level) {
    case S_FATAL:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->fatal("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    case S_ERROR:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->error("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    case S_WARN:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->warn("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    case S_INFO:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->info("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    case S_DEBUG:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->debug("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    case S_TRACE:
        if(m_directLogger->isErrorEnabled())
        {
            m_directLogger->trace("%1，%2, %3", logMsg,fileName,line);
        }
        break;
    default:
        break;
    }
    return true;
}
