#include "chatmodel.h"

#include "chatmessageitem.h"
#include "sessionuser.h"

ChatModel::ChatModel(QObject *parent)
    : QObject{parent},
    _inputMessage(""),
    _chatController(new ChatController())
{}

QString ChatModel::inputMessage() const
{
    return _inputMessage;
}

void ChatModel::setInputMessage(const QString &inputMessage)
{
    if (_inputMessage != inputMessage) {
        _inputMessage = inputMessage;
        emit inputMessageChanged();
    }
}

User *ChatModel::receivingUser() const
{
    return _receivingUser;
}

void ChatModel::setReceivingUser(User *newReceivingUser)
{
    if (_receivingUser == newReceivingUser)
        return;
    _receivingUser = newReceivingUser;
    emit receivingUserChanged();
}

void ChatModel::sendMessage(){
    if (_inputMessage.isEmpty()) {
        return;  // Safety check
    }
    _chatController->processSendingMessage(_inputMessage, _receivingUser->userId());
    qDebug() << _inputMessage;
    // an den MessageController schicken
    // von MessageController an den Server schicken
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    _receivingUser->addMessage(new ChatMessageItem("michi", _inputMessage, timeString));
    emit messageListChanged();
    emit sendMessageSuccess();
}

void ChatModel::setReceivingUser(QString username)
{
    this->_receivingUser = SessionUser::getInstance()->getUserFromDmListByUsername(username);
}
