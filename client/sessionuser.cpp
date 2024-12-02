#include "sessionuser.h"

#include "channel.h"

#include "Communicator/Communicator.h"
#include "Protocol/protocol.h"
#include "chatmessageitem.h"
#include "thread.h"

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
    connect(communicator, &Communicator::receivedMessageFromOtherUserInChannel, this, &SessionUser::handleReceivedMessageFromOtherUserInChannel);
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

void SessionUser::processChannelCreation(QString channelname, QString type, bool isPublic)
{
    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::createChannelResponse, this, &SessionUser::handleChannelCreationResponse);
    connect(communicator, &Communicator::createChannelResponse, this, &SessionUser::handleChannelCreationResponse);

    this->instance->_channelCreationName = channelname;

    QJsonObject jsonObject;
    jsonObject["channelName"] = channelname;
    jsonObject["type"] = type;
    jsonObject["isPublic"] = isPublic;
    jsonObject["token"] = this->instance->token();

    qDebug() << type;

    QJsonDocument jsonDoc(jsonObject);

    communicator->sendData(Protocol(COMMAND_TRANSFER, "create_channel", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

}

void SessionUser::processChannelJoin(QString channelname, QString invite)
{
    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::joinChannelResponse, this, &SessionUser::handleChannelJoinResponse);
    connect(communicator, &Communicator::joinChannelResponse, this, &SessionUser::handleChannelJoinResponse);

    this->instance->_channelCreationName = channelname;

    QJsonObject jsonObject;
    jsonObject["channelName"] = channelname;
    jsonObject["invite"] = invite;
    jsonObject["token"] = this->instance->token();

    QJsonDocument jsonDoc(jsonObject);
    communicator->sendData(Protocol(COMMAND_TRANSFER, "join_channel", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

}

void SessionUser::processThreadCreation(QString threadname, int channelId)
{
    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::threadCreationRespond, this, &SessionUser::handleThreadCreationRespond);
    connect(communicator, &Communicator::threadCreationRespond, this, &SessionUser::handleThreadCreationRespond);

    this->instance->_channelCreationName = threadname;


    Channel* currentChannel = qobject_cast<Channel*>(this->instance->_channelList[channelId]);
    int realChannelId = -1;
    if(currentChannel) {
        realChannelId = currentChannel->channelID();
    }

    qDebug() << "create thread " << threadname << ": " << realChannelId;
    QJsonObject jsonObject;
    jsonObject["threadname"] = threadname;
    jsonObject["channelId"] = realChannelId;
    jsonObject["token"] = this->instance->token();


    QJsonDocument jsonDoc(jsonObject);
    communicator->sendData(Protocol(COMMAND_TRANSFER, "create_thread", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

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

void SessionUser::handleReceivedMessageFromOtherUserInChannel(const int senderId, const QString message, const int channelId)
{
    qDebug() << "message received from: " << senderId << " in " << channelId << ": " << message;
    auto sender = this->getUserFromChannelsById(senderId);
    auto channel = this->getChannelFromListById(channelId);
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    channel->addMessage(new ChatMessageItem(sender->username(), message, timeString));
}

void SessionUser::handleReceivedDmList(const bool success, const QString message)
{
    qDebug() << "received dm list" << success << ": ";
    qDebug() << message;

    QByteArray byteArray = message.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray);

    // Check if parsing was successful
    if (!jsonDoc.isArray()) {
        qWarning() << "Invalid JSON format!";
        return;
    }

    // Step 2: Extract the QJsonArray
    QJsonArray jsonArray = jsonDoc.array();

    // Step 3: Iterate over the array and extract fields
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            qDebug() << obj;
            qDebug() << obj["receiver"].toString();
            qDebug() << obj["username"].toString();
            User* newUser = new User();
            newUser->setUserId(obj["receiver"].toString().toInt());
            newUser->setUsername(obj["username"].toString());


            this->instance->_dmList.append(newUser);
            qDebug() << "inserted";
        }
    }
    this->instance->loadChatHistoryForAllUsers();
    emit dmListChanged();

}

void SessionUser::loadData()
{
    auto *communicator = Communicator::getInstance();

    connect(communicator, &Communicator::getDmListResponse, this, &SessionUser::handleReceivedDmList);
    connect(communicator, &Communicator::channelDataResponse, this, &SessionUser::handleReceivedChannelsData);


    communicator->sendData(Protocol(COMMAND_TRANSFER, "get_dmlist_by_userid", this->instance->token().toStdString()));
    communicator->sendData(Protocol(COMMAND_TRANSFER, "get_channels_data", this->instance->token().toStdString()));

}

void SessionUser::loadChatHistoryForAllUsers()
{
    auto* communicator = Communicator::getInstance();

    // Connect the response signal to the handler for chat history
    connect(communicator, &Communicator::getChatHistoryResponse, this, &SessionUser::handleReceivedChatHistory);

    // Iterate over the _dmList and send a request for each user
    for (QObject* userObj : this->instance->_dmList) {
        User* user = qobject_cast<User*>(userObj);
        if (user) {
            QString receiverId = QString::number(user->userId());
            qDebug() << "Requesting chat history for user with ID:" << receiverId;

            QJsonObject payload;
            payload["token"] = this->instance->token();
            payload["receiver_id"] = receiverId;

            // Convert the JSON object to a string
            QString jsonString = QString::fromUtf8(QJsonDocument(payload).toJson(QJsonDocument::Compact));


            // Send a request for chat history
            communicator->sendData(Protocol(COMMAND_TRANSFER,
                                            "get_chat_history_by_userid",
                                            jsonString.toStdString()));
        }
    }
}

// Handler for the chat history response
void SessionUser::handleReceivedChatHistory(const bool success, const QString& message, const int receiverId)
{
    // Add the chat history request to the queue
    _chatHistoryQueue.enqueue(std::make_tuple(success, message, receiverId));

    // Start processing if not already processing
    if (!_isProcessingChatHistory) {
        handleNextChatHistory();
    }
}

void SessionUser::handleChannelCreationResponse(const bool success, const QString &message, const QString &invite)
{
    if(!success) {
        emit this->instance->channelPopupFailure(message);
        return;
    }

    qDebug() << "channel create response " << success << ": " << message << ": " << invite;
    auto newChannel = new Channel(_channelCreationName);
    newChannel->setChannelID(message.toInt());

    if(!invite.isEmpty()) {
        newChannel->setInvite(invite);
    }

    newChannel->setMemberList(QList<QObject *> {this->instance->user()});

    this->instance->_channelList.append(newChannel);
    emit this->instance->channelPopupSuccess(_channelCreationName, this->instance->_channelList.indexOf(newChannel));
    emit this->instance->channelListChanged();
}

void SessionUser::handleChannelJoinResponse(const bool success, const QString &message)
{
    if(!success) {
        emit this->instance->channelPopupFailure(message);
        return;
    }

    qDebug() << "channel join response " << success << ": " << message;;
    auto newChannel = new Channel(_channelCreationName);
    newChannel->setChannelID(message.toInt());

    newChannel->addMember(this->instance->user());

    this->instance->_channelList.append(newChannel);
    emit this->instance->channelPopupSuccess(_channelCreationName, this->instance->_channelList.indexOf(newChannel));
    emit this->instance->channelListChanged();
}

void SessionUser::handleReceivedChannelsData(const bool success, const QString message)
{
    qDebug() << "Channel data received: " << success << ": " << message;

    if (!success) {
        qDebug() << "Failed to retrieve channel data.";
        return;
    }

    // Parse the JSON string
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        qDebug() << "Invalid JSON format.";
        return;
    }

    QJsonArray channelArray = jsonDoc.array();

    qDebug() << "go through list";
    for (const QJsonValue& channelValue : channelArray) {
        if (!channelValue.isObject()) continue;

        QJsonObject channelObject = channelValue.toObject();

        // Extract channel details
        QString channelName = channelObject["channelName"].toString();
        QString channelId = channelObject["channel_id"].toString();
        QString channelType = channelObject["channel_type"].toString();
        QString channelAdmin = channelObject["channel_admin"].toString();
        QString channelInvite = channelObject["channel_invite"].toString();

        // Extract and parse channel members
        QString membersRaw = channelObject["channel_members"].toString();
        QStringList memberList = membersRaw.split(",", Qt::SkipEmptyParts);

        auto channel = new Channel(channelName, this);
        channel->setChannelID(channelId.toInt());
        channel->setInvite(channelInvite);

        for (const QString& member : memberList) {
            QStringList parts = member.split(":");
            if (parts.size() == 2) {
                QString username = parts[0];
                int userId = parts[1].toInt();

                qDebug() << "check existing user";
                // Check if user exists in dmList or other channels
                User* existingUser = getUserFromDmListById(userId);
                if (!existingUser) {
                    existingUser = getUserFromChannelsById(userId);
                }

                if (existingUser) {
                    channel->addMember(existingUser);
                } else {
                    channel->addMember(new User(username, userId, this));
                }
            }
        }

        qDebug() << "add to list";
        this->instance->_channelList.append(channel);

    }
    emit channelListChanged();
}

void SessionUser::handleThreadCreationRespond(const bool success, const QString message, const int channelId)
{
    if (!success) {
        emit this->instance->channelPopupFailure(message);
        return;
    }

    qDebug() << "thread create response " << success << ": " << message << ". " << _channelCreationName << ": <" << channelId;

    auto* newThread = new Thread(_channelCreationName, message.toInt());

    qDebug() << "emit signals";
    Channel* channel = this->instance->getChannelFromListById(channelId);
    int newThreadIndex = channel->threadList().length();
    channel->addThread(newThread);

    qDebug() << channel->threadList();
    qDebug() << this->instance->_channelList;
    qDebug() << "emit signals";

    emit this->instance->threadPopupSuccess(_channelCreationName, this->instance->_channelList.indexOf(channel), newThreadIndex);
    emit this->instance->channelListChanged();
}


void SessionUser::handleNextChatHistory()
{
    if (_chatHistoryQueue.isEmpty()) {
        _isProcessingChatHistory = false;
        return;
    }

    // Mark that we're processing
    _isProcessingChatHistory = true;

    // Get the next item from the queue
    auto [success, message, receiverId] = _chatHistoryQueue.dequeue();

    if (!success) {
        qWarning() << "Failed to load chat history:" << message;
        handleNextChatHistory();
        return;
    }

    qDebug() << "Received chat history:" << message;

    QByteArray byteArray = message.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray);
    if (!jsonDoc.isArray()) {
        qWarning() << "Invalid message JSON format!";
        handleNextChatHistory();
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    User* userForHistory;

    qDebug() << receiverId;

    for (QObject* userObj : this->instance->_dmList) {
        User* user = qobject_cast<User*>(userObj);
        if (user && user->userId() == receiverId) {
            userForHistory = user;
            qDebug() << "Chat history set for user with ID:" << receiverId;
            break;
        }
    }

    qDebug() << "get messages";

    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject messageObject = value.toObject();
            QString content = messageObject["content"].toString();
            QString receiverId = messageObject["receiver_id"].toString();
            QString senderId = messageObject["sender_id"].toString();
            QString timestamp = messageObject["timestamp"].toString();

            QString username = "";
            if(senderId == receiverId) {
                username = userForHistory->username();
            } else {
                username = this->instance->user()->username();
            }

            ChatMessageItem *messageItem = new ChatMessageItem(username, content, timestamp, this);
            userForHistory->addMessage(messageItem);
        }
    }

    // After handling this chat history, process the next one
    handleNextChatHistory();
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

Channel *SessionUser::getChannelFromListById(int channelId)
{
    for (QObject* obj : _channelList) { // Iterate over the list
        Channel* channel = qobject_cast<Channel*>(obj); // Cast QObject* to User*
        qDebug() << channel->channelID();
        if (channel && channel->channelID() == channelId) { // Check if the cast succeeded and the username matches
            qDebug() << "found";
            return channel;
        }
    }
    return nullptr;
}

User *SessionUser::getUserFromChannelsById(int userId)
{
    for (QObject* obj : _channelList) {
        Channel* channel = qobject_cast<Channel*>(obj); // Assuming Channel is your class for channels
        if (channel) {
            QList<QObject*> members = channel->memberList();
            for (QObject* memberObj : members) {
                User* user = qobject_cast<User*>(memberObj);
                if (user && user->userId() == userId) {
                    return user; // User found
                }
            }
        }
    }
    return nullptr; // User not found
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
