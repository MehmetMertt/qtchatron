#include "threadmodel.h"

#include "sessionuser.h"

ThreadModel::ThreadModel(QObject *parent)
    : QObject{parent}
{}

void ThreadModel::sendMessage()
{
    if (_inputMessage.isEmpty()) {
        return;  // Safety check
    }
    //_channelController->processSendingMessage(_inputMessage, this->channel()->channelID());
    qDebug() << _inputMessage;
    // an den MessageController schicken
    // von MessageController an den Server schicken
    auto timee = std::time(nullptr);
    auto tm = *std::localtime(&timee);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M");
    QString timeString = QString::fromStdString(oss.str());
    _currentThread->addMessage(new ChatMessageItem(SessionUser::getInstance()->user()->username(), _inputMessage, timeString));
    emit sendMessageSuccess();
}

QString ThreadModel::inputMessage() const
{
    return _inputMessage;
}

void ThreadModel::setInputMessage(const QString &newInputMessage)
{
    if (_inputMessage == newInputMessage)
        return;
    _inputMessage = newInputMessage;
    emit inputMessageChanged();
}

Thread *ThreadModel::currentThread() const
{
    return _currentThread;
}

void ThreadModel::setCurrentThread(Thread *newCurrentThread)
{
    if (_currentThread == newCurrentThread)
        return;
    _currentThread = newCurrentThread;
    emit currentThreadChanged();
}
