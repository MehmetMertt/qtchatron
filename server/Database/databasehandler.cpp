#include "databasehandler.h"
#include <QRandomGenerator>

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
 * \return true if inserted or false on error
 */
bool databaseHandler::AddUser(const QString& username, const QString& password, const QString& profile_info) {
    QSqlDatabase db = getDatabase();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Users (username, password_hash, password_salt, profile_info) VALUES (:username, :password_hash, :password_salt, :profile_info)");
    query.bindValue(":username", username);
    QString salt = generateSalt();
    query.bindValue(":password_hash", getSHA256(password+salt));
    query.bindValue(":password_salt", salt);
    query.bindValue(":profile_info", profile_info);

    if (!query.exec()) {
        qDebug() << "Failed to insert User:" << query.lastError().text();
        return false;
    }

    return true;
}



/*
void addBook(QSqlQuery &q, const QString &title, int year, const QVariant &authorId,
             const QVariant &genreId, int rating)
{
    q.addBindValue(title);
    q.addBindValue(year);
    q.addBindValue(authorId);
    q.addBindValue(genreId);
    q.addBindValue(rating);
    q.exec();
}

QVariant addGenre(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QVariant addAuthor(QSqlQuery &q, const QString &name, QDate birthdate)
{
    q.addBindValue(name);
    q.addBindValue(birthdate);
    q.exec();
    return q.lastInsertId();
}

const auto BOOKS_SQL = QLatin1String(R"(
    create table books(id integer primary key, title varchar, author integer,
                       genre integer, year integer, rating integer)
    )");

const auto AUTHORS_SQL =  QLatin1String(R"(
    create table authors(id integer primary key, name varchar, birthdate date)
    )");

const auto GENRES_SQL = QLatin1String(R"(
    create table genres(id integer primary key, name varchar)
    )");

const auto INSERT_AUTHOR_SQL = QLatin1String(R"(
    insert into authors(name, birthdate) values(?, ?)
    )");

const auto INSERT_BOOK_SQL = QLatin1String(R"(
    insert into books(title, year, author, genre, rating)
                      values(?, ?, ?, ?, ?)
    )");

const auto INSERT_GENRE_SQL = QLatin1String(R"(
    insert into genres(name) values(?)
    )");
*/
QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << QCoreApplication::applicationDirPath();
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database.db");

    if (!db.open())
        return db.lastError();

/*
    StringList tables = db.tables();
    if (tables.contains("books", Qt::CaseInsensitive)
        && tables.contains("authors", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(BOOKS_SQL))
        return q.lastError();
    if (!q.exec(AUTHORS_SQL))
        return q.lastError();
    if (!q.exec(GENRES_SQL))
        return q.lastError();

    if (!q.prepare(INSERT_AUTHOR_SQL))
        return q.lastError();
    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));

    if (!q.prepare(INSERT_GENRE_SQL))
        return q.lastError();
    QVariant sfiction = addGenre(q, QLatin1String("Science Fiction"));
    QVariant fiction = addGenre(q, QLatin1String("Fiction"));
    QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

    if (!q.prepare(INSERT_BOOK_SQL))
        return q.lastError();
    addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation and Empire"), 1952, asimovId, sfiction, 4);
    addBook(q, QLatin1String("Second Foundation"), 1953, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation's Edge"), 1982, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation and Earth"), 1986, asimovId, sfiction, 4);
    addBook(q, QLatin1String("Prelude to Foundation"), 1988, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Forward the Foundation"), 1993, asimovId, sfiction, 3);
    addBook(q, QLatin1String("The Power and the Glory"), 1940, greeneId, fiction, 4);
    addBook(q, QLatin1String("The Third Man"), 1950, greeneId, fiction, 5);
    addBook(q, QLatin1String("Our Man in Havana"), 1958, greeneId, fiction, 4);
    addBook(q, QLatin1String("Guards! Guards!"), 1989, pratchettId, fantasy, 3);
    addBook(q, QLatin1String("Night Watch"), 2002, pratchettId, fantasy, 3);
    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy, 3);
*/
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
