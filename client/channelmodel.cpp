#include "channelmodel.h"

#include "sessionuser.h"

ChannelModel::ChannelModel(QObject *parent)
    : QObject{parent},
    _channelController(new ChannelController())
{}

void ChannelModel::sendMessage()
{
    if (_inputMessage.isEmpty()) {
        return;  // Safety check
    }
    _channelController->processSendingMessage(_inputMessage, this->channel()->channelID());
    qDebug() << _inputMessage;
    // an den MessageController schicken
    // von MessageController an den Server schicken
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    _channel->addMessage(new ChatMessageItem(SessionUser::getInstance()->user()->username(), _inputMessage, timeString));
    emit sendMessageSuccess();
}

Channel *ChannelModel::channel() const
{
    return _channel;
}

void ChannelModel::setChannel(Channel *newChannel)
{
    if (_channel == newChannel)
        return;
    _channel = newChannel;
    emit channelChanged();
}

QString ChannelModel::inputMessage() const
{
    return _inputMessage;
}

void ChannelModel::setInputMessage(const QString &newInputMessage)
{
    if (_inputMessage == newInputMessage)
        return;
    _inputMessage = newInputMessage;
    emit inputMessageChanged();
}
