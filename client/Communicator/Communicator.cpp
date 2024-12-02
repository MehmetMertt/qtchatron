// Communicator.cpp
#include "Communicator.h"
#include "qsslconfiguration.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

Communicator* Communicator::instance = nullptr;
std::mutex Communicator::mtx;

Communicator::Communicator(QObject *parent)
    : QObject(parent)
    , _clientSocket(new QSslSocket(this))
{
    setSslCaCertificate("server.crt");
    setSslProtocol(QSsl::TlsV1_3OrLater);

    connect(_clientSocket, &QSslSocket::encrypted, this, &Communicator::onEncrypted);
    connect(_clientSocket, &QTcpSocket::connected, this, &Communicator::onConnected);
    connect(_clientSocket, &QTcpSocket::disconnected, this, &Communicator::disconnectFromHost);
    connect(_clientSocket, &QTcpSocket::readyRead, this, &Communicator::onReadyRead);
    connect(_clientSocket, &QAbstractSocket::errorOccurred, this, &Communicator::error);
}

void Communicator::connectToServer(const QString &address, quint16 port)
{
    // Configure SSL settings
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.addCaCertificate(_sslCaCertificate);
    _clientSocket->setSslConfiguration(sslConfig);
    _clientSocket->setProtocol(_sslProtocol);
    _clientSocket->setPeerVerifyMode(QSslSocket::VerifyNone);

    qDebug() << "Connecting to server...";
    _clientSocket->connectToHostEncrypted(address, port);
}

void Communicator::onConnected()
{
    if (!_clientSocket->waitForEncrypted(5000)) {  // Wait up to 5 seconds for the connection
        qWarning() << "SSL handshake failed:" << _clientSocket->errorString();
        return;
    }
}


void Communicator::onEncrypted()
{
    qDebug() << "Encrypted connection established.";
    emit socketEncryptionSuccess();
    sendData(Protocol(MessageType::COMMAND_TRANSFER, "hello", "Hello Server")); //test
}

void Communicator::disconnectFromHost()
{
    _clientSocket->disconnectFromHost();
}

void Communicator::sendData(const Protocol& p)
{
    std::string serializedData = p.serialize();
    quint32 dataLength = serializedData.size();

    QDataStream clientStream(_clientSocket);
    clientStream.setVersion(QDataStream::Qt_6_8);
    clientStream << dataLength;
    clientStream.writeRawData(serializedData.data(), dataLength);

    qDebug() << "Data sent to server.";
}

void Communicator::onReadyRead()
{
    QDataStream socketStream(_clientSocket);
    socketStream.setVersion(QDataStream::Qt_6_8);

    while (!_clientSocket->atEnd()) {
        socketStream.startTransaction();

        // Read the length prefix
        quint32 dataLength;
        socketStream >> dataLength;

        // Check if all data is available
        if (_clientSocket->bytesAvailable() < dataLength) {
            socketStream.rollbackTransaction();
            break;
        }

        // Read the serialized Protocol data
        QByteArray serializedData;
        serializedData.resize(dataLength);
        socketStream.readRawData(serializedData.data(), dataLength);

        if (socketStream.commitTransaction()) {
            // Deserialize the Protocol message
            Protocol receivedProtocol;
            try {
                receivedProtocol.deserialize(serializedData.toStdString());

                qDebug() << "Received Protocol Object:";
                qDebug() << "MessageType:" << receivedProtocol.getMsgType();
                qDebug() << "Name:" << QString::fromStdString(receivedProtocol.getName());
                qDebug() << "Payload:" << QString::fromStdString(receivedProtocol.getPayload());

                // Handle the received Protocol message
                handleProtocolMessage(receivedProtocol);

            } catch (const std::exception& ex) {
                emit logMessage("Failed to deserialize Protocol: " + QString(ex.what()));
            }
        } else {
            break;
        }
    }
}

void Communicator::handleProtocolMessage(const Protocol& p)
{
    qDebug() << "wtf is happening";
    switch (p.getMsgType()) {
    case MessageType::MESSAGE_TRANSFER:
        qDebug() << "wtf das ist scheise: " << p.getName();
        if(p.getName() == "send_dm_response" || p.getName() == "send_channel_response") {
            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {
                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                emit sendMessageResponse(success, message);
            }
        } else if(p.getName() == "send_dm") {
            qDebug() << "got dm";
            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {
                // Zugriff auf die Werte
                int senderId = jsonObject["senderId"].toInt(-1);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                qDebug() << "notify session user";
                emit receivedMessageFromOtherUser(senderId, message);
            } else {
                qDebug() << "json parse Error";
            }
        } else if(p.getName() == "send_channel") {
            qDebug() << "got channel message";
            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {
                // Zugriff auf die Werte
                int senderId = jsonObject["senderId"].toInt(-1);
                int channelId = jsonObject["channelId"].toInt(-1);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                qDebug() << "notify session user";
                emit receivedMessageFromOtherUserInChannel(senderId, message, channelId);
            } else {
                qDebug() << "json parse Error";
            }
        }
        emit messageReceived(QString::fromStdString(p.getName()), QString::fromStdString(p.getPayload()));
        break;
    case MessageType::COMMAND_TRANSFER:
        // implement command_transfer

        if(p.getName() == "login_response" || p.getName() == "signup_response") {

            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {
                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                emit authResponseReceived(success, message, p.getName() == "login_response");
            }

        } else if(p.getName() == "check_user_exists_response") {

            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {

                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                emit chatCreationResponse(success, message, message.toInt());
            }
        } else if(p.getName() == "get_dmlist_by_userid_response") {

            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {

                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                qDebug() << message;
                emit getDmListResponse(success, message);
            }
        } else if(p.getName() == "get_chat_history_by_userid_response") {

            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {

                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");
                int receiverId = jsonObject["receiverId"].toString().toInt();

                qDebug() << message;
                emit getChatHistoryResponse(success, message, receiverId);
            }
        } else if(p.getName() == "create_channel_response") {

            QJsonObject jsonObject = parseJsonPayload(p.getPayload());

            if (!jsonObject.isEmpty()) {

                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");
                QString invite = jsonObject["invite"].toString();

                qDebug() << message;
                emit createChannelResponse(success, message, invite);
            }
        }

        emit logMessage("Command response received: " + QString::fromStdString(p.getPayload()));
        break;
    case MessageType::FILE_TRANSFER:
        // Handle file transfers if implemented
        emit logMessage("File transfer received.");
        break;
    default:
        emit logMessage("Unknown message type received.");
        break;
    }
}

QJsonObject Communicator::parseJsonPayload(const std::string& payload) {
    QString jsonQString = QString::fromStdString(payload);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonQString.toUtf8());

    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        return jsonDoc.object(); // Return the parsed JSON object
    }
    return {}; // Return an empty QJsonObject if parsing fails
}

void Communicator::error(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit logMessage("Socket error: " + _clientSocket->errorString());
}

bool Communicator::setSslCaCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(":/certs/" + path);

    if (!certificateFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open certificate file:" << path;
        return false;
    }

    _sslCaCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}

void Communicator::setSslProtocol(QSsl::SslProtocol Protocol)
{
    _sslProtocol = Protocol;
}
