#include "communicator.h"
#include <QDebug>

Communicator::Communicator(QObject *parent) : QObject(parent)
{
    // Connect signals for socket events
    connect(&_socket, &QSslSocket::connected, this, &Communicator::onConnected);
    connect(&_socket, &QSslSocket::readyRead, this, &Communicator::onReadyRead);
    connect(&_socket, QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors), this, &Communicator::onSslErrors);
}

void Communicator::connectToServer(const QString &host, quint16 port)
{
    qDebug() << "Connecting to server...";

    // Load certificate (optional for mutual SSL; skip if not using client-side certs)
    // QFile certFile(":/client.crt");
    // QFile keyFile(":/client.key");

    // Uncomment this if using client certificates:
    // QSslCertificate certificate(&certFile, QSsl::Pem);
    // QSslKey key(&keyFile, QSsl::Rsa, QSsl::Pem);
    // _socket.setLocalCertificate(certificate);
    // _socket.setPrivateKey(key);

    // Ignore SSL errors for self-signed certificates (for development only)
    _socket.ignoreSslErrors();

    // Connect to server with SSL
    _socket.connectToHostEncrypted(host, port);
}

void Communicator::sendMessage(const QString &message)
{
    if (_socket.state() == QAbstractSocket::ConnectedState) {
        _socket.write(message.toUtf8());
        _socket.flush();
    } else {
        qWarning() << "Not connected to server.";
    }
}

void Communicator::onConnected()
{
    qDebug() << "Successfully connected to server!";
    sendMessage("Hello from SSL Communicator!");  // Example message
}

void Communicator::onReadyRead()
{
    QByteArray data = _socket.readAll();
    qDebug() << "Received from server:" << data;
}

void Communicator::onSslErrors(const QList<QSslError> &errors)
{
    for (const QSslError &error : errors) {
        qWarning() << "SSL Error:" << error.errorString();
    }
    // For development purposes, ignore SSL errors (don't do this in production!)
    _socket.ignoreSslErrors();
}
