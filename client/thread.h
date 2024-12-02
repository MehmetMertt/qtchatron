#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QtQml>

#include "chatmessageitem.h"

class Thread : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QList<QObject *> messageList MEMBER _messageList NOTIFY messageListChanged FINAL)
    Q_PROPERTY(QString threadName READ threadName WRITE setThreadName NOTIFY threadNameChanged FINAL)
    Q_PROPERTY(int threadID READ threadID WRITE setThreadID NOTIFY threadIDChanged FINAL)
public:
    Thread(QObject *parent = nullptr);
    Thread(QString threadname, int threadId, QObject *parent = nullptr);

    QList<QObject *> messageList() const;
    void setMessageList(const QList<QObject *> &newMessageList);
    void addMessage(ChatMessageItem *newMessage);

    QString threadName() const;
    void setThreadName(const QString &newThreadName);

    int threadID() const;
    void setThreadID(int newThreadID);

private:
    QList<QObject *> _messageList;
    QString _threadName;
    int _threadID;

signals:
    void messageListChanged();
    void threadNameChanged();
    void threadIDChanged();
};

#endif // THREAD_H
