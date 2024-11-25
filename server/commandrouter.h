#ifndef COMMANDROUTER_H
#define COMMANDROUTER_H

#include <QJsonObject>
#include <QObject>

class CommandRouter : public QObject
{
    Q_OBJECT

public:
    CommandRouter(QObject* parent = nullptr);

    QJsonObject routeCommand(const QJsonObject& jsonObj);

signals:
    void jsonResponse(const QJsonObject& response);
    void logMessage(const QString& message);
};

#endif // COMMANDROUTER_H
