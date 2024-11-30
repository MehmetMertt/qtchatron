#include "Server/Server.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

Server::Server(QHostAddress address, quint16 port, QObject *parent)
    : QTcpServer(parent)
{
    _address = address;
    _port = port;
    setSslLocalCertificate("server.crt");
    setSslPrivateKey("server.key");
    setSslProtocol(QSsl::TlsV1_3OrLater);
}

void Server::start() {

    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (this->listen(_address, _port))
        qDebug().nospace() << "Now listening on " << qPrintable(_address.toString()) << ":" << _port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(_address.toString()) << ":" << _port;
}

void Server::handleMessageReceived(ServerWorker* sender, const Protocol& p)
{
    Q_ASSERT(sender);
    qDebug() << "ok";
            // Handle the message based on its type
    switch (p.getMsgType()) {
    case MessageType::COMMAND_TRANSFER: {
        std::string command = p.getName();
        std::string params = p.getPayload();
        Command cmd(command,params);
        // Process the command using CommandHandler
        std::string responsePayload;
        try {

            responsePayload = commandHandler.routeCommand(cmd);
        } catch (const std::exception& ex) {
            responsePayload = std::string("Error: ") + ex.what();
        }

        // Create a redsponse Protocol message
        Protocol responseProtocol(MessageType::COMMAND_TRANSFER, "Server", responsePayload);

        // Send the response back to the client
        sender->sendData(responseProtocol);
        break;
    }

    case MessageType::MESSAGE_TRANSFER: {
        // Handle general messages
        QString senderName = QString::fromStdString(p.getName());
        QString message = QString::fromStdString(p.getPayload());

        emit logMessage(senderName + ": " + message);
        break;
    }

    case MessageType::FILE_TRANSFER: {
        // Handle file transfers if implemented
        emit logMessage("File transfer received.");
        break;
    }

    default:
        emit logMessage("Unknown message type received.");
        break;
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket(this);

    sslSocket->setSocketDescriptor(socketDescriptor);
    sslSocket->setLocalCertificate(_sslLocalCertificate);
    sslSocket->setPrivateKey(_sslPrivateKey);
    sslSocket->setProtocol(_sslProtocol);
    sslSocket->startServerEncryption();

    this->addPendingConnection(sslSocket);
}

void Server::onNewConnection() {

    QSslSocket *sslSocket = qobject_cast<QSslSocket*>(this->nextPendingConnection());

    if (!sslSocket) {
        qDebug() << "Error: Failed to cast QTcpSocket to QSslSocket";
        return;
    }

    ServerWorker *worker = new ServerWorker(sslSocket, this);

    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&Server::userError, this, worker));
    connect(worker, &ServerWorker::messageReceived,this,&Server::handleMessageReceived);
    connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);

    _clients.append(worker);

    //emit logMessage(QStringLiteral("New client Connected"));
    qDebug() << "New client connected";
}


void Server::userDisconnected(ServerWorker *sender)
{
    _clients.removeAll(sender);

    QJsonObject disconnectedMessage;
    disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
    emit logMessage(QStringLiteral(" disconnected"));
    qDebug() << QStringLiteral(" disconnected");

    sender->deleteLater();
}

void Server::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QStringLiteral("Error from "));
}

void Server::stopServer()
{
    for (ServerWorker *worker : _clients) {
        worker->disconnectFromClient();
    }
    close();
}

bool Server::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(QStringLiteral("../certs/") + path);

    if (!certificateFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open certificate file:" << path;
        return false;
    }

    _sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return !_sslLocalCertificate.isNull();
}

bool Server::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile("../certs/"+fileName);

    if (!keyFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open private key file:" << fileName;
        return false;
    }

    _sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void Server::setSslProtocol(QSsl::SslProtocol Protocol)
{
    _sslProtocol = Protocol;
}
