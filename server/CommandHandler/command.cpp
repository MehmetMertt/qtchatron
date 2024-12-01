#include "command.h"

Command::Command(std::string command, std::string params, QObject *parent)
    : QObject{parent}
{
    _command = command;
    _params = params;
}

void Command::setCommand(const std::string &newCommand)
{
    _command = newCommand;
}

std::string Command::command() const
{
    return _command;
}

std::string Command::params() const
{
    return _params;
}

void Command::setParams(const std::string &newParams)
{
    _params = newParams;
}




