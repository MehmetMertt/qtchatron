#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString username, QObject *parent = nullptr);


    QString username() const;

private:
    QString _username;
    QString _token;


signals:
};

#endif // USER_H
