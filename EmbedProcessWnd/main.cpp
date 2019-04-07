/*
 *  @brief 主函数
 *  @date
 *  @author zhhm
 *
*/
#include "SFrontWorker.h"
#include "ProcessWindow.h"
#include "FtpManager.h"

#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QWidget>
#include <QProcess>
#include <QMainWindow>
#include <QTextCodec>
#include <QDateTime>
QDateTime startTime;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SFrontWorker::instance().init();
//    qint64 pid = 0;
//    QProcess process;
//    bool bStart = process.startDetached("F:\\Qt_Program\\QML\\TestQtInstaller\\setup.exe",QStringList(), "F:\\Qt_Program\\QML\\TestQtInstaller\\", &pid);
//    bool bStarted = process.waitForStarted();
    startTime = QDateTime::currentDateTime();
    FtpManager ftpMananger;
    ftpMananger.setHostPort("192.168.1.3",21);
    ftpMananger.setUserInfo("ftpuser","ftpuser");
    ftpMananger.checkFtpLogin("192.168.1.3",21,"ftpuser","ftpuser");
    QString ftpFileName = QStringLiteral("test.zip");
    qDebug() << "ftpFileName: " << ftpFileName;
    qDebug() << "ftpFileName Local8Bit: " << ftpFileName.toLocal8Bit();
    qDebug() << "ftpFileName Utf8: " << ftpFileName.toUtf8();
    qDebug() << "ftpFileName: Latin1" << ftpFileName.toLatin1();
    qDebug() << "ftpFileName: StdString" << ftpFileName.toStdString().c_str();
    QTextCodec *codec1 = QTextCodec::codecForName("GB2312");
    ftpMananger.get(codec1->fromUnicode("/Program/test.zip"), QApplication::applicationDirPath()+"/temp/"+ftpFileName.toLocal8Bit());

    QObject::connect(&ftpMananger, &FtpManager::downloadFinished, &SFrontWorker::instance(), &SFrontWorker::onDownloadFinished, Qt::UniqueConnection);
//    QMainWindow mainWindow;
//    int pid;
//    HWND hwnd = FindMyWindows("WpfApplication2.exe", pid);//获取指定进程的窗口句柄
//    QWindow* window = QWindow::fromWinId((WId)hwnd);
//    QWidget *widget = QWidget::createWindowContainer(window,&mainWindow);
//    mainWindow.setCentralWidget(widget);
//    mainWindow.showMaximized();
    return app.exec();
}

