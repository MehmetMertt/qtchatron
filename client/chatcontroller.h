#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>

class ChatController : public QObject
{
    Q_OBJECT
public:
    explicit ChatController(QObject *parent = nullptr);

    void processSendingMessage(QString message, int receiverId);
    void processSendResponse(const bool success, const QString message);

signals:
};

#endif // CHATCONTROLLER_H
