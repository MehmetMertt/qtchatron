#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "sessionuser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SessionUser* sessionUser = SessionUser::getInstance();
    qmlRegisterSingletonInstance<SessionUser>("ClientObjects", 1, 0, "SessionUser", sessionUser);

    const QUrl url(QStringLiteral("qrc:/view/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
