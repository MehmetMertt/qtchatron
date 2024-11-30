#include "CommandHandler/CommandHandler.h"

#include <QString>
#include <QDebug>

CommandHandler::CommandHandler(QObject* parent) : QObject(parent) {}

std::string CommandHandler::routeCommand(const std::string& command, const std::string& params)
{
    std::string response;

    qDebug() << "route command:" << QString::fromStdString(command);

    if (command == "hello") {
        // Respond with "hello"
        response = "hello";
    }
    else if (command == "login") {
        // Respond with request for username
        response = "enter username";
    }
    else {
        // Handle unknown commands
        QString qCommand = QString::fromStdString(command);
        emit logMessage("Unknown command: " + qCommand);
        response = "Error: Unknown command";
    }

    return response;
}
