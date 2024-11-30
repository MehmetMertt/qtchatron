#ifndef SESSIONUSER_H
#define SESSIONUSER_H

#include <QObject>
#include <QtQml>

#include "user.h"

class SessionUser : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<QObject *> dmList MEMBER _dmList NOTIFY dmListChanged FINAL)
    Q_PROPERTY(User *user MEMBER _user FINAL)
public:
    explicit SessionUser(QObject *parent = nullptr);
    //explicit SessionUser(QString username, QObject *parent = nullptr);

    QList<QObject *> dmList() const;
    void setDmList(const QList<QObject *> &newDmList);

    User *user() const;

private:
    User *_user;
    QList<QObject *> _dmList;

signals:
    void dmListChanged();
};

#endif // SESSIONUSER_H
