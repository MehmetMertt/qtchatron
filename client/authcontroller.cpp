#include "authcontroller.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "Communicator/Communicator.h"
#include "Protocol/protocol.h"
#include "sessionuser.h"

AuthController::AuthController(QObject *parent)
    : QObject(parent)
{
}

std::string AuthController::dataToJsonString(const QString &username, const QString &password) {
    QJsonObject jsonObject;
    jsonObject["username"] = username;
    jsonObject["password"] = password;

    QJsonDocument jsonDoc(jsonObject);

    return QString(jsonDoc.toJson(QJsonDocument::Compact)).toStdString();
}

void AuthController::login(const QString &username, const QString &password,
                           const std::function<void(bool, const QString &)> &callback)
{
    //qDebug() << "Authenticating login with username:" << username;

    _authCallback = callback;
    _username = username;

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::authResponseReceived, this, &AuthController::handleAuthResponseCallback);
    connect(communicator, &Communicator::authResponseReceived, this, &AuthController::handleAuthResponseCallback);


    communicator->sendData(Protocol(MessageType::COMMAND_TRANSFER, "login_request", this->dataToJsonString(username, password)));

}

void AuthController::handleAuthResponseCallback(const bool success, const QString message, const int authLogin)
{
    //qDebug() << "login response: " << success << ": " << message;

    QString callbackMessage = message;

    if(message.contains("unexpected")) {
        callbackMessage = "An unexpected error occured";
    }

    qDebug() << authLogin;

    if(success && authLogin) {
        qDebug() << "setting new user";
        SessionUser::getInstance()->setUser(new User(_username));
        SessionUser::getInstance()->setToken(message);
        SessionUser::getInstance()->loadData();
    }

    if (_authCallback) {
        _authCallback(success, callbackMessage);
        _authCallback = nullptr; // Reset to avoid calling it multiple times
    }
}



void AuthController::signup(const QString &username, const QString &password,
                            const std::function<void(bool, const QString &)> &callback)
{
    //qDebug() << "Processing signup for username:" << username;

    _authCallback = callback;

    auto *communicator = Communicator::getInstance();
    disconnect(communicator, &Communicator::authResponseReceived, this, &AuthController::handleAuthResponseCallback);
    connect(communicator, &Communicator::authResponseReceived, this, &AuthController::handleAuthResponseCallback);


    communicator->sendData(Protocol(MessageType::COMMAND_TRANSFER, "signup_request", this->dataToJsonString(username, password)));
}

void AuthController::logout(const std::function<void (bool, const QString &)> &callback)
{
    //TODO: Remove current user from Session


    callback(true, "Logout successful");
}
