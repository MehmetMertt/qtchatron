#include "sessionuser.h"

SessionUser::SessionUser(QObject *parent)
    : QObject{parent},
    _user(new User("MyUser"))
{
    _dmList.append(new User("Mehmet"));
    _dmList.append(new User("Michi"));
    _dmList.append(new User("Martin"));
    _dmList.append(new User("User1"));
}


/*SessionUser::SessionUser(QString username, QObject *parent)
    : QObject{parent},
    _user(new User(username))
{
    _dmList.append(new User("Mehmet"));
    _dmList.append(new User("Michi"));
    _dmList.append(new User("Martin"));
    _dmList.append(new User("User1"));
}*/

QList<QObject *> SessionUser::dmList() const
{
    return _dmList;
}

void SessionUser::setDmList(const QList<QObject *> &newDmList)
{
    if (_dmList == newDmList)
        return;
    _dmList = newDmList;
    emit dmListChanged();
}

User *SessionUser::user() const
{
    return _user;
}
