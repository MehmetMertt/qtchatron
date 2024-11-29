#include "databaseresponse.h"

DatabaseResponse::DatabaseResponse(bool success, QString message,QObject *parent)
    : QObject{parent},
    _success(success),
    _message(message)
{

}

bool DatabaseResponse::success() const
{
    return _success;
}

void DatabaseResponse::setSuccess(bool newSuccess)
{
    _success = newSuccess;
}

QString DatabaseResponse::message() const
{
    return _message;
}

void DatabaseResponse::setMessage(const QString &newMessage)
{
    _message = newMessage;
}
