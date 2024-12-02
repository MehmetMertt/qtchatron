#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QObject>
#include <QtQml>
#include "ctime"

#include "user.h"
#include "chatcontroller.h"

class ChatModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString inputMessage READ inputMessage WRITE setInputMessage NOTIFY inputMessageChanged)
    Q_PROPERTY(User *receivingUser READ receivingUser WRITE setReceivingUser NOTIFY receivingUserChanged FINAL)

public:
    explicit ChatModel(QObject *parent = nullptr);
    Q_INVOKABLE void sendMessage();
    Q_INVOKABLE void setReceivingUser(QString username);

    QString inputMessage() const;
    void setInputMessage(const QString &inputMessage);

    User *receivingUser() const;
    void setReceivingUser(User *newReceivingUser);

signals:
    void inputMessageChanged();
    void messageListChanged();
    void sendMessageSuccess();

    void receivingUserChanged();

private:
    QString _inputMessage;
    User *_receivingUser;

    ChatController *_chatController;


};

#endif // CHATMODEL_H
