#include "chatmessageitem.h"

ChatMessageItem::ChatMessageItem(QString sender, QString message, QString time, QObject *parent)
    : QObject{parent},
    _sender(sender),
    _message(message),
    _time(time)
{}

ChatMessageItem::ChatMessageItem(QObject *parent)
    : QObject{parent}
{}
