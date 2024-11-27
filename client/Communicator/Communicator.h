#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSslSocket>

class QHostAddress;
class QJsonDocument;
class Communicator : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Communicator)
public:
    explicit Communicator(QObject *parent = nullptr);

public slots:
    void connectToServer(const QString &address, quint16 port);
    void sendMessage(const QString &text, const QString &command);
    void disconnectFromHost();

private slots:
    void onReadyRead();

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void encrypted();

private:
    QSslSocket *_clientSocket;
    QSslCertificate _sslCaCertificate;
    QSsl::SslProtocol _sslProtocol;

    void jsonReceived(const QJsonObject &doc);
    void onConnected();
    void onEncrypted();
    bool setSslCaCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslProtocol(QSsl::SslProtocol protocol);
};

#endif // COMMUNICATOR_H
