#include "WindowContainer.h"
#include "ProcessWindow.h"
#include "ui_windowcontainer.h"

#include <QDebug>
#include <QWindow>
#include <QWidget>
WindowContainer::WindowContainer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowContainer),
    m_curWid (0)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

WindowContainer::~WindowContainer()
{
    CloseWindow((HWND)m_curWid);
}

//嵌入进程的窗口
void WindowContainer::EmbedProcessWindow(const QString processName, const int x, const int y, const int width, const int height)
{
    qDebug() << QString::fromLocal8Bit("进程名字: ") << processName;

    if(m_curWid)
    {
        ShowWindow((HWND)m_curWid, WS_MAXIMIZE);
        return;
    }

    int pid = -1;
    HWND hwnd = FindMyWindows(processName.toStdString(), pid);//获取指定进程的窗口句柄
//    HWND parentHWnd = (HWND)(/*windowHandle()->*/winId());//获取当前窗口句柄
    //找到指定的进程窗口
//    if(-1 != pid && NULL != hwnd /*&& NULL != parentHWnd*/)
//    {
//        unsigned long lStyle = GetWindowLong(hwnd, GWL_STYLE);
//        lStyle &= ~WS_CAPTION;
//        lStyle &= ~WS_BORDER;
//        lStyle &= ~WS_POPUP;
//        lStyle &= ~WS_CLIPCHILDREN;//响应键盘事件
//        lStyle &= ~WS_MAXIMIZE;//窗口最大化时吸附进去，窗口的位置是乱的，去掉最大化设置
//        lStyle |= WS_CLIPSIBLINGS;
//        ::SetWindowLong(hwnd,GWL_STYLE, lStyle);
////        //为了防止一次可能吸附不成功，多设置几次
////        bool bResult = false;
////        for(int i = 0; i < 10; i++)
////        {
////            if(NULL != SetParent(hwnd, parentHWnd))
////            {
////                bResult = true;
////                break;
////            }
////            else
////                Sleep(10);
////        }
////        if(false == bResult)
////        {
////            show();//首先显示主窗体，
//            ShowWindow(hwnd, SW_SHOWMAXIMIZED);//然后再显示子窗体,否则会出现没有刷新的现象
////            m_curWid = (WId)hwnd;
////            qDebug() << "SetParent: false";
////        }
////        else
////            qDebug() << "SetParent: true";
//    }
    QWindow* window = QWindow::fromWinId((WId)hwnd);
    QWidget *widget = QWidget::createWindowContainer(window,this);
    setCentralWidget(widget);
    attachWindowThreadInput((WId)hwnd);
    //设置窗口的大小
    show();
    setGeometry(x,y,width,height);
    qDebug() << "x: " << x << " y: " << y<<1 << " width:" << width << " height:" << height;
}

void WindowContainer::attachWindowThreadInput(WId remoteWindowId)
{
    DWORD currentThreadId = GetCurrentThreadId();
    DWORD remoteThreadId = GetWindowThreadProcessId((HWND)remoteWindowId, NULL);
    qDebug() << __FUNCTION__ << "win" << remoteWindowId << "thr" << remoteThreadId;
    if (currentThreadId != remoteThreadId) {
        if (!AttachThreadInput(remoteThreadId, currentThreadId, true))
            qErrnoWarning("AttachThreadInput");
    }
}

