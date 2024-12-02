#include "Channel.h"

#include "user.h"

Channel::Channel(QObject *parent)
    : QObject{parent}
{
    _memberList.append(new User("Mehmer"));
    _memberList.append(new User("Michi"));
    _memberList.append(new User("Martin"));
    _memberList.append(new User("User1"));
}

Channel::Channel(QString name, QObject *parent)
    : QObject{parent},
    _channelName(name)
{
    _memberList.append(new User("Mehmer"));
    _memberList.append(new User("Michi"));
    _memberList.append(new User("Martin"));
    _memberList.append(new User("User1"));
}

QList<QObject *> Channel::memberList() const
{
    return _memberList;
}

void Channel::setMemberList(const QList<QObject *> &newMemberList)
{
    if (_memberList == newMemberList)
        return;
    _memberList = newMemberList;
    emit memberListChanged();
}

QString Channel::channelName() const
{
    return _channelName;
}

void Channel::setChannelName(const QString &newChannelName)
{
    if (_channelName == newChannelName)
        return;
    _channelName = newChannelName;
    emit channelNameChanged();
}

int Channel::channelID() const
{
    return _channelID;
}

void Channel::setChannelID(int newChannelID)
{
    if (_channelID == newChannelID)
        return;
    _channelID = newChannelID;
    emit channelIDChanged();
}

QList<QObject *> Channel::messageList() const
{
    return _messageList;
}

void Channel::setMessageList(const QList<QObject *> &newMessageList)
{
    if (_messageList == newMessageList)
        return;
    _messageList = newMessageList;
    emit messageListChanged();
}

QString Channel::invite() const
{
    return _invite;
}

void Channel::setInvite(const QString &newInvite)
{
    if (_invite == newInvite)
        return;
    _invite = newInvite;
    emit inviteChanged();
}

void Channel::addMessage(ChatMessageItem *newMessage)
{
    _messageList.append(newMessage);
    emit messageListChanged();
}
