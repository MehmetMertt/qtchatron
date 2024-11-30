#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{}

User::User(QString username, QObject *parent)
    : QObject{parent},
    _username(username)
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
