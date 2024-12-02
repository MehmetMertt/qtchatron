#ifndef THREADMODEL_H
#define THREADMODEL_H

#include <QObject>
#include <QtQml>

#include "thread.h"

class ThreadModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString inputMessage READ inputMessage WRITE setInputMessage NOTIFY inputMessageChanged FINAL)
    Q_PROPERTY(Thread *currentThread READ currentThread WRITE setCurrentThread NOTIFY currentThreadChanged FINAL)

public:
    explicit ThreadModel(QObject *parent = nullptr);

    Q_INVOKABLE void sendMessage();

    QString inputMessage() const;
    void setInputMessage(const QString &newInputMessage);

    Thread *currentThread() const;
    Q_INVOKABLE void setCurrentThread(Thread *newCurrentThread);

private:
    QString _inputMessage;
    Thread *_currentThread;

    //ThreadController *_threadController;


signals:
    void inputMessageChanged();
    void currentThreadChanged();
    void sendMessageSuccess();
};

#endif // THREADMODEL_H
