#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtQml>

#include "chatmessageitem.h"


class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QList<QObject *> messageList MEMBER _messageList NOTIFY messageListChanged FINAL)

public:
    explicit User(QObject *parent = nullptr);
    explicit User(QString username, QObject *parent = nullptr);
    explicit User(QString username, int id, QObject *parent = nullptr);

    QString username() const;
    void setUsername(const QString &newUsername);

    Q_INVOKABLE QString getInitials();

    int userId() const;
    void setUserId(int newUserId);

    void addMessage(ChatMessageItem *newMessage);
    void setMessageList(QList<QObject *> newMessageList);

private:
    QString _username;
    int _userId;
    QList<QObject *> _messageList;

signals:
    void usernameChanged();
    void messageListChanged();
    void userIdChanged();
};

#endif // USER_H
