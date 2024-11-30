#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include "Protocol/Protocol.h"
#include <QSslSocket>

class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)
public:
    explicit ServerWorker(QSslSocket *socket, QObject *parent = nullptr);
    void sendData(const Protocol& p);
    void receiveData();
signals:
    //void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void messageReceived(ServerWorker* worker, Protocol receivedProtocol);
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
private:
    QSslSocket *_serverSocket;
};

#endif // SERVERWORKER_H
