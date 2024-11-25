#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <serverworker.h>
#include <QSslCertificate>
#include <QSslKey>

class Server : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    explicit Server(QObject *parent = nullptr);
    void start();
    void setSslLocalCertificate(const QSslCertificate &certificate);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);

    void setSslPrivateKey(const QSslKey &key);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa, QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());

    void setSslProtocol(QSsl::SslProtocol protocol);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void logMessage(const QString &msg);
public slots:
    void stopServer();
private slots:
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);
private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    QVector<ServerWorker *> m_clients;

    QSslCertificate m_sslLocalCertificate;
    QSslKey m_sslPrivateKey;
    QSsl::SslProtocol m_sslProtocol;

    void onNewConnection();
};

#endif // SERVER_H
