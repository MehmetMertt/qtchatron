/*
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>

class communicator : public QObject
{
    Q_OBJECT
public:
    explicit communicator(QObject *parent = nullptr);

signals:
};

#endif // COMMUNICATOR_H
*/

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslKey>

class Communicator : public QObject
{
    Q_OBJECT

public:
    explicit Communicator(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message);

private slots:
    void onConnected();
    void onReadyRead();
    void onSslErrors(const QList<QSslError> &errors);

private:
    QSslSocket _socket;
};

#endif // COMMUNICATOR_H
//*/
