#include "user.h"

User::User(QString username, QObject *parent)
    : QObject{parent},
    _username(username)
{}

QString User::username() const
{
    return _username;
}
