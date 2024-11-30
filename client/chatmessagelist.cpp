#include "chatmessagelist.h"

ChatMessageList::ChatMessageList(QObject *parent)
    : QObject{parent}
{
    _chatMessageList.append(new ChatMessageItem("flo", "hallo", "00:01"));
    _chatMessageList.append(new ChatMessageItem("flo", "wie gehts", "00:01"));
    _chatMessageList.append(new ChatMessageItem("michi", "Das ist eine lange geschichte in einer sehr langen nachricht, weil ich muss das halt auch irgendwie testen wie das auschaut", "00:02"));
    _chatMessageList.append(new ChatMessageItem("flo", "ich weiß bro", "00:03"));
}

void ChatMessageList::add(ChatMessageItem *newItem)
{
    _chatMessageList.append(newItem);
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
