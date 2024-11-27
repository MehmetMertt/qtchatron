#include "clientmanager.h"

ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    _client = new Client();
}

Client *ClientManager::getClient() const
{
    return _client;
}

void ClientManager::setClient(Client *newClient)
{
    if (_client == newClient)
        return;
    _client = newClient;
    emit clientChanged();
}
