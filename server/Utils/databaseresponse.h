#ifndef DATABASERESPONSE_H
#define DATABASERESPONSE_H

#include <QObject>

class DatabaseResponse : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseResponse(bool success, QString message,QObject *parent = nullptr);

    bool success() const;
    void setSuccess(bool newSuccess);

    QString message() const;
    void setMessage(const QString &newMessage);

    QString extra() const;
    void setExtra(const QString &newExtra);

private:
    bool _success;
    QString _message;
    QString _extra;
signals:
};

#endif // DATABASERESPONSE_H
