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

    void handleAuthResponseCallback(const bool success, const QString message);

    void signup(const QString &username, const QString &password,
                const std::function<void(bool, const QString &)> &callback);

    void logout(const std::function<void(bool, const QString &)> &callback);

    std::string dataToJsonString(const QString &username, const QString &password);

private:
    std::function<void(bool, const QString &)> _authCallback;
};

#endif // AUTHCONTROLLER_H
