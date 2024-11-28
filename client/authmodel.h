#ifndef AUTHMODEL_H
#define AUTHMODEL_H

#include <QObject>
#include <QtQml>

#include "authcontroller.h"

class AuthModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // Expose username and password as properties
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    explicit AuthModel(QObject *parent = nullptr);

    // QML bindings for login and signup
    Q_INVOKABLE void login();
    Q_INVOKABLE void signup();

    // Username getter and setter
    QString username() const;
    void setUsername(const QString &username);

    // Password getter and setter
    QString password() const;
    void setPassword(const QString &password);

signals:
    void usernameChanged();
    void passwordChanged();
    void loginSuccessful();
    void loginFailed(const QString &reason);

private:
    QString _username;
    QString _password;

    AuthController* _authController;
};

#endif // AUTHMODEL_H
