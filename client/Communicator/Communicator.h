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
    void authResponseReceived(const bool success, const QString message, const int authLogin);
    void chatCreationResponse(const bool success, const QString message, const int receiverUserId);
    void sendMessageResponse(const bool success, const QString message);
    void receivedMessageFromOtherUser(const int senderId, const QString message);
    void getDmListResponse(const bool success, const QString message);
    void getChatHistoryResponse(const bool success, const QString message, const int receiverId);

private slots:
    void onEncrypted();
    void onConnected();
    void onReadyRead();
    void error(QAbstractSocket::SocketError socketError);

private:
    Communicator(QObject *parent = nullptr);
    Communicator(const Communicator&) = delete; // Prevent copy constructor
    Communicator& operator=(const Communicator&) = delete; // Prevent copy assignment

    QJsonObject parseJsonPayload(const std::string& payload);

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
