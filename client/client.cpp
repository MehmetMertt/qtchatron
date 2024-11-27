#include "client.h"
#include "Communicator/Communicator.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent)
    : QObject{parent},
    _loading(true)
{}

QPair<QString, quint16> Client::loadConfiguration() {
    QString defaultServerIP = "127.0.0.1";
    quint16 defaultServerPort = 45000;

    QFile configFile("../config/config.json");
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

bool Client::loading() const
{
    return _loading;
}

void Client::setLoading(bool newLoading)
{
    _loading = newLoading;
    emit loadingChanged();
}

void Client::start() {
    Communicator *communicator = new Communicator();
    auto [address, port] = loadConfiguration();
    connect(communicator, &Communicator::encrypted, this, (std::bind(&Client::setLoading, this, false)));
    communicator->connectToServer(address, port);
    //free(communicator);
}
