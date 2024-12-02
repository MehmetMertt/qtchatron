#include "threadcontroller.h"

#include "sessionuser.h"
#include "Communicator/Communicator.h"

ThreadController::ThreadController(QObject *parent)
    : QObject{parent}
{}

void ThreadController::processSendingMessage(QString message, int threadId)
{
    QString senderToken = SessionUser::getInstance()->token();

    QJsonObject jsonObject;
    jsonObject["message"] = message;
    jsonObject["senderToken"] = senderToken;
    jsonObject["threadId"] = threadId;

    QJsonDocument jsonDoc(jsonObject);

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::sendMessageResponse, this, &ThreadController::processSendResponse);
    connect(communicator, &Communicator::sendMessageResponse, this, &ThreadController::processSendResponse);


    communicator->sendData(Protocol(MessageType::MESSAGE_TRANSFER, "send_to_thread", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

}

void ThreadController::processSendResponse(const bool success, const QString message)
{
    qDebug() << "send response " << success << ": " << message;
}
