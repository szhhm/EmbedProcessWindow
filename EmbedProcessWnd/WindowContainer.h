#ifndef WINDOWCONTAINER_H
#define WINDOWCONTAINER_H

#include <QMainWindow>
#include <qwindowdefs.h>

namespace Ui {
class WindowContainer;
}
class WindowContainer : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowContainer(QWidget *parent = 0);
    virtual ~WindowContainer();
    //嵌入进程的窗口
    Q_INVOKABLE void EmbedProcessWindow(const QString processName,
                                        const int x,
                                        const int y,
                                        const int width,
                                        const int height);

    //把当前程序的事件通过WId传递给第三方exe

    void attachWindowThreadInput(WId remoteWindowId);
signals:

public slots:
private:
    WId m_curWid;
    Ui::WindowContainer* ui;
};

#endif // WINDOWCONTAINER_H
