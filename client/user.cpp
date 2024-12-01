#include "user.h"


User::User(QObject *parent)
    : QObject{parent}
{}


User::User(QString username, QObject *parent)
    : QObject{parent},
    _username(username)
{}

User::User(QString username, int id, QObject *parent)
    : QObject{parent},
    _username(username),
    _userId(id)
{}

QString User::username() const
{
    return _username;
}

void User::setUsername(const QString &newUsername)
{
    if (_username == newUsername)
        return;
    _username = newUsername;
    emit usernameChanged();
}

QString User::getInitials()
{
    return _username.left(1).toUpper();
}

int User::userId() const
{
    return _userId;
}

void User::setUserId(int newUserId)
{
    if (_userId == newUserId)
        return;
    _userId = newUserId;
    emit userIdChanged();
}

void User::addMessage(ChatMessageItem *newMessage)
{
    _messageList.append(newMessage);
    emit messageListChanged();
}

