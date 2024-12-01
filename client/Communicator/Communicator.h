// Communicator.h
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSslSocket>
#include "Protocol/Protocol.h"
#include <mutex>


class Communicator : public QObject
{
    Q_OBJECT
public:
    static Communicator* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Communicator();
        }
        return instance;
    }

    void connectToServer(const QString &address, quint16 port);
    void disconnectFromHost();

    // General send function
    void sendData(const Protocol& p);

signals:
    void logMessage(const QString &message);
    void messageReceived(const QString &sender, const QString &message);
    void socketEncryptionSuccess();
    void loginResponseReceived(const bool success, const QString message);

private slots:
    void onEncrypted();
    void onConnected();
    void onReadyRead();
    void error(QAbstractSocket::SocketError socketError);

private:
    Communicator(QObject *parent = nullptr);
    Communicator(const Communicator&) = delete; // Prevent copy constructor
    Communicator& operator=(const Communicator&) = delete; // Prevent copy assignment

    static Communicator* instance;
    static std::mutex mtx;

    void handleProtocolMessage(const Protocol& p);
    bool setSslCaCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslProtocol(QSsl::SslProtocol Protocol);

    QSslSocket *_clientSocket;
    QSslCertificate _sslCaCertificate;
    QSsl::SslProtocol _sslProtocol;
};


#endif // COMMUNICATOR_H
