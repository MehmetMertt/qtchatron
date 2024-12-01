#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtQml>

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)

public:
    explicit User(QObject *parent = nullptr);
    explicit User(QString username, QObject *parent = nullptr);

    QString username() const;
    void setUsername(const QString &newUsername);

    Q_INVOKABLE QString getInitials();

private:
    QString _username;

signals:
    void usernameChanged();
};

#endif // USER_H
