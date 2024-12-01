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
