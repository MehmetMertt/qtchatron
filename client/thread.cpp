#include "thread.h"

Thread::Thread(QObject *parent)
    : QObject{parent}
{}

Thread::Thread(QString threadname, int threadId, QObject *parent)
    : QObject{parent},
    _threadName(threadname),
    _threadID(threadId)
{}

QList<QObject *> Thread::messageList() const
{
    return _messageList;
}

void Thread::setMessageList(const QList<QObject *> &newMessageList)
{
    if (_messageList == newMessageList)
        return;
    _messageList = newMessageList;
    emit messageListChanged();
}

void Thread::addMessage(ChatMessageItem *newMessage)
{
    _messageList.append(newMessage);
    emit messageListChanged();
}

QString Thread::threadName() const
{
    return _threadName;
}

void Thread::setThreadName(const QString &newThreadName)
{
    if (_threadName == newThreadName)
        return;
    _threadName = newThreadName;
    emit threadNameChanged();
}

int Thread::threadID() const
{
    return _threadID;
}

void Thread::setThreadID(int newThreadID)
{
    if (_threadID == newThreadID)
        return;
    _threadID = newThreadID;
    emit threadIDChanged();
}
