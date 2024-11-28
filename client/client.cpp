#include "client.h"


#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent)
    : QObject{parent}
{}

QPair<QString, quint16> Client::loadConfiguration() {
    QString defaultServerIP = "127.0.0.1";
    quint16 defaultServerPort = 45000;

    QFile configFile(":/config/config.json");
    if (!configFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open config file.";
        return QPair<QString, quint16>(defaultServerIP, defaultServerPort); // Default values
    }

    QByteArray data = configFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject config = doc.object();

    QString address = config["serverAddress"].toString(defaultServerIP);
    quint16 port = static_cast<quint16>(config["port"].toInt(defaultServerPort));

    qDebug() << address << ": " << port;

    return QPair<QString, quint16>(address, port);
}

void Client::start() {
    auto [address, port] = loadConfiguration();
    connect(&_communicator, &Communicator::socketEncrypted, this, [this]()->void{emit encryptionSuccess();});
    _communicator.connectToServer(address, port);
}
