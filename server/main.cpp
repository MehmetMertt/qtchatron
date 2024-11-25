#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <server.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);



    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("appserver", "Main");

    Server server;

    return app.exec();
}
