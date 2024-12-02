#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>

class ThreadController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadController(QObject *parent = nullptr);

    void processSendingMessage(QString message, int channelId);
    void processSendResponse(const bool success, const QString message);

signals:
};

#endif // THREADCONTROLLER_H
