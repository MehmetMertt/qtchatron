// Communicator.h
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSslSocket>
#include "Protocol/Protocol.h"

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    void connectToServer(const QString &address, quint16 port);
    void disconnectFromHost();

    // General send function
    void sendData(const Protocol& p);

signals:
    void logMessage(const QString &message);
    void messageReceived(const QString &sender, const QString &message);
    void socketEncryptionSuccess();

private slots:
    void onEncrypted();
    void onConnected();
    void onReadyRead();
    void error(QAbstractSocket::SocketError socketError);

private:
    void handleProtocolMessage(const Protocol& p);
    bool setSslCaCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslProtocol(QSsl::SslProtocol Protocol);

    QSslSocket *_clientSocket;
    QSslCertificate _sslCaCertificate;
    QSsl::SslProtocol _sslProtocol;
};

#endif // COMMUNICATOR_H
