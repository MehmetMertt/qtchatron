#ifndef SESSIONUSER_H
#define SESSIONUSER_H

#include <QObject>
#include <QtQml>
#include <mutex>
#include <QMap>
#include <QVariantList>

#include "user.h"


class SessionUser : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<QObject *> dmList MEMBER _dmList NOTIFY dmListChanged FINAL)
    Q_PROPERTY(QList<QObject *> channelList READ channelList WRITE setChannelList NOTIFY channelListChanged FINAL)
    Q_PROPERTY(User *user MEMBER _user NOTIFY userChanged FINAL)

public:
    static SessionUser* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new SessionUser();
        }
        return instance;
    }

    Q_INVOKABLE void processChatCreation(QString username);

    void handleChatCreationResponse(const bool success, const QString message, const int receiverUserId);

    Q_INVOKABLE User* getUserFromDmListByUsername(QString username);
    QList<QObject *> dmList() const;
    void setDmList(const QList<QObject *> &newDmList);

    QList<QObject *> channelList() const;
    void setChannelList(const QList<QObject *> &newChannelList);

    User *user() const;
    void setUser(User* newUser);

    QString token() const;
    void setToken(const QString &newToken);

private:
    SessionUser(QObject *parent = nullptr);
    SessionUser(const SessionUser&) = delete;
    SessionUser& operator=(const SessionUser&) = delete;
    static SessionUser* instance;
    static std::mutex mtx;

    User *_user;
    QList<QObject*> _dmList;
    QList<QObject *> _channelList;
    QString _token;

    QString _chatCreationUsername;

signals:
    void dmListChanged();
    void channelListChanged();
    void userChanged();
    void chatCreationSuccess(QString username, int userID);
    void chatCreationFailure(QString message);
};


#endif // SESSIONUSER_H
