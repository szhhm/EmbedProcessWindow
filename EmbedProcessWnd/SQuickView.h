#ifndef SQUICKVIEW_H
#define SQUICKVIEW_H

#include <QQuickView>
class WindowContainer;
class SQuickView : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(double horizontalRatio READ horizontalRatio WRITE setHorizontalRatio NOTIFY horizontalRatioChanged)
    Q_PROPERTY(double verticalRatio READ verticalRatio WRITE setVerticalRatio NOTIFY verticalRatioChanged)
public:
    explicit SQuickView(QQmlEngine* engine, QWindow *parent = nullptr);
    void initWindowContainer();

    double horizontalRatio() const;
    double verticalRatio() const;
    void setHorizontalRatio(const double &ratio);
    void setVerticalRatio(const double &ratio);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
signals:
    void horizontalRatioChanged();
    void verticalRatioChanged();
public slots:
    bool close();
private:
    WindowContainer* m_pWindowContainer;
    QPoint m_delta;
    bool m_draggEabled;

    double m_horizontalRatio;
    double m_verticalRatio;
};

#endif // SQUICKVIEW_H
