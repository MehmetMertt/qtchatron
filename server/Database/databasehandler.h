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
    QSharedPointer<DatabaseResponse> AddUser(const QString& username, const QString& password, const QString& profile_info);
    bool verifyPassword(const QString& inputPassword, const QString& storedHash, const QString& storedSalt);
    bool validateInput(const QString& username, const QString& password, QSharedPointer<DatabaseResponse>& dbr);
    QSharedPointer<DatabaseResponse> LoginUser(const QString& username, const QString& password);
    QSharedPointer<DatabaseResponse> insertTokenByID(const QString& id);



signals:
};

#endif // DATABASEHANDLER_H
