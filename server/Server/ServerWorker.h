#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QSslSocket>

class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QSslSocket *socket, QObject *parent = nullptr);
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
    QSslSocket *_serverSocket;
};

#endif // SERVERWORKER_H
