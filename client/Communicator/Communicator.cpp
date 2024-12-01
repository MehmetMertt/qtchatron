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
    switch (p.getMsgType()) {
    case MessageType::MESSAGE_TRANSFER:
        emit messageReceived(QString::fromStdString(p.getName()), QString::fromStdString(p.getPayload()));
        break;
    case MessageType::COMMAND_TRANSFER:
        // implement command_transfer

        if(p.getName() == "login_response") {

            QString jsonQString = QString::fromStdString(p.getPayload());

            // Konvertiere den QString in ein QJsonDocument
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonQString.toUtf8());

            // Überprüfen, ob das Dokument gültiges JSON enthält
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                // Zugriff auf die Werte
                bool success = jsonObject["success"].toBool(false);
                QString message = jsonObject["message"].toString("An unexpected error occured!");

                emit loginResponseReceived(success, message);
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
