#include "channelmodel.h"

#include "user.h"

ChannelModel::ChannelModel(QObject *parent)
    : QObject{parent}
{
    _memberList.append(new User("Mehmer"));
    _memberList.append(new User("Michi"));
    _memberList.append(new User("Martin"));
    _memberList.append(new User("User1"));
}

ChannelModel::ChannelModel(QString name, QObject *parent)
    : QObject{parent},
    _channelName(name)
{
    _memberList.append(new User("Mehmer"));
    _memberList.append(new User("Michi"));
    _memberList.append(new User("Martin"));
    _memberList.append(new User("User1"));
}

QList<QObject *> ChannelModel::memberList() const
{
    return _memberList;
}

void ChannelModel::setMemberList(const QList<QObject *> &newMemberList)
{
    if (_memberList == newMemberList)
        return;
    _memberList = newMemberList;
    emit memberListChanged();
}

QString ChannelModel::channelName() const
{
    return _channelName;
}

void ChannelModel::setChannelName(const QString &newChannelName)
{
    if (_channelName == newChannelName)
        return;
    _channelName = newChannelName;
    emit channelNameChanged();
}

int ChannelModel::channelID() const
{
    return _channelID;
}

void ChannelModel::setChannelID(int newChannelID)
{
    if (_channelID == newChannelID)
        return;
    _channelID = newChannelID;
    emit channelIDChanged();
}


