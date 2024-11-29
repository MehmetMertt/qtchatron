#include "databasehandler.h"
#include <QRandomGenerator>
#include <QSqlError>
#include <QSqlError>
#include <QRegularExpression>
#include <QCryptographicHash>





QString generateSalt(int length = 15) {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int charactersLength = possibleCharacters.length();

    QString randomString;
    randomString.reserve(length); // Reserve memory for better performance

    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(charactersLength);
        randomString.append(possibleCharacters.at(index));
    }

    return randomString;
}




QSqlDatabase databaseHandler::getDatabase() {
    return QSqlDatabase::database();
}




/**
 * \brief Generates SHA256 Hash form String
 *
 *
 * \param input Text to be hashed
 * \return hashed input as string
 */
QString getSHA256(const QString &input)
{
    QByteArray bytes = input.toStdString().c_str();

    QString hash = QString( QCryptographicHash::hash( (bytes ),QCryptographicHash::Sha256).toHex());
    return hash;
}

/**
 * \brief Adds a User to the database
 *
 * This function takes the username, password and profile info. It generates a hash of the password + random salt and inserts it into the database
 *
 * \param username The Username of the user
 * \param password The unhashed password of the user
 * \param profile_info Small User Description
 * \return returns QSharedPointer<DatabaseResponse> Object
 */
QSharedPointer<DatabaseResponse> databaseHandler::AddUser(const QString& username, const QString& password, const QString& profile_info) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));

    if (username.isEmpty() || password.isEmpty()) {
        dbr->setMessage("Username and password cannot be empty.");
        return dbr;
    }

    if (password.length() < 8) {
        dbr->setMessage("Password must be at least 8 characters long.");
        return dbr;
    }

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]+$");
    if (!usernameRegex.match(username).hasMatch()) {
        dbr->setMessage("The username contains invalid characters. Only letters, numbers, and underscores are allowed.");
        return dbr;
    }

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        dbr->setMessage("Internal Database Error. Database is not open. Contact a developer.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Users (username, password_hash, password_salt, profile_info) VALUES (:username, :password_hash, :password_salt, :profile_info)");
    query.bindValue(":username", username);
    QString salt = generateSalt();
    query.bindValue(":password_hash", getSHA256(password + salt));
    query.bindValue(":password_salt", salt);
    query.bindValue(":profile_info", profile_info);

    if (!query.exec()) {
        QSqlError error = query.lastError();

        if (error.databaseText().contains("UNIQUE constraint failed")) {
            if (error.databaseText().contains("UNIQUE constraint failed: Users.username")) {
                dbr->setMessage("The username is already taken. Please choose another.");
                return dbr;
            }
        } else {
            dbr->setMessage("An unexpected database error occurred: " + error.text());
            return dbr;
        }
    }

    dbr->setSuccess(true);
    dbr->setMessage("Account successfully created.");
    return dbr;
}


/**
 * \brief Logins a User to the database
 *
 * This function takes the username, password and returns a QShardPointer<DatabaseResponse> Object
 *
 * \param username The Username of the user
 * \param password The unhashed password of the user
 * \return returns QSharedPointer<DatabaseResponse> Object
 */
QSharedPointer<DatabaseResponse> databaseHandler::LoginUser(const QString& username, const QString& password) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));

    if (username.isEmpty() || password.isEmpty()) {
        dbr->setMessage("Username and password cannot be empty.");
        return dbr;
    }

    if (password.length() < 8) {
        dbr->setMessage("Password must be at least 8 characters long.");
        return dbr;
    }

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]+$");
    if (!usernameRegex.match(username).hasMatch()) {
        dbr->setMessage("The username contains invalid characters. Only letters, numbers, and underscores are allowed.");
        return dbr;
    }

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        dbr->setMessage("Internal Database Error. Database is not open. Contact a developer.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare("SELECT password_hash, password_salt FROM USERS WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }

    if (!query.next()) {
        // Username not found
        dbr->setMessage("Invalid Username or Password");
        return dbr;
    }

    // Retrieve hash and salt
    QString storedHash = query.value("password_hash").toString();
    QString storedSalt = query.value("password_salt").toString();

    // Hash the input password with the stored salt
    QString inputHash = getSHA256(password + storedSalt);

    if (inputHash != storedHash) {
        dbr->setMessage("Invalid Username or Password");
        return dbr;
    }

    // Login successful
    dbr->setSuccess(true);
    dbr->setMessage("Login successful.");
    return dbr;
}


QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << QCoreApplication::applicationDirPath();
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database.db");

    if (!db.open())
        return db.lastError();

    return QSqlError();
}


databaseHandler::databaseHandler(QObject *parent)
    : QObject{parent}
{
    // Initialize the database in the constructor
    QSqlError error = initDb();
    if (error.type() != QSqlError::NoError) {
        qCritical() << "Database initialization failed:" << error.text();
    } else {
        qDebug() << "Database initialized successfully.";
    }
}
