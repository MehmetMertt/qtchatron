#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QObject>
#include <QtQml>

#include <channel.h>
#include <channelcontroller.h>

class ChannelModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(Channel *channel READ channel WRITE setChannel NOTIFY channelChanged FINAL)
    Q_PROPERTY(QString inputMessage READ inputMessage WRITE setInputMessage NOTIFY inputMessageChanged FINAL)

public:
    explicit ChannelModel(QObject *parent = nullptr);

    Q_INVOKABLE void sendMessage();
    Q_INVOKABLE void setChannel(Channel *newChannel);

    Channel *channel() const;

    QString inputMessage() const;
    void setInputMessage(const QString &newInputMessage);

private:
    QString _inputMessage;
    Channel *_channel;

    ChannelController *_channelController;


signals:
    void channelChanged();
    void inputMessageChanged();
    void sendMessageSuccess();
};

#endif // CHANNELMODEL_H
