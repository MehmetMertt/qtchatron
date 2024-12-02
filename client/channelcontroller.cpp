#include "channelcontroller.h"

#include "sessionuser.h"
#include "Communicator/Communicator.h"

ChannelController::ChannelController(QObject *parent)
    : QObject{parent}
{}

void ChannelController::processSendingMessage(QString message, int channelId)
{
    QString senderToken = SessionUser::getInstance()->token();

    QJsonObject jsonObject;
    jsonObject["message"] = message;
    jsonObject["senderToken"] = senderToken;
    jsonObject["channelId"] = channelId;

    QJsonDocument jsonDoc(jsonObject);

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::sendMessageResponse, this, &ChannelController::processSendResponse);
    connect(communicator, &Communicator::sendMessageResponse, this, &ChannelController::processSendResponse);


    communicator->sendData(Protocol(MessageType::MESSAGE_TRANSFER, "send_to_channel", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

}

void ChannelController::processSendResponse(const bool success, const QString message)
{
    qDebug() << "send response " << success << ": " << message;
}
