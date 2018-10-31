#include "SQuickView.h"
#include "WindowContainer.h"
#include "common/SCommon.h"

#include <QApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QDesktopWidget>
#include <QQmlContext>
#include <QPushButton>
SQuickView::SQuickView(QQmlEngine* engine, QWindow *parent) :
    QQuickView(engine,parent),
    m_horizontalRatio(1.0),
    m_verticalRatio(1.0)
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);
    setResizeMode(QQuickView::SizeRootObjectToView);
    rootContext()->setContextProperty("mainView",this);
//    QString filePath = QCoreApplication::applicationDirPath()+"/res/qml/main.qml";
//    setSource(QUrl::fromUserInput(filePath));
    setSource(QUrl("qrc:/res/qml/main.qml"));
    initWindowContainer();
    m_draggEabled = false;
}

void SQuickView::initWindowContainer()
{
    if(nullptr == m_pWindowContainer)
        return;
    m_pWindowContainer = new WindowContainer;
    rootContext()->setContextProperty("wndContainer",m_pWindowContainer);

    QQuickItem* containerRect = rootObject()->findChild<QQuickItem*>("WndContainerRect");
    if(NULL != containerRect)
    {
        m_pWindowContainer->setGeometry(containerRect->x(),containerRect->y(),
                                 containerRect->width(),containerRect->height());
        m_pWindowContainer->setAttribute(Qt::WA_NativeWindow);
        m_pWindowContainer->show();
        m_pWindowContainer->windowHandle()->setParent(this);
        m_pWindowContainer->hide();
    }

}

double SQuickView::horizontalRatio() const
{
    return m_horizontalRatio;
}

double SQuickView::verticalRatio() const
{
    return m_verticalRatio;
}

void SQuickView::setHorizontalRatio(const double &ratio)
{
    if(ratio - m_horizontalRatio > DEFAULT_RATIO && ratio -m_horizontalRatio < -DEFAULT_RATIO)
        return ;
    m_horizontalRatio = ratio;
    emit horizontalRatioChanged();
    qDebug() << "setHorizontalRatio: " << ratio;
}

void SQuickView::setVerticalRatio(const double &ratio)
{
    if(ratio - m_verticalRatio > DEFAULT_RATIO && ratio -m_verticalRatio < -DEFAULT_RATIO)
        return ;
    m_verticalRatio = ratio;
    emit verticalRatioChanged();
    qDebug() << "setVerticalRatio: " << ratio;
}

void SQuickView::mousePressEvent(QMouseEvent *e)
{
    requestActivate();
    qDebug() << "mousePressEvent: ";
    if(Qt::LeftButton == e->button() && e->x() < 600 && e->y() < 30)
    {
        m_draggEabled = true;
        m_delta =  e->globalPos() - geometry().topLeft(); //获取鼠标的世界坐标-减去窗口左上角的坐标
    }
    else
    {
        m_draggEabled = false;
    }
    QQuickView::mousePressEvent(e);
}

void SQuickView::mouseReleaseEvent(QMouseEvent *e)
{
    if(true == m_draggEabled)
    {
        const QRect& rect = QApplication::desktop()->screenGeometry(e->globalPos());
        qDebug() << "rect: " << rect;
        setHorizontalRatio(rect.width()/DEFAULT_WINDOW_WIDTH);
        setVerticalRatio(rect.height()/DEFAULT_WINDOW_HEIGHT);
    //    setGeometry(rect.x(), rect.y(), rect.width(), rect.height()- 40 * rect.height() / 1080.0);
        m_draggEabled = false;
    }
    QQuickView::mouseReleaseEvent(e);
}

void SQuickView::mouseMoveEvent(QMouseEvent *e)
{
    if(true == m_draggEabled)//窗口在移动的时候，e->button()一直为0。
    {
//        qDebug() << "mouseMoveEvent: ";
        setPosition(e->globalPos() - m_delta);//设置鼠标移动后的窗口的位置
    }
    QQuickView::mouseMoveEvent(e);
}

bool SQuickView::close()
{
    if(nullptr != m_pWindowContainer)
        m_pWindowContainer->close();
    return QQuickView::close();
}
