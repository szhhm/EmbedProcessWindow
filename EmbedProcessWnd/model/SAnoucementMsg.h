#ifndef SANOUCEMENTMSG_H
#define SANOUCEMENTMSG_H

#include <QObject>
#include <QAbstractListModel>
#include <QSharedPointer>
class SAnoucementMsg : public QObject
{
    Q_OBJECT
public:
    explicit SAnoucementMsg(QObject *parent = nullptr);
    virtual ~SAnoucementMsg();
signals:

public slots:
public:
    QString m_msgId;//消息id
    QString m_msgContent;//消息内容
    int     m_msgType;//消息类别
};

class SAnoucementMsgModel : public QAbstractListModel

{
    Q_OBJECT
public:
    enum
    {
        MsgIdRole = Qt::UserRole+1,
        MsgContentRole,
        MsgTypeRole,
    };
    explicit SAnoucementMsgModel(QObject*parent = nullptr);
    virtual ~SAnoucementMsgModel();

    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
    virtual QHash<int,QByteArray> roleNames() const;
public:
    QVector<QSharedPointer<SAnoucementMsg> > m_pMsgVec;
};

#endif // SANOUCEMENTMSG_H
