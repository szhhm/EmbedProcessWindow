/****************************************************************************************************************************
 * 类 FtpManager再Qt5.10 使用QNetworkAccessManager类来实现ftp的上传下载功能。
 * 使用QTcpSocket类来检测ftp的可用性
 *
 */
#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QFile>
#include <QNetworkReply>

class QFtpManagerPrivate;
class Q_DECL_EXPORT FtpManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpManager(QObject* parent = 0);
    ~FtpManager();
    // 设置地址和端口
    void setHostPort(const QString &host, const int port = 21);
    // 设置登录 FTP 服务器的用户名和密码
    void setUserInfo(const QString &userName, const QString &password);
    // 上传文件
    void put(const QString &fileName, const QString &path);
    // 下载文件
    void get(const QString &path, const QString &fileName);

    //检测ftp登录
    void checkFtpLogin(const QString& host, const int port, const QString& userName, const QString& password);

signals:
    void error(QNetworkReply::NetworkError);
    // 上传进度
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    // 下载进度
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    //文件下载完成
    void downloadFinished(const QString& compressedPathName);
    //文件上传完成
    void uploadFinished();

    //检测ftp登录的结果
    void ftpLoginResult(const bool bSuccess, const QString& msg);
private slots:
    // 下载过程中写文件
    void onDownloadFinished();
    void readData();
    void onUploadFinished();

    //ftp连接出错误处理
    void onFtpConnectError(int error);
    void onFtpConnected();
    void onFtpLoginReadyRead();
private:
    QUrl m_url;
    QFile m_file;
    QNetworkAccessManager m_networkMgr;
    QNetworkReply* m_pReply;
    QFtpManagerPrivate* m_pData;
};

#endif // FTPMANAGER_H
