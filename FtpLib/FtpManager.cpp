#include "FtpManager.h"

#include <QFile>
#include <QFileInfo>
#include <QTcpSocket>
#include <QNetworkAccessManager>

class QFtpManagerPrivate
{
public:
    explicit QFtpManagerPrivate() : m_userName(QString("")),m_password(QString("")){}

public:
    QTcpSocket  m_tcpSocket;
    QString     m_userName;
    QString     m_password;
};

/*********************************************************************************************************************/
FtpManager::FtpManager(QObject *parent) :
    QObject(parent), m_pReply(NULL), m_pData(NULL)
{
    m_url.setScheme("ftp");

    m_pData = new QFtpManagerPrivate();
    connect(&(m_pData->m_tcpSocket),static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &FtpManager::onFtpConnectError, Qt::UniqueConnection);
    connect(&(m_pData->m_tcpSocket),&QTcpSocket::connected, this, &FtpManager::onFtpConnected, Qt::UniqueConnection);
    connect(&(m_pData->m_tcpSocket),&QTcpSocket::readyRead, this, &FtpManager::onFtpLoginReadyRead, Qt::UniqueConnection);
}

FtpManager::~FtpManager()
{
    if(m_pData)
        delete m_pData;
}

void FtpManager::setHostPort(const QString &host, const int port)
{
    m_url.setHost(host);
    m_url.setPort(port);
}

void FtpManager::setUserInfo(const QString &userName, const QString &password)
{
    m_url.setUserName(userName);
    m_url.setPassword(password);
}

void FtpManager::put(const QString &fileName, const QString &path)
{
    //如果文件已经打开，就先关闭文件
    if(m_file.isOpen())
        m_file.close();

    m_file.setFileName(fileName);
    if(!m_file.open(QIODevice::ReadOnly)){
        qDebug() << QString::fromLocal8Bit("file: %1 open failed").arg(fileName);
        return;
    }
    m_url.setPath(path);

    m_pReply = m_networkMgr.put(QNetworkRequest(m_url), &m_file);
    connect(m_pReply, &QNetworkReply::uploadProgress, this, &FtpManager::uploadProgress, Qt::UniqueConnection);
    connect(m_pReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &FtpManager::error, Qt::UniqueConnection);
    connect(m_pReply, &QNetworkReply::finished, this, &FtpManager::onUploadFinished, Qt::UniqueConnection);
}

void FtpManager::get(const QString &path, const QString &fileName)
{
    m_file.setFileName(fileName);
    if(!m_file.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug() << QString::fromLocal8Bit("file: %1 open failed").arg(fileName);
        return;
    }
    m_url.setPath(path);

    m_pReply = m_networkMgr.get(QNetworkRequest(m_url));
    connect(m_pReply, &QNetworkReply::downloadProgress, this, &FtpManager::downloadProgress, Qt::UniqueConnection);
    connect(m_pReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &FtpManager::error, Qt::UniqueConnection);
    connect(m_pReply, &QNetworkReply::readyRead, this, &FtpManager::readData, Qt::UniqueConnection);
    connect(m_pReply, &QNetworkReply::finished, this, &FtpManager::onDownloadFinished, Qt::UniqueConnection);
}

void FtpManager::checkFtpLogin(const QString &host, const int port, const QString &userName, const QString &password)
{
    if(NULL == m_pData){
        qDebug() << "FtpManager::checkFtpLogin(): NULL == p";
        return;
    }
    m_pData->m_userName = userName;
    m_pData->m_password = password;
    m_pData->m_tcpSocket.connectToHost(host,port);
}

void FtpManager::onDownloadFinished()
{
    switch (m_pReply->error()) {
    case QNetworkReply::NoError:
        {
            const QByteArray& data = m_pReply->readAll();
            m_file.write(data);
            m_file.flush();
            break;
        }
    default:
        {
            qDebug() << "Error: " << m_pReply->errorString();
            m_file.close();
            m_pReply->deleteLater();
            m_file.remove();
            m_pReply = NULL;
            return;
        }
    }
    m_file.close();
    m_pReply->deleteLater();
    m_pReply = NULL;
    emit downloadFinished(m_file.fileName());
}

void FtpManager::readData()
{
    switch (m_pReply->error()) {
    case QNetworkReply::NoError:
        {
            const QByteArray& data = m_pReply->readAll();
            m_file.write(data);
            m_file.flush();
            break;
        }
    default:
        {
            qDebug() << "Error: " << m_pReply->errorString();
            m_file.close();
            m_pReply->deleteLater();
            m_file.remove();
            m_pReply = NULL;
            return;
        }
    }
}

void FtpManager::onUploadFinished()
{
    switch (m_pReply->error()) {
    case QNetworkReply::NoError:
        break;
    default:
        qDebug() << "Error: " << m_pReply->errorString();
        break;
    }
    m_file.close();
    m_pReply->deleteLater();
    m_pReply = NULL;
    emit uploadFinished();
}

void FtpManager::onFtpConnectError(int error)
{
    QString msg = QString::fromLocal8Bit("连接ftp出错");
    emit ftpLoginResult(false,msg);
    if(m_pData)
        m_pData->m_tcpSocket.close();
}

void FtpManager::onFtpConnected()
{
    if(NULL == m_pData){
        qDebug() << "FtpManager::onFtpConnected(): NULL == p";
        return;
    }
    QString cmd = QString::fromLocal8Bit("USER %1\r\nPASS %2\r\nQUIT\r\n").arg(m_pData->m_userName, m_pData->m_password);
    m_pData->m_tcpSocket.write(cmd.toUtf8());
}

void FtpManager::onFtpLoginReadyRead()
{
    QString strResult = QString("");
    if(!m_pData)
        return;
    while (m_pData->m_tcpSocket.canReadLine()) {
        const QString& line = QString::fromLatin1(m_pData->m_tcpSocket.readLine());
        qDebug() << "onFtpLoginReadyRead(): readline:" << line;
        if(line.isEmpty())
            continue;
        const int errorCode = line.split(" ").first().toInt();
        switch (errorCode) {
        case 220:
            strResult = QString::fromLocal8Bit("Microsft ftp service");
            break;
        case 221:
            strResult = QString::fromLocal8Bit("ftp退出登录");
            m_pData->m_tcpSocket.close();
            break;
        case 230:
            strResult = QString::fromLocal8Bit("ftp登录成功");
            emit ftpLoginResult(true,strResult);
            break;
        case 332:
            strResult = QString::fromLocal8Bit("登录ftp需要账号信息");
            emit ftpLoginResult(false,strResult);
            break;
        case 503:
            strResult = QString::fromLocal8Bit("请先输入ftp用户名");
            emit ftpLoginResult(false,strResult);
            break;
        case 530:
            strResult = QString::fromLocal8Bit("ftp账号或密码错误");
            emit ftpLoginResult(false,strResult);
            break;
        default:
            break;
        }
        qDebug() << "onFtpLoginReadyRead(): error:" << strResult;
    }
}


