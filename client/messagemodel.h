#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include <QtQml>
#include "chatmessagelist.h"
#include "chatmessageitem.h"
#include "ctime"

class MessageModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString inputMessage READ inputMessage WRITE setInputMessage NOTIFY inputMessageChanged)
    Q_PROPERTY(QList<QObject *> messageList MEMBER _messageList NOTIFY messageListChanged FINAL)

public:
    explicit MessageModel(QObject *parent = nullptr);
    Q_INVOKABLE void sendMessage();

    QString inputMessage() const;
    void setInputMessage(const QString &inputMessage);

signals:
    void inputMessageChanged();
    void messageListChanged();
    void sendMessageSuccess();

private:
    QString _inputMessage;
    QList<QObject *> _messageList;
};

#endif // MESSAGEMODEL_H
