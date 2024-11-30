// Communicator.h
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSslSocket>
#include "Protocol/protocol.h"

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    void connectToServer(const QString &address, quint16 port);
    void disconnectFromHost();

    // General send function
    void sendData(const protocol& p);

signals:
    void logMessage(const QString &message);
    void messageReceived(const QString &sender, const QString &message);

private slots:
    void onEncrypted();
    void onConnected();
    void onReadyRead();
    void error(QAbstractSocket::SocketError socketError);

private:
    void handleProtocolMessage(const protocol& p);
    bool setSslCaCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslProtocol(QSsl::SslProtocol protocol);

    QSslSocket *_clientSocket;
    QSslCertificate _sslCaCertificate;
    QSsl::SslProtocol _sslProtocol;
};

#endif // COMMUNICATOR_H
