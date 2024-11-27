#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include "client.h"

class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager(QObject *parent = nullptr);

    Client *getClient() const;
    void setClient(Client *newClient);

private:
    Client *_client;

    Q_PROPERTY(Client *_client READ getClient WRITE setClient NOTIFY clientChanged FINAL)

signals:
    void clientChanged();
};

#endif // CLIENTMANAGER_H
