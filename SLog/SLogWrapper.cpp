#include "SLogWrapper.h"
#include "SLogHelper.h"

#include <QDir>
#include <QMutex>
#include <QDebug>
#include <QDateTime>
/**************************       SLogWrapper        *************************************************************************************/

SLogWrapper *SLogWrapper::getInstance()
{
    static SLogWrapper logWrapper;
    return &logWrapper;
}

SLogBase *SLogWrapper::getLogHelperObj(QString logPath)
{
    QString dstLogPath = "SLog";
    QString dstLogFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")+".log";
    int index = 0;
    if(!logPath.isEmpty())
    {
        index = logPath.lastIndexOf("/");
        if(0 < index)
        {
            dstLogPath = logPath.left(index);
        }
        else
        {
            dstLogPath = logPath;
        }
    }
    if(m_map.contains(dstLogPath))
        return m_map.value(dstLogPath);
    if(0 < index && index < logPath.length()-1)
    {
        dstLogFileName = logPath.right(logPath.length()-index-1);
    }
    QString dirPath = QDir::currentPath()+QDir::separator()+dstLogPath;
    QDir dir(dirPath);
    if(!dir.exists() && !dir.mkdir(dirPath))
    {
        qDebug() << "makeDir false";
    }

    auto logHelper = new SLogHelper(dstLogPath);
    logHelper->setAppenderName(dstLogPath + "Appender");
    logHelper->setLogPath(dirPath);
    logHelper->setLogFileName(dstLogFileName);
    logHelper->setLogLevel("INFO");
    logHelper->setMaxFileSize(10 * 1024 *1024);
    logHelper->setMaxBackupIndex(10);
    logHelper->initLog();
    m_map[dstLogPath] = logHelper;
    return logHelper;
}


