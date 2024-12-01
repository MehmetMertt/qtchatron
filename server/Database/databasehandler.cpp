#include "databasehandler.h"
#include <QRandomGenerator>
#include <QSqlError>
#include <QSqlError>
#include <QRegularExpression>
#include <QCryptographicHash>





QString generateRandomString(int length = 15) {
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int charactersLength = possibleCharacters.length();

    QString randomString;
    randomString.reserve(length); // better performance (stackoverflow)

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
 * \brief Checks if User exist in database
 *
 * Takes username as input and returns DatabaseResponse with either true or false
 *
 * \param username username of the user
 * \return returns QSharedPointer<DatabaseResponse> Object with either true or false
 */
QSharedPointer<DatabaseResponse> databaseHandler::checkIfUserExists(const QString& username) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));


    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        dbr->setMessage("Internal Database Error. Database is not open. Contact a developer.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id from Users where Users.username = :username");
    query.bindValue(":username", username);


    if (!query.exec()) {
        QSqlError error = query.lastError();
        dbr->setMessage("An unexpected database error occurred: " + error.text());
        return dbr;
        }

    if(query.next()) {
            dbr->setSuccess(true);
            QString id = query.value("id").toString();
            dbr->setMessage("id:"+id);
            return dbr;
    }

    dbr->setMessage("User not found");
    return dbr;
}

/*

 *
 * */


/**
 * \brief Gets all DIrect Messages between two UserID's
 *
 * This function takes two userids and returns a QShardPointer<DatabaseResponse> Object
 *
 * \param id ID of the first user
 * \param id ID of the second user
 * \return returns QSharedPointer<DatabaseResponse> Object with messages or null
 */
QSharedPointer<DatabaseResponse> databaseHandler::sendMessageToUserID(const QString& senderID,const QString& receiverID,const QString& message) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));

    if (!db.isOpen()) {
        dbr->setMessage("Database is not open.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO DirectMessages
        (sender_id, receiver_id, content)
        VALUES(:sender_id, :receiver_id, :content);
    )");
    query.bindValue(":sender_id", senderID);
    query.bindValue(":receiver_id", receiverID);
    query.bindValue(":content", message);


    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }


    if (query.numRowsAffected() > 0) {
        dbr->setMessage("Message successfully inserted.");
        dbr->setSuccess(true);
    } else {
        dbr->setMessage("Insertion succeeded, but no rows were affected.");
    }
    return dbr;
}



/**
 * \brief Gets all DIrect Messages between two UserID's
 *
 * This function takes two userids and returns a QShardPointer<DatabaseResponse> Object
 *
 * \param id ID of the first user
 * \param id ID of the second user
 * \return returns QSharedPointer<DatabaseResponse> Object with messages or null
 */
QSharedPointer<DatabaseResponse> databaseHandler::getDirectMessagesBetweenUserByID(const QString& userid1,const QString& userid2) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));

    if (!db.isOpen()) {
        dbr->setMessage("Database is not open.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT sender_id,receiver_id,content,"timestamp",is_read
        FROM DirectMessages dm
        WHERE (sender_id = :userid1 AND receiver_id = :userid2)
           OR (sender_id = :userid2 AND receiver_id = :userid1)
        ORDER BY timestamp ASC;
    )");
    query.bindValue(":userid1", userid1);
    query.bindValue(":userid2", userid2);

    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }

    QJsonArray jsonArray; // Array to hold each message as a JSON object

    while (query.next()) {
        QJsonObject messageObject;
     //   messageObject["chat_id"] = query.value("id").toString();
        messageObject["sender_id"] = query.value("sender_id").toString();
        messageObject["receiver_id"] = query.value("receiver_id").toString();
        messageObject["content"] = query.value("content").toString();
        messageObject["timestamp"] = query.value("timestamp").toString();
        messageObject["isRead"] = query.value("is_read").toString();

        jsonArray.append(messageObject);
    }

    if (jsonArray.isEmpty()) {
        dbr->setMessage("null");
        dbr->setSuccess(false);
        return dbr;
    }

    QJsonDocument jsonDoc(jsonArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    dbr->setMessage(jsonString);
    dbr->setSuccess(true);
    return dbr;
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

    if (!validateInput(username, password, dbr)) {
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
    QString salt = generateRandomString();
    query.bindValue(":password_hash", getSHA256(password + salt));
    query.bindValue(":password_salt", salt);
    query.bindValue(":profile_info", profile_info);

    if (!query.exec()) {
        QSqlError error = query.lastError();

        if (error.databaseText().contains("UNIQUE constraint failed")) {
                dbr->setMessage("The username is already taken. Please choose another.");
                return dbr;

        } else {
            dbr->setMessage("An unexpected database error occurred: " + error.text());
            return dbr;
        }
    }

    dbr->setSuccess(true);
    dbr->setMessage("Account successfully created.");
    return dbr;
}



bool databaseHandler::verifyPassword(const QString& inputPassword, const QString& storedHash, const QString& storedSalt) {
    QString inputHash = getSHA256(inputPassword + storedSalt);
    return inputHash == storedHash;
}

bool databaseHandler::validateInput(const QString& username, const QString& password, QSharedPointer<DatabaseResponse>& dbr) {
    if (username.isEmpty() || password.isEmpty()) {
        dbr->setMessage("Username and password cannot be empty.");
        return false;
    }

    if (password.length() < 8) {
        dbr->setMessage("Password must be at least 8 characters long.");
        return false;
    }

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]+$");
    if (!usernameRegex.match(username).hasMatch()) {
        dbr->setMessage("The username contains invalid characters. Only letters, numbers, and underscores are allowed.");
        return false;
    }

    return true;
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


    if (!validateInput(username, password, dbr)) {
        return dbr;
    }

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        dbr->setMessage("Internal Database Error. Database is not open. Contact a developer.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id,password_hash, password_salt FROM USERS WHERE username = :username");
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
    QString id = query.value("id").toString();
    QString storedSalt = query.value("password_salt").toString();

    // Hash the input password with the stored salt
    QString inputHash = getSHA256(password + storedSalt);

    if (!verifyPassword(password, storedHash, storedSalt)) {
        dbr->setMessage("Invalid Username or Password");
        return dbr;
    }



    // Login successful

    //TODO: get channels & messages from user

    return insertTokenByID(id);
}

QSharedPointer<DatabaseResponse> databaseHandler::insertTokenByID(const QString& id) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));
    QSqlQuery query(db);
    QString token = generateRandomString(20);
    QString expires_at = QDateTime::currentDateTime().addDays(21).toString(Qt::ISODate); //make token expire in 21 days
    query.prepare("REPLACE INTO AuthTokens (user_id, token, expires_at) VALUES (:user_id, :token, :expires_at)"); //replace is really interessting REPLACE does INSERT OR REPLACE (if unique constraint)
    query.bindValue(":user_id",id);
    query.bindValue(":token",token);
    query.bindValue(":expires_at",expires_at);
    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }
    dbr->setMessage(token);
    dbr->setSuccess(true);
    return dbr;
}



QSharedPointer<DatabaseResponse> databaseHandler::getIDByToken(const QString& token) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));
    QSqlQuery query(db);
    query.prepare("SELECT u.id FROM Users u JOIN AuthTokens at ON u.id = at.user_id WHERE at.token  = :token"); //replace is really interessting REPLACE does INSERT OR REPLACE (if unique constraint)
    query.bindValue(":token",token);
    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }
    if (!query.next()) {
        // ID not found
        dbr->setMessage("null");
        return dbr;
    }

    QString id = query.value("id").toString();

    dbr->setMessage(id);
    dbr->setSuccess(true);
    return dbr;
}

/**
 * \brief Logins a User to the database
 *
 * This function takes the username, password and returns a QShardPointer<DatabaseResponse> Object
 *
 * \param id ID of the sender
 * \return returns QSharedPointer<DatabaseResponse> Object with message NULL if no messages or json of ID & Username
 */
QSharedPointer<DatabaseResponse> databaseHandler::getAllDirectMessagesByUserID(const QString& id) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));

    if (!db.isOpen()) {
        dbr->setMessage("Database is not open.");
        return dbr;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT DISTINCT dm.id, u.username, dm.receiver_id
        FROM DirectMessages dm
        JOIN Users u ON dm.receiver_id = u.id
        WHERE dm.sender_id = :user_id
    )");
    query.bindValue(":user_id", id);

    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }

    QJsonArray jsonArray; // Array to hold each message as a JSON object

    while (query.next()) {
        QJsonObject messageObject;
     //   messageObject["chat_id"] = query.value("id").toString();
        messageObject["receiver"] = query.value("receiver_id").toString();
        messageObject["username"] = query.value("username").toString();
        jsonArray.append(messageObject);
    }

    if (jsonArray.isEmpty()) {
        dbr->setMessage("null");
        dbr->setSuccess(true);
        return dbr;
    }

    QJsonDocument jsonDoc(jsonArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    dbr->setMessage(jsonString);
    dbr->setSuccess(true);
    return dbr;
}



QSharedPointer<DatabaseResponse> databaseHandler::logoutUserByID(const QString& id) {
    QSqlDatabase db = getDatabase();
    QSharedPointer<DatabaseResponse> dbr(new DatabaseResponse(false, ""));
    QSqlQuery query(db);
    query.prepare("DELETE FROM AuthTokens WHERE user_id = :user_id");
    query.bindValue(":user_id",id);
    if (!query.exec()) {
        dbr->setMessage("An unexpected database error occurred: " + query.lastError().text());
        return dbr;
    }
    int affectedRows = query.numRowsAffected();
    if(affectedRows <= 0){
        dbr->setMessage("No token found to delete");
        return dbr;
    }
    dbr->setMessage("token deleted");
    dbr->setSuccess(true);
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
