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

    if (cmd == "get_dmlist_by_userid") {
        QString token = QString::fromStdString(params);
        QString userId = _dbHandler->getIDByToken(token)->message();

        auto dbResponse = _dbHandler->getAllDirectMessagesByUserID(userId);

        QJsonObject responseObject;
        responseObject["success"] = dbResponse->success();
        responseObject["message"] = dbResponse->message();

        QJsonDocument responseJsonDoc(responseObject);

        return QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
    } else if (cmd == "get_chat_history_by_userid") {
        QString jsonQString = QString::fromStdString(params);

        // Konvertiere den QString in ein QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonQString.toUtf8());

        // Überprüfen, ob das Dokument gültiges JSON enthält
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();

            // Zugriff auf die Werte
            QString token = jsonObject["token"].toString();
            QString receiverId = jsonObject["receiver_id"].toString();
            QString userId = _dbHandler->getIDByToken(token)->message();

            auto dbResponse = _dbHandler->getDirectMessagesBetweenUserByID(userId, receiverId);

            QJsonObject responseObject;
            responseObject["success"] = dbResponse->success();
            responseObject["message"] = dbResponse->message();
            responseObject["receiverId"] = dbResponse->extra();

            qDebug() << dbResponse->message();

            QJsonDocument responseJsonDoc(responseObject);

            return QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
        }
    }
    else if (cmd == "login_request" || cmd == "signup_request") {
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

            auto dbResponse = cmd == "login_request" ? _dbHandler->LoginUser(username, password) : _dbHandler->AddUser(username, password, "");

            qDebug() << "db response: " << dbResponse->success() << ": " << dbResponse->message();
            QJsonObject responseObject;
            responseObject["success"] = dbResponse->success();
            responseObject["message"] = dbResponse->message();

            QJsonDocument responseJsonDoc(responseObject);

            return QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
        } else {
            qWarning() << "Ungültiges JSON-Format!";
        }
    } else if(cmd == "check_user_exists") {
        QString username = QString::fromStdString(params);

        auto dbResponse = _dbHandler->checkIfUserExists(username);

        QJsonObject responseObject;
        responseObject["success"] = dbResponse->success();
        responseObject["message"] = dbResponse->message();

        QJsonDocument responseJsonDoc(responseObject);

        return QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();

    } else {
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
    } else if(command.command() == "signup_request") {
        return "signup_response";
    } else if(command.command() == "check_user_exists") {
        return "check_user_exists_response";
    } else if(command.command() == "get_dmlist_by_userid") {
        return "get_dmlist_by_userid_response";
    } else if(command.command() == "get_chat_history_by_userid") {
        return "get_chat_history_by_userid_response";
    }else {
        return "unknown response";
    }
}

databaseHandler *CommandHandler::dbHandler()
{
    return _dbHandler;
}
