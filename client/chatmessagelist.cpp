#include "chatmessagelist.h"

#include "chatmessageitem.h"

ChatMessageList::ChatMessageList(QObject *parent)
    : QObject{parent}
{
    _chatMessageList.append(new ChatMessageItem("flo", "hallo", "00:01"));
    _chatMessageList.append(new ChatMessageItem("flo", "wie gehts", "00:01"));
    _chatMessageList.append(new ChatMessageItem("michi", "scheiße", "00:02"));
    _chatMessageList.append(new ChatMessageItem("flo", "ich weiß bro", "00:03"));
}

/*
void ChatList::setChatList(const QList<QObject *> &newChatList)
{
    if (_chatList == newChatList)
        return;
    _chatList = newChatList;
    emit chatListChanged();
}
*/
