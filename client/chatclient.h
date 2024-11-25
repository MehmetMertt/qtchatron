#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QSslSocket>

class QHostAddress;
class QJsonDocument;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QString &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text, const QString &command);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
private:
    QSslSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);

    void onConnected();
};

#endif // CHATCLIENT_H
