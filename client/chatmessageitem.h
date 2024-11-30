#ifndef CHATMESSAGEITEM_H
#define CHATMESSAGEITEM_H

#include <QObject>
#include <QtQml>

class ChatMessageItem : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString sender MEMBER _sender NOTIFY senderChanged FINAL)
    Q_PROPERTY(QString message MEMBER _message NOTIFY messageChanged FINAL)
    Q_PROPERTY(QString time MEMBER _time NOTIFY timeChanged FINAL)
public:
    ChatMessageItem(QObject *parent = nullptr);
    ChatMessageItem(QString sender, QString message, QString time, QObject *parent = nullptr);

private:
    QString _sender;
    QString _message;
    QString _time;



signals:
    void senderChanged();
    void messageChanged();
    void timeChanged();
};

#endif // CHATMESSAGEITEM_H
