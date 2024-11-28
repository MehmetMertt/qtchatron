#include "clientcontroller.h"

#include <unistd.h>

ClientController::ClientController(QObject *parent)
    : QObject{parent}
{}

void ClientController::runClient()
{
    qDebug() << "running client";
    connect(&_client, &Client::encryptionSuccess, this, [this]()->void{
        sleep(2);
        emit clientReady();
    });
    _client.start();
}
