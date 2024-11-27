#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QJsonObject>
#include <QObject>

class CommandHandler : public QObject
{
    Q_OBJECT

public:
    CommandHandler(QObject* parent = nullptr);
    /**
     * @brief Routes the incoming JSON command to the appropriate handler.
     * @param jsonObj The JSON object containing the command.
     * @return A JSON object containing the response.
     */
    QJsonObject routeCommand(const QJsonObject& jsonObj);

signals:
   /**
     * @brief Emitted when a JSON response is generated.
     * @param response The JSON object containing the response.
     */
    void jsonResponse(const QJsonObject& response);
    
        /**
     * @brief Emitted for logging messages.
     * @param message The log message.
     */
    void logMessage(const QString& message);
};

#endif // COMMANDHANDLER_H
