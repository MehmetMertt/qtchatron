#include "Server/ServerWorker.h"
#include <QOverload>
#include <QAbstractSocket>
#include <QJsonParseError>
#include <QJsonObject>

ServerWorker::ServerWorker(QSslSocket *socket, QObject *parent)
    : QObject(parent)
    , _serverSocket(socket)
{
    connect(_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::receiveData);
    connect(_serverSocket, &QSslSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(_serverSocket, &QAbstractSocket::errorOccurred, this, &ServerWorker::error);
}

void ServerWorker::disconnectFromClient()
{
    if(_serverSocket->state() == QAbstractSocket::ConnectedState) {
        _serverSocket->disconnectFromHost();
    }
}


void ServerWorker::sendData(const protocol& p)
{
    std::string serializedData = p.serialize();
    quint32 dataLength = serializedData.size();

    QDataStream socketStream(_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_8);
    socketStream << dataLength;
    socketStream.writeRawData(serializedData.data(), dataLength);

    qDebug() << "Data sent to client.";
}

void ServerWorker::receiveData()
{
    QDataStream socketStream(_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_8);

    while (!_serverSocket->atEnd()) {
        socketStream.startTransaction();

        // Read the length prefix
        quint32 dataLength;
        socketStream >> dataLength;

        // Check if all data is available
        if (_serverSocket->bytesAvailable() < dataLength) {
            socketStream.rollbackTransaction();
            break;
        }

        // Read the serialized protocol data
        QByteArray serializedData;
        serializedData.resize(dataLength);
        socketStream.readRawData(serializedData.data(), dataLength);

        if (socketStream.commitTransaction()) {
            // Deserialize the protocol message
            protocol receivedProtocol;
            try {
                receivedProtocol.deserialize(serializedData.toStdString());

                qDebug() << "Received Protocol Object:";
                qDebug() << "MessageType:" << receivedProtocol.msgType;
                qDebug() << "Name:" << QString::fromStdString(receivedProtocol.name);
                qDebug() << "Payload:" << QString::fromStdString(receivedProtocol.payload);

                // Emit messageReceived signal
                emit messageReceived(this, receivedProtocol);

            } catch (const std::exception& ex) {
                emit logMessage("Failed to deserialize protocol: " + QString(ex.what()));
            }
        } else {
            // Data was incomplete, wait for more
            break;
        }
    }
}

