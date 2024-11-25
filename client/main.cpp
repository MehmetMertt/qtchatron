#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <communicator.h>

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
    engine.loadFromModule("appclient", "Main");

    Communicator communicator;
    communicator.connectToServer("127.0.0.1", 45000);


    return app.exec();
}
