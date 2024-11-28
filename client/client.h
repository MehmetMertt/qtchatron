#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "Communicator/Communicator.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void start();

private:
    QPair<QString, quint16> loadConfiguration();
    Communicator _communicator;

signals:
    void encryptionSuccess();
};

#endif // CLIENT_H
