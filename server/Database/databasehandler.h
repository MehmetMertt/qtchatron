#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include "Utils/databaseresponse.h"

class databaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit databaseHandler(QObject *parent = nullptr);
    QSqlDatabase getDatabase();


    /* Helper-Section */

    bool verifyPassword(const QString& inputPassword, const QString& storedHash, const QString& storedSalt);
    bool validateInput(const QString& username, const QString& password, QSharedPointer<DatabaseResponse>& dbr);

    /* User-Section */
    QSharedPointer<DatabaseResponse> AddUser(const QString& username, const QString& password, const QString& profile_info);
    QSharedPointer<DatabaseResponse> logoutUserByID(const QString& id);
    QSharedPointer<DatabaseResponse> LoginUser(const QString& username, const QString& password);
    QSharedPointer<DatabaseResponse> insertTokenByID(const QString& id);
    QSharedPointer<DatabaseResponse> getIDByToken(const QString& token);
    QSharedPointer<DatabaseResponse> checkIfUserExists(const QString& username);

    /* Direct-Message-Section */
    QSharedPointer<DatabaseResponse> getDirectMessagesBetweenUserByID(const QString& userid1,const QString& userid2);
    QSharedPointer<DatabaseResponse> sendMessageToUserID(const QString& senderID,const QString& receiverID,const QString& message);
    QSharedPointer<DatabaseResponse> getAllDirectMessagesByUserID(const QString& id);

    /* Channel-Section */
    bool isUserInChannel(const QString& userID, const QString& channelID);
    QSharedPointer<DatabaseResponse> getChannels();
    QSharedPointer<DatabaseResponse> createChannel(const QString& name,const QString& type,bool isPublic,const QString& user_id);
    QSharedPointer<DatabaseResponse> getChannelsFromUser(const QString& userID);
    QSharedPointer<DatabaseResponse> sendMessageToChannel(const QString& channelID,const QString& userID,const QString& message);

    /* Thread-Section */
    QSharedPointer<DatabaseResponse> createThread(const QString& channelID,const QString& title,const QString& userID);
    QSharedPointer<DatabaseResponse> getThreadsFromChannel(const QString& channelID);
    QSharedPointer<DatabaseResponse> sendMessageToThread(const QString& threadID,const QString& userID,const QString& message);
    QSharedPointer<DatabaseResponse>  (const QString& threadID);

signals:
};

#endif // DATABASEHANDLER_H
