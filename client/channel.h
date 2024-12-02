#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QtQml>

#include "chatmessageitem.h"

class Channel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QList<QObject *> memberList MEMBER _memberList NOTIFY memberListChanged FINAL)
    Q_PROPERTY(QString channelName READ channelName WRITE setChannelName NOTIFY channelNameChanged FINAL)
    Q_PROPERTY(int channelID READ channelID WRITE setChannelID NOTIFY channelIDChanged FINAL)
    Q_PROPERTY(QList<QObject *> messageList MEMBER _messageList NOTIFY messageListChanged FINAL)
    Q_PROPERTY(QString invite READ invite WRITE setInvite NOTIFY inviteChanged FINAL)

public:
    explicit Channel(QObject *parent = nullptr);
    explicit Channel(QString name, QObject *parent = nullptr);

    QList<QObject *> memberList() const;
    void setMemberList(const QList<QObject *> &newMemberList);



    QString channelName() const;
    void setChannelName(const QString &newChannelName);

    int channelID() const;
    void setChannelID(int newChannelID);


    QList<QObject *> messageList() const;
    void setMessageList(const QList<QObject *> &newMessageList);

    QString invite() const;
    void setInvite(const QString &newInvite);

    void addMessage(ChatMessageItem *newMessage);

private:
    QList<QObject *> _memberList;
    QList<QObject *> _messageList;
    QString _channelName;
    int _channelID;
    QString _invite;


signals:
    void memberListChanged();
    void channelNameChanged();
    void channelIDChanged();
    void messageListChanged();
    void inviteChanged();
};

#endif // CHANNEL_H
