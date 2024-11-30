#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent)
    : QObject{parent},
    _inputMessage("")
{
    _messageList.append(new ChatMessageItem("flo", "hallo", "00:01"));
    _messageList.append(new ChatMessageItem("flo", "wie gehts", "00:01"));
    _messageList.append(new ChatMessageItem("michi", "Das ist eine lange geschichte in einer sehr langen nachricht, weil ich muss das halt auch irgendwie testen wie das auschaut", "00:02"));
    _messageList.append(new ChatMessageItem("flo", "ich weiß bro", "00:03"));
}

QString MessageModel::inputMessage() const
{
    return _inputMessage;
}

void MessageModel::setInputMessage(const QString &inputMessage)
{
    if (_inputMessage != inputMessage) {
        _inputMessage = inputMessage;
        emit inputMessageChanged();
    }
}

void MessageModel::sendMessage(){
    if (_inputMessage.isEmpty()) {
        return;  // Safety check
    }
    qDebug() << _inputMessage;
    // an den MessageController schicken
    // von MessageController an den Server schicken
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    _messageList.append(new ChatMessageItem("michi", _inputMessage, timeString));
    emit messageListChanged();
    emit sendMessageSuccess();
}
