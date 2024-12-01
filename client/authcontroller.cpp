#include "authcontroller.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "Communicator/Communicator.h"
#include "Protocol/protocol.h"

AuthController::AuthController(QObject *parent)
    : QObject(parent)
{
}

void AuthController::login(const QString &username, const QString &password,
                           const std::function<void(bool, const QString &)> &callback)
{
    qDebug() << "Authenticating login with username:" << username;

    _loginCallback = callback;

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::loginResponseReceived, this, &AuthController::handleLoginResponse);
    connect(communicator, &Communicator::loginResponseReceived, this, &AuthController::handleLoginResponse);

    QJsonObject jsonObject;
    jsonObject["username"] = username;
    jsonObject["password"] = password;

    QJsonDocument jsonDoc(jsonObject);

    communicator->sendData(Protocol(MessageType::COMMAND_TRANSFER, "login_request", QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString()));

    // Simulate backend call
   /* if (username == "admin" && password == "password") {
        callback(true, "Login successful");
    } else {
        callback(false, "Invalid username or password");
    }*/
}

void AuthController::handleLoginResponse(const bool success, const QString message)
{
    qDebug() << "login response: " << success << ": " << message;

    QString callbackMessage = message;

    if(message.contains("unexpected")) {
        callbackMessage = "An unexpected error occured";
    }

    if (_loginCallback) {
        _loginCallback(success, callbackMessage);
        _loginCallback = nullptr; // Reset to avoid calling it multiple times
    }
}



void AuthController::signup(const QString &username, const QString &password,
                            const std::function<void(bool, const QString &)> &callback)
{
    qDebug() << "Processing signup for username:" << username;

    // Simulate backend call
    if (!username.isEmpty() && !password.isEmpty()) {
        callback(true, "Signup successful");
    } else {
        callback(false, "Invalid data");
    }
}

void AuthController::logout(const std::function<void (bool, const QString &)> &callback)
{
    //TODO: Remove current user from Session


    callback(true, "Logout successful");
}
