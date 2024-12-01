#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include <functional>

class AuthController : public QObject
{
    Q_OBJECT

public:
    explicit AuthController(QObject *parent = nullptr);

    void login(const QString &username, const QString &password,
               const std::function<void(bool, const QString &)> &callback);

    void handleLoginResponse(const bool success, const QString message);

    void signup(const QString &username, const QString &password,
                const std::function<void(bool, const QString &)> &callback);

    void logout(const std::function<void(bool, const QString &)> &callback);

private:
    std::function<void(bool, const QString &)> _loginCallback;
};

#endif // AUTHCONTROLLER_H
