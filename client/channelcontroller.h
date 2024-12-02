#ifndef CHANNELCONTROLLER_H
#define CHANNELCONTROLLER_H

#include <QObject>

class ChannelController : public QObject
{
    Q_OBJECT
public:
    explicit ChannelController(QObject *parent = nullptr);

    void processSendingMessage(QString message, int channelId);
    void processSendResponse(const bool success, const QString message);

signals:
};

#endif // CHANNELCONTROLLER_H
