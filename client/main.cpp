#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>
//#include <client.h>
#include <clientmanager.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    qmlRegisterSingletonType(QUrl("qrc:/styles/Style.qml"), "Style", 1, 0, "Style");
    const QUrl url(QStringLiteral("qrc:/view/Main.qml"));

    QQmlApplicationEngine engine;
    ClientManager *clientManager = new ClientManager(&engine);
    engine.rootContext()->setContextProperty("ClientManager", clientManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    //qmlRegisterType<Client>("/client", 1, 0, "Client");
    //engine.rootContext()->setContextObject(client);
    engine.load(url);

    // show loading screen
    // ...
    // show main page

    return app.exec();
}
