#include "chatcontroller.h"

#include "sessionuser.h"
#include "Communicator/Communicator.h"

ChatController::ChatController(QObject *parent)
    : QObject{parent}
{}

void ChatController::processSendingMessage(QString message, int receiverId)
{
    QString senderToken = SessionUser::getInstance()->token();

    QJsonObject jsonObject;
    jsonObject["message"] = message;
    jsonObject["senderToken"] = senderToken;
    jsonObject["receiverId"] = receiverId;

    QJsonDocument jsonDoc(jsonObject);

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::sendMessageResponse, this, &ChatController::processSendResponse);
    connect(communicator, &Communicator::sendMessageResponse, this, &ChatController::processSendResponse);


    communicator->sendData(Protocol(MessageType::MESSAGE_TRANSFER, "send_dm", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

}

void ChatController::processSendResponse(const bool success, const QString message)
{
    qDebug() << "send response " << success << ": " << message;
}
