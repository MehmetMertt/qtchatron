#ifndef SESSIONUSER_H
#define SESSIONUSER_H

#include <QObject>
#include <QtQml>
#include <mutex>
#include <QMap>
#include <QVariantList>

#include "user.h"
#include "channel.h"


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
    Q_INVOKABLE void processChannelCreation(QString channelname, QString type, bool isPublic);
    Q_INVOKABLE void processChannelJoin(QString channelname, QString invite = nullptr);
    Q_INVOKABLE void processThreadCreation(QString threadname, int channelId);

    void handleChatCreationResponse(const bool success, const QString message, const int receiverUserId);

    void loadData();

    Q_INVOKABLE User* getUserFromDmListByUsername(QString username);
    User* getUserFromDmListById(int userId);
    Channel* getChannelFromListById(int channelId);
    User* getUserFromChannelsById(int userId);
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
    QString _channelCreationName;

    QQueue<std::tuple<bool, QString, int>> _chatHistoryQueue; // Queue for handling messages
    bool _isProcessingChatHistory = false; // Flag to prevent concurrent processing



    void handleNextChatHistory();

    void handleReceivedMessageFromOtherUser(const int senderId, const QString message);
    void handleReceivedMessageFromOtherUserInChannel(const int senderId, const QString message, const int channelId);
    void handleReceivedDmList(const bool success, const QString message);
    void loadChatHistoryForAllUsers();
    void handleReceivedChatHistory(const bool success, const QString& message, const int receiverId);
    void handleChannelCreationResponse(const bool success, const QString& message, const QString& invite);
    void handleChannelJoinResponse(const bool success, const QString& message);
    void handleReceivedChannelsData(const bool success, const QString message);
    void handleThreadCreationRespond(const bool success, const QString message, const int threadid);

signals:
    void dmListChanged();
    void channelListChanged();
    void userChanged();
    void chatCreationSuccess(QString username, int userID);
    void chatCreationFailure(QString message);
    void channelPopupSuccess(QString channelName, int channelID);
    void channelPopupFailure(QString message);
    void threadPopupSuccess(QString threadName, int channelID, int threadID);
    void threadPopupFailure(QString message);
};


#endif // SESSIONUSER_H
