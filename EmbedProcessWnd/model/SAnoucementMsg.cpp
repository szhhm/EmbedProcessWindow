#include "SAnoucementMsg.h"
#include <QDebug>

SAnoucementMsg::SAnoucementMsg(QObject *parent) : QObject(parent)
{
    m_msgId         = QString("");//消息id
    m_msgContent    = QString("");//消息内容
    m_msgType       = 0;//消息类别
}

SAnoucementMsg::~SAnoucementMsg()
{

}

/**********************************SAnoucementMsgModel*********************************************************************************/
SAnoucementMsgModel::SAnoucementMsgModel(QObject *parent)
{

}

SAnoucementMsgModel::~SAnoucementMsgModel()
{

}

int SAnoucementMsgModel::rowCount(const QModelIndex &parent) const
{
   return m_pMsgVec.size();
}

QVariant SAnoucementMsgModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= m_pMsgVec.size())
        return QVariant();
    auto pMsg = m_pMsgVec[index.row()];
    if(nullptr == pMsg)
        return QVariant();
    switch (role) {
    case MsgIdRole:
        return pMsg->m_msgId;
        break;
    case MsgContentRole:
        return pMsg->m_msgContent;
        break;
    case MsgTypeRole:
        return pMsg->m_msgType;
        break;
    default:
        break;
    }
    return QVariant();
}

bool SAnoucementMsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() > m_pMsgVec.size())
        return false;
    auto &data = m_pMsgVec.at(index.row());
    switch (role) {
    case MsgContentRole:
        qDebug() << value;
        data->m_msgContent = value.toString();
        break;
    default:
        break;
    }
    emit dataChanged(index,index);
    return true;
}

QHash<int, QByteArray> SAnoucementMsgModel::roleNames() const
{
    QHash<int,QByteArray> tmpRoleNames;
    tmpRoleNames[MsgIdRole] = "msgId";
    tmpRoleNames[MsgContentRole] = "msgContent";
    tmpRoleNames[MsgTypeRole] = "msgType";
    return tmpRoleNames;
}
