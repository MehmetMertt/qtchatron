#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QObject>
#include <QtQml>

#include "user.h"


class SessionModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(User *currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged FINAL)
    Q_PROPERTY(QString currentUsername READ currentUsername CONSTANT)
public:
    static SessionModel* instance() {
        if(!_instance) {
            _instance = new SessionModel();
        }
        return _instance;
    }

    SessionModel(SessionModel const&)    = delete;
    void operator=(SessionModel const&)  = delete;

    QString currentUsername() const;
    User *currentUser() const;

    void setCurrentUser(User *newCurrentUser);

private:
    SessionModel() {}
    static SessionModel* _instance;
    User *_currentUser;
    QString _currentUsername;

signals:
    void currentUserChanged();
};

//SessionModel* SessionModel::_instance = nullptr;

#endif // SESSIONMODEL_H
