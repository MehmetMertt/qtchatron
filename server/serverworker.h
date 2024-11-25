#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QSslSocket>
#include <commandrouter.h>

class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QSslSocket *socket, QObject *parent = nullptr);
    QString userName() const;
    void setUserName(const QString &userName);
    void sendJson(const QJsonObject &jsonData);
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    QSslSocket *m_serverSocket;
    QString m_userName;
    CommandRouter* m_commandRouter = new CommandRouter();
};

#endif // SERVERWORKER_H
