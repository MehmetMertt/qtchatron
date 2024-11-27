#include "Server/ServerWorker.h"

#include <QOverload>
#include <QAbstractSocket>
#include <QJsonParseError>
#include <QJsonObject>

ServerWorker::ServerWorker(QSslSocket *socket, QObject *parent)
    : QObject(parent)
    , _serverSocket(socket)
{
    connect(_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::receiveJson);
    connect(_serverSocket, &QSslSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(_serverSocket, &QAbstractSocket::errorOccurred, this, &ServerWorker::error);
}

void ServerWorker::disconnectFromClient()
{
    if(_serverSocket->state() == QAbstractSocket::ConnectedState) {
        _serverSocket->disconnectFromHost();
    }
}


// https://wiki.qt.io/WIP-How_to_create_a_simple_chat_application#The_Single_Thread_Server
void ServerWorker::receiveJson()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(_serverSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_6_8);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()){ // and is a JSON object
                    QJsonObject jsonObj = jsonDoc.object();
                    qDebug() << "json received: " << jsonDoc.object();
                    emit jsonReceived(jsonDoc.object()); // send the message to the central server
                }
                else {
                    emit logMessage("Invalid message: " + QString::fromUtf8(jsonData)); //notify the server of invalid data
                }
            } else {
                emit logMessage("Invalid message: " + QString::fromUtf8(jsonData)); //notify the server of invalid data
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    // we crate a temporary QJsonDocument forom the object and then convert it
    // to its UTF-8 encoded version. We use QJsonDocument::Compact to save bandwidth
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    // we notify the central server we are about to send the message
    emit logMessage("Sending: " + QString::fromUtf8(jsonData));
    // we send the message to the socket in the exact same way we did in the client
    QDataStream socketStream(_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_8);
    socketStream << jsonData;
    qDebug() << "message send to client";
}
