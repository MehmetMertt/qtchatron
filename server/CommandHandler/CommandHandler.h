#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QJsonObject>
#include <QObject>

class CommandHandler : public QObject
{
    Q_OBJECT

public:
    CommandHandler(QObject* parent = nullptr);

    QJsonObject routeCommand(const QJsonObject& jsonObj);

signals:
    void jsonResponse(const QJsonObject& response);
    void logMessage(const QString& message);
};

#endif // COMMANDHANDLER_H
