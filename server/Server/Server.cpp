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
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);

    _clients.append(worker);

    //emit logMessage(QStringLiteral("New client Connected"));
    qDebug() << "New client connected";
}



void Server::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void Server::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    //emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));

    auto response = commandHandler.routeCommand(doc);
    sendJson(sender, response);
}

void Server::userDisconnected(ServerWorker *sender)
{
    _clients.removeAll(sender);

    QJsonObject disconnectedMessage;
    disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
    emit logMessage(QLatin1String(" disconnected"));
    qDebug() << QLatin1String(" disconnected");

    sender->deleteLater();
}

void Server::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from "));
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
    QFile certificateFile("../certs/"+path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    _sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}

bool Server::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile("../certs/"+fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    _sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void Server::setSslProtocol(QSsl::SslProtocol protocol)
{
    _sslProtocol = protocol;
}
