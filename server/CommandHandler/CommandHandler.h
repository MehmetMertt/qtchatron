#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include <string>

class CommandHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommandHandler(QObject* parent = nullptr);

    /**
     * @brief Processes a command and returns a response.
     * @param command The command name.
     * @param params The parameters associated with the command.
     * @return The response string.
     */
    std::string routeCommand(const std::string& command, const std::string& params);

signals:
    /**
     * @brief Logs a message.
     * @param message The message to log.
     */
    void logMessage(const QString& message);
};

#endif // COMMANDHANDLER_H
