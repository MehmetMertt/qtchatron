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
    connect(&_sslServer, &QSslServer::newConnection, this, &Server::onNewConnection);

    if (_sslServer.listen(QHostAddress::Any, 45000)) {
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
    // Accept the new TCP connection
    QTcpSocket *client = _sslServer.nextPendingConnection();
    if (client == nullptr) {
        return;
    }

    qInfo() << "New client connected.";

    // Upgrade the client connection to SSL
    QSslSocket *sslClient = new QSslSocket(this);
    connect(sslClient, &QSslSocket::encrypted, this, &Server::onClientEncrypted);
    connect(sslClient, &QSslSocket::disconnected, this, &Server::onClientDisconnected);

    sslClient->setProtocol(QSsl::TlsV1_3OrLater);
    sslClient->setSocketDescriptor(client->socketDescriptor());
    sslClient->startServerEncryption();  // Start SSL handshake

    _clients.insert(getClientKey(sslClient), sslClient);

    connect(sslClient, &QSslSocket::readyRead, this, &Server::onReadyRead);
}

void Server::onReadyRead()
{
    const auto client = qobject_cast<QSslSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    const auto message = this->getClientKey(client).toUtf8() + ": " + client->readAll();

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
