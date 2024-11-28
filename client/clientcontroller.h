#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QtQml>

#include "client.h"

class ClientController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ClientController(QObject *parent = nullptr);

    Q_INVOKABLE void runClient();

private:
    Client _client;

signals:
    void clientReady();
};

#endif // CLIENTCONTROLLER_H
