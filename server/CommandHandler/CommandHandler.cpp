#include "CommandHandler/CommandHandler.h"

#include <QString>
#include <QDebug>

CommandHandler::CommandHandler(QObject* parent) : QObject(parent), _dbHandler(new databaseHandler()) {}

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
    else if (cmd == "login_request") {
        // Respond with request for username
        QString jsonQString = QString::fromStdString(params);

        // Konvertiere den QString in ein QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonQString.toUtf8());

        // Überprüfen, ob das Dokument gültiges JSON enthält
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();

            // Zugriff auf die Werte
            QString username = jsonObject["username"].toString();
            QString password = jsonObject["password"].toString();

            qDebug() << "Username:" << username;
            qDebug() << "Password:" << password;

            auto dbResponse = _dbHandler->LoginUser(username, password);

            qDebug() << "db response: " << dbResponse->success() << ": " << dbResponse->message();
            QJsonObject responseObject;
            responseObject["success"] = dbResponse->success();
            responseObject["message"] = dbResponse->message();

            QJsonDocument responseJsonDoc(responseObject);

            return QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
        } else {
            qWarning() << "Ungültiges JSON-Format!";
        }
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

QString CommandHandler::getCommandResponseName(const Command &command)
{
    if(command.command() == "login_request") {
        return "login_response";
    } else {
        return "unknown response";
    }
}
