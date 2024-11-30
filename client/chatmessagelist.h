#ifndef CHATMESSAGELIST_H
#define CHATMESSAGELIST_H

#include <QObject>
#include <QtQml>


class ChatMessageList : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<QObject *> chatMessageList MEMBER _chatMessageList NOTIFY chatMessageListChanged FINAL)
public:
    explicit ChatMessageList(QObject *parent = nullptr);

    //void setChatList(const QList<MessageItem *> &newChatList);

private:
    QList<QObject *> _chatMessageList;



signals:
    void chatMessageListChanged();
};

#endif // CHATMESSAGELIST_H
