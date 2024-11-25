#include "server.h"
#include <QSslKey>
#include <QSslCertificate>
#include <QFile>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSslConfiguration>
#include <QDir>

Server::Server(QObject *parent) : QObject(parent)
{
    // Load SSL certificates and private keys for the server
    if (!loadSslCertificate()) {
        qWarning() << "Failed to load SSL certificate!";
        return;
    }

    // Start the TCP server to listen for new connections
    connect(&_tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (_tcpServer.listen(QHostAddress::Any, 45000)) {
        qInfo() << "Server listening on port 45000...";
    } else {
        qWarning() << "Failed to start server!";
    }
}

bool Server::loadSslCertificate()
{
    QDir resourceDir(":/");
    qDebug() << "Resource directory contents:" << resourceDir.entryList();

    // Load server certificate and private key
    // !!!! This certificate is only for development !!!!!
    QFile certFile("../certs/server.crt");
    QFile keyFile("../certs/server.key");

    if (!certFile.open(QIODevice::ReadOnly) || !keyFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Error loading certificate or key file.";
        return false;
    }

    QSslCertificate cert(&certFile, QSsl::Pem);
    QSslKey key(&keyFile, QSsl::Rsa);

    qDebug() << cert << "\n" << key << "\n";

    if (cert.isNull() || key.isNull()) {
        qWarning() << "Error parsing certificate or key.";
        return false;
    }

    // Set the certificate and private key to the server
    _sslSocket.setLocalCertificate(cert);
    _sslSocket.setPrivateKey(key);

    // Set the SSL mode to server
    _sslSocket.setPeerVerifyMode(QSslSocket::VerifyNone);
    _sslSocket.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    return true;
}

void Server::sendMessage(const QString &message)
{
    emit newMessage("Server: " + message.toUtf8());
}

void Server::onNewConnection()
{
    const auto client = _tcpServer.nextPendingConnection();
    if(client == nullptr) {
        qInfo() << "client failure.\n";
        return;
    }

    qInfo() << "New client connected.";

    QSslSocket *sslClient = new QSslSocket(this);
    sslClient->setProtocol(QSsl::TlsV1_3OrLater);
    // Set the socket descriptor to the pending connection
    sslClient->setSocketDescriptor(client->socketDescriptor());

    // Start the SSL handshake
    sslClient->startServerEncryption();
    connect(sslClient, &QSslSocket::encrypted, this, &Server::onClientEncrypted);
    _clients.insert(this->getClientKey(sslClient), sslClient);

    connect(sslClient, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(sslClient, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
}

void Server::onReadyRead()
{
    qDebug() << "1\n";
    const auto client = qobject_cast<QSslSocket*>(sender());
    qDebug() << "2\n";

    if(client == nullptr) {
        qDebug() << "client failure\n";
        return;
    }

    const auto message = this->getClientKey(client).toUtf8() + ": " + client->readAll();

    qDebug() << "message: " << message << "\n";

    emit newMessage(message);
}

void Server::onClientEncrypted()
{
    const auto client = qobject_cast<QSslSocket*>(sender());

    if (client == nullptr) {
        return;
    }

    qInfo() << "SSL connection established with" << getClientKey(client);
}

void Server::onClientDisconnected()
{
    const auto client = qobject_cast<QSslSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    qInfo() << "Client disconnected:" << getClientKey(client);
    _clients.remove(getClientKey(client));
}

void Server::onNewMessage(const QByteArray &ba)
{
    for (const auto &client : std::as_const(_clients)) {
        client->write(ba);
        client->flush();
    }
}

QString Server::getClientKey(const QSslSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}

void Server::printClients()
{
    qInfo() << "Printing list of connected clients:";

    for (auto it = _clients.begin(); it != _clients.end(); ++it) {
        QString clientKey = it.key();               // Key (client identifier)
        QSslSocket *clientSocket = it.value();      // Value (QSslSocket pointer)

        if (clientSocket) {
            qInfo() << "Client Key:" << clientKey
                    << ", Peer Address:" << clientSocket->peerAddress().toString()
                    << ", Peer Port:" << clientSocket->peerPort()
                    << ", State:" << clientSocket->state();
        } else {
            qWarning() << "Null QSslSocket for client key:" << clientKey;
        }
    }
}
/*
void Server::onClientEncrypted() {
    qInfo() << "SSL handshake completed successfully.";
}
*/
