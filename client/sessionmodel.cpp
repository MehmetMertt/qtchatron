#include "sessionmodel.h"
#include <QGlobalStatic>


QString SessionModel::currentUsername() const
{
    qDebug() << "qml access " << _currentUser;
    return _currentUsername;
}

User* SessionModel::currentUser() const
{
    return _currentUser;
}

void SessionModel::setCurrentUser(User* user)
{
    if (user != _currentUser) {
        qDebug() << "new user " << user->username();
        _currentUser = user;
        _currentUsername = user->username();
    }
}


