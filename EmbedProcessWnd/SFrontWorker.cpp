#include "SFrontWorker.h"
#include "SQuickView.h"
#include "model/SAnoucementMsg.h"
#include "SFrontWorker.h"
#include "SLogWrapper.h"

#include <QDateTime>
#include <QQmlEngine>
#include <QQmlContext>
#include <QHostAddress>
#include <QNetworkInterface>

#include <QMainWindow>
#include "ProcessWindow.h"
extern QDateTime startTime;
SFrontWorker::SFrontWorker(QObject *parent) :
    QObject(parent)
    ,m_verticalRatio(1.0)
    ,m_horizontalRatio(1.0)
{

}

SFrontWorker::~SFrontWorker()
{
}

double SFrontWorker::horizontalRatio() const
{
    return m_horizontalRatio;
}

double SFrontWorker::verticalRatio() const
{
    return m_verticalRatio;
}

void SFrontWorker::setHorizontalRatio(const double &ratio)
{
    if(ratio - m_horizontalRatio > 0.00001 && ratio -m_horizontalRatio < -0.00001)
        return ;
    m_horizontalRatio = ratio;
    emit horizontalRatioChanged();
    qDebug() << "setHorizontalRatio: " << ratio;
}

void SFrontWorker::setVerticalRatio(const double &ratio)
{
    if(ratio - m_verticalRatio > 0.00001 && ratio -m_verticalRatio < -0.00001)
        return ;
    m_verticalRatio = ratio;
    emit verticalRatioChanged();
    qDebug() << "setVerticalRatio: " << ratio;
}

SFrontWorker &SFrontWorker::instance()
{
    static SFrontWorker instance;
    return instance;
}

void SFrontWorker::init()
{
    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::SFrontWorker():开始初始化程序"));
    QQmlEngine* engine = new QQmlEngine(this);
    engine->rootContext()->setContextProperty("frontWorker",this);

    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::SFrontWorker():向qml类型中注册自定义C++类"));
    qmlRegisterType<SAnoucementMsg>("SClient",1,0,"AnoucementMsg");
    qmlRegisterType<SAnoucementMsgModel>("SClient",1,0,"AnoucementMsgModel");

    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::SFrontWorker():创建QuickView"));
//    engine->rootContext()->setContextProperty("mainView",mainView);
    if(nullptr == mainView){
        mainView = new SQuickView(engine);
//        mainView->resize(800,600);
        mainView->show();
    }
    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::SFrontWorker():加载完成，耗时:%1 ms。").arg(QDateTime::currentDateTime().msecsTo(startTime)));
    qDebug() << "localIp: " << getLocalmachineIp();
}

SAnoucementMsgModel *SFrontWorker::anoucementMsgs()
{
    static SAnoucementMsgModel model;
    for(int i = 0 ; i < 10; i++){
        QSharedPointer<SAnoucementMsg> pMsg = QSharedPointer<SAnoucementMsg>(new SAnoucementMsg);
        pMsg->m_msgId = i;
        pMsg->m_msgContent = QString::fromLocal8Bit("公告消息")+QString::number(i);
        pMsg->m_msgType = i%3;
        model.m_pMsgVec.prepend(pMsg);
    }
    return &model;
}

void SFrontWorker::close()
{
    if(nullptr != mainView)
        mainView->close();
}

void SFrontWorker::embededWindow()
{
    QMainWindow* mainWindow = new QMainWindow;
    mainWindow->createWinId();
    mainWindow->windowHandle()->setParent(mainView);
    int pid;
    HWND hwnd = FindMyWindows("WpfApplication2.exe", pid);//获取指定进程的窗口句柄
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    QWindow* window = QWindow::fromWinId((WId)hwnd);
    QWidget *widget = QWidget::createWindowContainer(window,mainWindow);
    mainWindow->setCentralWidget(widget);
    mainWindow->setGeometry(10,100,400,400);
    mainWindow->show();
}

void SFrontWorker::testModifyModelData()
{
    qDebug() <<"testModifyModelData";
    QModelIndex& index = anoucementMsgs()->index(0);
    anoucementMsgs()->setData(index,u8"这个是修改后的公告消息",SAnoucementMsgModel::MsgContentRole);
}

/*
 * 名称:get_localmachine_ip
 * 功能:获取本机的IP地址
 * 参数:no
 * 返回:QString
 */
QString SFrontWorker::getLocalmachineIp() const
{
    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::getLocalmachineIp():耗时:%1 ms。").arg(QDateTime::currentDateTime().msecsTo(startTime)));
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::getLocalmachineIp():获取所有IP地址，耗时:%1 ms。").arg(QDateTime::currentDateTime().msecsTo(startTime)));
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    S_WRITE_LOG("",SLogBase::S_INFO,QString::fromLocal8Bit("SFrontWorker::getLocalmachineIp():IP地址：%2，耗时:%1 ms。").arg(QDateTime::currentDateTime().msecsTo(startTime)).arg(ipAddress));
    return ipAddress;
}

void SFrontWorker::onDownloadFinished(const QString &compressedPathName)
{
    qDebug() << u8"下载完成";
    S_WRITE_LOG("", SLogBase::S_INFO, QString::fromLocal8Bit("下载完成，耗时：%1 ms").arg(QDateTime::currentDateTime().msecsTo(startTime)));
}
