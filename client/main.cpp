#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include  <Communicator/Communicator.h>

QPair<QString, quint16> loadConfiguration();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    qmlRegisterSingletonType(QUrl("qrc:/styles/Style.qml"), "Style", 1, 0, "Style");
    const QUrl url(QStringLiteral("qrc:/view/Main.qml"));

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    Communicator client;
    auto [address, port] = loadConfiguration();
    client.connectToServer(address, port);

    return app.exec();
}

QPair<QString, quint16> loadConfiguration() {
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
