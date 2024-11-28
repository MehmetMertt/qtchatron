#include "AuthController.h"
#include <QDebug>

AuthController::AuthController(QObject *parent)
    : QObject(parent)
{
}

void AuthController::login(const QString &username, const QString &password,
                           const std::function<void(bool, const QString &)> &callback)
{
    qDebug() << "Authenticating login with username:" << username;

    // Simulate backend call
    if (username == "admin" && password == "password") {
        callback(true, "Login successful");
    } else {
        callback(false, "Invalid username or password");
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
