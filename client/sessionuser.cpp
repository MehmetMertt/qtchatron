#include "sessionuser.h"

#include "channelmodel.h"

#include "Communicator/Communicator.h"
#include "Protocol/protocol.h"

SessionUser* SessionUser::instance = nullptr;
std::mutex SessionUser::mtx;

SessionUser::SessionUser(QObject *parent)
    : QObject{parent},
    _user(new User()),
    _dmList(QList<QObject *>()),
    _channelList(QList<QObject *>())
{
    auto *communicator = Communicator::getInstance();
    connect(communicator, &Communicator::receivedMessageFromOtherUser, this, &SessionUser::handleReceivedMessageFromOtherUser);
}

QString SessionUser::token() const
{
    return _token;
}

void SessionUser::setToken(const QString &newToken)
{
    _token = newToken;
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

void SessionUser::processChatCreation(QString username)
{
    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::chatCreationResponse, this, &SessionUser::handleChatCreationResponse);
    connect(communicator, &Communicator::chatCreationResponse, this, &SessionUser::handleChatCreationResponse);

    this->instance->_chatCreationUsername = username;

    communicator->sendData(Protocol(COMMAND_TRANSFER, "check_user_exists", username.toStdString()));

}

void SessionUser::handleChatCreationResponse(const bool success, const QString message, const int receiverUserId)
{
    qDebug() << "chat creation respons: " << success << ": " << message << ": " << receiverUserId;
    if(success) {
        auto newUser = new User(this->instance->_chatCreationUsername, receiverUserId);
        this->instance->_dmList.append(newUser);
        qDebug("emit");
        emit this->instance->chatCreationSuccess(this->instance->_chatCreationUsername, this->instance->_dmList.indexOf(newUser));
    } else {
        emit this->instance->chatCreationFailure(message);
    }
}

void SessionUser::handleReceivedMessageFromOtherUser(const int senderId, const QString message)
{
    qDebug() << "message received from: " << senderId;
    auto sender = this->getUserFromDmListById(senderId);
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    sender->addMessage(new ChatMessageItem(sender->username(), message, timeString));
}

User *SessionUser::getUserFromDmListByUsername(QString username)
{
    for (QObject* obj : _dmList) { // Iterate over the list
        User* user = qobject_cast<User*>(obj); // Cast QObject* to User*
        qDebug() << user->username();
        if (user && user->username() == username) { // Check if the cast succeeded and the username matches
            qDebug() << "found";
            return user;
        }
    }
    return nullptr;
}

User *SessionUser::getUserFromDmListById(int userId)
{
    for (QObject* obj : _dmList) { // Iterate over the list
        User* user = qobject_cast<User*>(obj); // Cast QObject* to User*
        qDebug() << user->userId();
        if (user && user->userId() == userId) { // Check if the cast succeeded and the username matches
            qDebug() << "found";
            return user;
        }
    }
    return nullptr;
}


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

void SessionUser::setUser(User *newUser)
{
    qDebug() << "new user set: " << newUser->username();
    _user = newUser;
    emit userChanged();
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
