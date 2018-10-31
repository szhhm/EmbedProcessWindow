/*
 *  @brief 主函数
 *  @date
 *  @author zhhm
 *
*/
#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QWidget>
#include "SFrontWorker.h"
#include "FtpManager.h"

#include <QProcess>
#include <QMainWindow>
#include <QApplication>
#include "ProcessWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SFrontWorker::instance().init();

//    qint64 pid = 0;
//    QProcess process;
//    bool bStart = process.startDetached("F:\\Qt_Program\\QML\\TestQtInstaller\\setup.exe",QStringList(), "F:\\Qt_Program\\QML\\TestQtInstaller\\", &pid);
//    bool bStarted = process.waitForStarted();
//    FtpManager ftpMananger;
//    ftpMananger.setHostPort("192.168.1.3",21);
//    ftpMananger.setUserInfo("ftpuser","ftpuser");
//    ftpMananger.checkFtpLogin("192.168.1.3",21,"ftpuser","ftpuser");

//    QMainWindow mainWindow;
//    int pid;
//    HWND hwnd = FindMyWindows("WpfApplication2.exe", pid);//获取指定进程的窗口句柄
//    QWindow* window = QWindow::fromWinId((WId)hwnd);
//    QWidget *widget = QWidget::createWindowContainer(window,&mainWindow);
//    mainWindow.setCentralWidget(widget);
//    mainWindow.showMaximized();
    return app.exec();
}

