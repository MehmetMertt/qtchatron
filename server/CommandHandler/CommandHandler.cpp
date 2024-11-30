#include "CommandHandler/CommandHandler.h"

#include <QString>
#include <QDebug>

CommandHandler::CommandHandler(QObject* parent) : QObject(parent) {}

std::string CommandHandler::routeCommand(const Command& command)
{
    std::string response;
    std::string cmd = command.command();
    std::string params = command.params();
    qDebug() << "route command:" << QString::fromStdString(cmd);

    if (cmd == "hello") {
        // Respond with "hello"
        response = "hello";
    }
    else if (cmd == "login") {
        // Respond with request for username
        response = "enter username";
    }
    else {
        // Handle unknown commands
        QString qCommand = QString::fromStdString(cmd);
        emit logMessage("Unknown command: " + qCommand);
        response = "Error: Unknown command";
    }

    return response;
}
