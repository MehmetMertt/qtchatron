#include "AuthModel.h"
#include "AuthController.h" // Include the controller header
#include <QDebug>

#include "sessionmodel.h"

AuthModel::AuthModel(QObject *parent)
    : QObject(parent),
    _username(""),
    _password(""),
    _authController(new AuthController(this)) // Initialize the controller
{
}

QString AuthModel::username() const
{
    return _username;
}

void AuthModel::setUsername(const QString &username)
{
    if (_username != username) {
        _username = username;
        emit usernameChanged();
    }
}

QString AuthModel::password() const
{
    return _password;
}

void AuthModel::setPassword(const QString &password)
{
    if (_password != password) {
        _password = password;
        emit passwordChanged();
    }
}

void AuthModel::login()
{
    qDebug() << "Passing login credentials to AuthController: username:" << _username;

    // Pass the username and password to the AuthController
    _authController->login(_username, _password, [this](bool success, const QString &message) {
        if (success) {
            //SessionModel::instance()->setCurrentUser(new User(_username));
            emit authMethodSuccessful();
        } else {
            emit authMethodFailed(message);
        }
    });
}

void AuthModel::signup()
{
    qDebug() << "Passing signup credentials to AuthController: username:" << _username;

    // Pass the username and password to the AuthController
    _authController->signup(_username, _password, [this](bool success, const QString &message) {
        if (success) {
            emit authMethodSuccessful();
        } else {
            emit authMethodFailed(message);
        }
    });
}

void AuthModel::logout()
{
    //qDebug() << "Pass logout to AuthController: username" << SessionModel::instance()->currentUser()->username();

    _authController->logout([this](bool success, const QString &message) {
        if(success) {
            emit authMethodSuccessful();
            //remove SessionModel::getInstance().setCurrentUser(new User(_username));
        } else {
            emit authMethodFailed(message);
        }
    });
}
