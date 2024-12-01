#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(std::string command, std::string params, QObject *parent = nullptr);
    void setCommand(const std::string &newCommand);
    std::string command() const;
    std::string params() const;
    void setParams(const std::string &newParams);

private:
    std::string _command;
    std::string _params;
signals:
};

#endif // COMMAND_H
