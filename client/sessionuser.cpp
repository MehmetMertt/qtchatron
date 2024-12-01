#include "sessionuser.h"

#include "channelmodel.h"

SessionUser::SessionUser(QObject *parent)
    : QObject{parent},
    _user(new User("Flo"))
{
    _dmList.append(new User("Mehmet"));
    _dmList.append(new User("Michi"));
    _dmList.append(new User("Martin"));
    _dmList.append(new User("User1"));

    _channelList.append(new ChannelModel("MyChannel"));
    _channelList.append(new ChannelModel("Yooo"));
    _channelList.append(new ChannelModel("Group21"));
    _channelList.append(new ChannelModel("FH"));
    _channelList.append(new ChannelModel("This is a sick Channel"));
    _channelList.append(new ChannelModel("One More"));
    _channelList.append(new ChannelModel("MyChannel"));
    _channelList.append(new ChannelModel("Yooo"));
    _channelList.append(new ChannelModel("Group21"));
    _channelList.append(new ChannelModel("FH"));
    _channelList.append(new ChannelModel("This is a sick Channel"));
    _channelList.append(new ChannelModel("One More"));
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

QList<QObject *> SessionUser::channelList() const
{
    return _channelList;
}

void SessionUser::setChannelList(const QList<QObject *> &newChannelList)
{
    if (_channelList == newChannelList)
        return;
    _channelList = newChannelList;
    emit channelListChanged();
}
