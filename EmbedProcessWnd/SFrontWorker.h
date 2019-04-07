#ifndef SFRONTWORKER_H
#define SFRONTWORKER_H

#include <QObject>
class SQuickView;
class SAnoucementMsgModel;
class SFrontWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double horizontalRatio READ horizontalRatio WRITE setHorizontalRatio NOTIFY horizontalRatioChanged)
    Q_PROPERTY(double verticalRatio READ verticalRatio WRITE setVerticalRatio NOTIFY verticalRatioChanged)
private:
    explicit SFrontWorker(QObject *parent = nullptr);
    ~SFrontWorker();
public:
    static SFrontWorker& instance();
    void init();//初始化
    Q_INVOKABLE static SAnoucementMsgModel* anoucementMsgs();
    Q_INVOKABLE void close();
    Q_INVOKABLE void embededWindow();
    Q_INVOKABLE void testModifyModelData();

    double horizontalRatio() const;
    double verticalRatio() const;
    void setHorizontalRatio(const double &ratio);
    void setVerticalRatio(const double &ratio);

    QString getLocalmachineIp() const;
signals:
    void horizontalRatioChanged();
    void verticalRatioChanged();

public slots:
    void onDownloadFinished(const QString& compressedPathName);
private:
    SQuickView* mainView;
    double m_horizontalRatio;
    double m_verticalRatio;
};

#endif // SFRONTWORKER_H
