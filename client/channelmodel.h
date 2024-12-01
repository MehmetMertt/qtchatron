#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QObject>
#include <QtQml>

class ChannelModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<QObject *> memberList MEMBER _memberList NOTIFY memberListChanged FINAL)

public:
    explicit ChannelModel(QObject *parent = nullptr);

    QList<QObject *> memberList() const;
    void setMemberList(const QList<QObject *> &newMemberList);

private:
    QList<QObject *> _memberList;


signals:
    void memberListChanged();
};

#endif // CHANNELMODEL_H
