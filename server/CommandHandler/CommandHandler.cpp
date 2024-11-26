#include "CommandHandler/CommandHandler.h"

#include <QJsonObject>

CommandHandler::CommandHandler(QObject* parent) : QObject(parent) {}

QJsonObject CommandHandler::routeCommand(const QJsonObject& jsonObj)
{
    QJsonObject response;
    response[QStringLiteral("type")] = QStringLiteral("message");
    if (jsonObj.contains("command")) {
        QString command = jsonObj["command"].toString();

        qDebug() << "route command " << command;

        if (command == "hello") {
            // Respond with "hello"

            response["text"] = "hello";
            emit jsonResponse(response);
        }
        else if (command == "login") {
            // Respond with request for username
            response["text"] = "enter username";
            emit jsonResponse(response);
        }
        else {
            response["text"] = "Error";
            // Handle unknown commands
            emit logMessage("Unknown command: " + command);
        }

    } else {
        emit logMessage("Invalid message: Missing 'command' field");
        response["text"] = "Error";
    }
    return response;
}
