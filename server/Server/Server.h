#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <Server/ServerWorker.h>
#include <QSslCertificate>
#include <QSslKey>
#include <CommandHandler/CommandHandler.h>

class Server : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    explicit Server(QHostAddress address = QHostAddress::Any, quint16 port = 45000, QObject *parent = nullptr);
    void start();
    void handleMessageReceived(ServerWorker* sender, const protocol& p);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();

private slots:
   // void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);

private:
    void onNewConnection();
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa, QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());
    void setSslProtocol(QSsl::SslProtocol protocol);

    QVector<ServerWorker *> _clients;

    QSslCertificate _sslLocalCertificate;
    QSslKey _sslPrivateKey;
    QSsl::SslProtocol _sslProtocol;

    QHostAddress _address;
    quint16 _port;
    CommandHandler commandHandler;

};

#endif // SERVER_H
