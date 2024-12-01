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
    Q_PROPERTY(QString channelName READ channelName WRITE setChannelName NOTIFY channelNameChanged FINAL)
    Q_PROPERTY(int channelID READ channelID WRITE setChannelID NOTIFY channelIDChanged FINAL)

public:
    explicit ChannelModel(QObject *parent = nullptr);
    explicit ChannelModel(QString name, QObject *parent = nullptr);

    QList<QObject *> memberList() const;
    void setMemberList(const QList<QObject *> &newMemberList);



    QString channelName() const;
    void setChannelName(const QString &newChannelName);

    int channelID() const;
    void setChannelID(int newChannelID);

private:
    QList<QObject *> _memberList;
    QString _channelName;
    int _channelID;


signals:
    void memberListChanged();
    void channelNameChanged();
    void channelIDChanged();
};

#endif // CHANNELMODEL_H
