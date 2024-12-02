#include "Server/Server.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

Server::Server(QHostAddress address, quint16 port, QObject *parent)
    : QTcpServer(parent)
{
    _address = address;
    _port = port;
    setSslLocalCertificate("server.crt");
    setSslPrivateKey("server.key");
    setSslProtocol(QSsl::TlsV1_3OrLater);
}

void Server::start() {

    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (this->listen(_address, _port))
        qDebug().nospace() << "Now listening on " << qPrintable(_address.toString()) << ":" << _port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(_address.toString()) << ":" << _port;
}

void Server::handleMessageReceived(ServerWorker* sender, const Protocol& p)
{
    Q_ASSERT(sender);
    qDebug() << "ok";
            // Handle the message based on its type
    switch (p.getMsgType()) {
    case MessageType::COMMAND_TRANSFER: {
        std::string command = p.getName();
        std::string params = p.getPayload();
        Command cmd(command,params);
        // Process the command using CommandHandler
        std::string responsePayload;
        try {

            responsePayload = commandHandler.routeCommand(cmd);
        } catch (const std::exception& ex) {
            responsePayload = std::string("Error: ") + ex.what();
        }


        if(command == "login_request") {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(responsePayload).toUtf8());

            // Überprüfen, ob das Dokument gültiges JSON enthält
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                bool success = jsonObject["success"].toBool();
                QString message = jsonObject["message"].toString();

                if(success) {
                    int userID = commandHandler.dbHandler()->getIDByToken(message)->message().toInt();
                    qDebug() << "set worker id: " << userID;
                    sender->setUserID(userID);
                }
            }
        }


        // Create a redsponse Protocol message
        Protocol responseProtocol(MessageType::COMMAND_TRANSFER, commandHandler.getCommandResponseName(cmd).toStdString(), responsePayload);

        // Send the response back to the client
        sender->sendData(responseProtocol);
        break;
    }

    case MessageType::MESSAGE_TRANSFER: {
        // Handle general messages
        QString command = QString::fromStdString(p.getName());
        QString params = QString::fromStdString(p.getPayload());

        if(command == "send_dm") {

            // Konvertiere den QString in ein QJsonDocument
            QJsonDocument jsonDoc = QJsonDocument::fromJson(params.toUtf8());

            // Überprüfen, ob das Dokument gültiges JSON enthält
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                QString senderToken = jsonObject["senderToken"].toString();
                int receiverId = jsonObject["receiverId"].toInt();
                QString message = jsonObject["message"].toString();
                int senderId = commandHandler.dbHandler()->getIDByToken(senderToken)->message().toInt();

                QJsonObject sendToReceiverObj;
                sendToReceiverObj["senderId"] = senderId;
                sendToReceiverObj["message"] = message;

                QJsonDocument sendToReceiverJsonDoc(sendToReceiverObj);

                std::string sendToReceiverPayload = QString(sendToReceiverJsonDoc.toJson(QJsonDocument::Compact)).toStdString();


                for (ServerWorker* worker : _clients) {
                    qDebug() << "worker: " << worker->userID();
                    if (worker && worker->userID() == receiverId) { // Annahme: getUserId() gibt die User-ID zurück
                        Protocol sendToReceiverProtocol(MessageType::MESSAGE_TRANSFER, "send_dm", sendToReceiverPayload);
                        worker->sendData(sendToReceiverProtocol); // sendData schickt die Nachricht
                        qDebug() << "send to receiver: " << worker->userID();
                        return; // Sobald der Worker gefunden wurde, beende die Suche
                    }
                }
                std::string responsePayload;
                auto dbResponse = commandHandler.dbHandler()->sendMessageToUserID(QString::number(senderId), QString::number(receiverId), message);

                QJsonObject responseObject;
                responseObject["success"] = dbResponse->success();
                responseObject["message"] = dbResponse->message();

                QJsonDocument responseJsonDoc(responseObject);

                try {
                    std::string responsePayload = QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
                } catch (const std::exception& ex) {
                    responsePayload = std::string("Error: ") + ex.what();
                }

                // Create a redsponse Protocol message
                Protocol responseProtocol(MessageType::MESSAGE_TRANSFER, "send_dm_response", responsePayload);

                // Send the response back to the client
                sender->sendData(responseProtocol);
            }
        } else if(command == "send_to_channel") {

            // Konvertiere den QString in ein QJsonDocument
            QJsonDocument jsonDoc = QJsonDocument::fromJson(params.toUtf8());

            // Überprüfen, ob das Dokument gültiges JSON enthält
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                QString senderToken = jsonObject["senderToken"].toString();
                int channelId = jsonObject["channelId"].toInt();
                QString message = jsonObject["message"].toString();
                int senderId = commandHandler.dbHandler()->getIDByToken(senderToken)->message().toInt();

                auto dbResponse = commandHandler.dbHandler()->getChannelMembersFromID(QString::number(channelId));

                QJsonDocument doc = QJsonDocument::fromJson(dbResponse->message().toUtf8());
                if (!doc.isArray()) {
                    qDebug() << "Error: Message is not a JSON array!";
                    return;
                }

                qDebug() << "send to: " << dbResponse->message();
                QJsonArray jsonArray = doc.array();

                // Nachricht erstellen
                QJsonObject sendToReceiverObj;
                sendToReceiverObj["senderId"] = senderId;
                sendToReceiverObj["message"] = message;
                sendToReceiverObj["channelId"] = channelId;

                QJsonDocument sendToReceiverJsonDoc(sendToReceiverObj);
                std::string sendToReceiverPayload = QString(sendToReceiverJsonDoc.toJson(QJsonDocument::Compact)).toStdString();


                for (const QJsonValue& value : jsonArray) {
                    if (!value.isObject()) {
                        continue; // Überspringe ungültige Einträge
                    }

                    QJsonObject obj = value.toObject();
                    QString userIdStr = obj["user_id"].toString();

                    if (userIdStr.isEmpty()) {
                        qDebug() << "Error: user_id is missing or invalid!";
                        continue;
                    }

                    int userId = userIdStr.toInt(); // Konvertiere zu int, falls erforderlich
                    if(userId == senderId) {
                        continue;
                    }
                    qDebug() << "try to send to: " << userId;
                    // ServerWorker suchen und Nachricht senden
                    for (ServerWorker* worker : _clients) {
                        if (worker && worker->userID() == userId) { // Annahme: getUserId() gibt die User-ID zurück
                            Protocol sendToReceiverProtocol(MessageType::MESSAGE_TRANSFER, "send_channel", sendToReceiverPayload);
                            worker->sendData(sendToReceiverProtocol);
                            qDebug() << "Message sent to user ID:" << userId;
                            break; // Breche die innere Schleife ab, wenn der Worker gefunden wurde
                        }
                    }
                }


                std::string responsePayload;
                commandHandler.dbHandler()->sendMessageToChannel(QString::number(channelId), QString::number(senderId), message);

                QJsonObject responseObject;
                responseObject["success"] = true; //dbResponse->success();
                responseObject["message"] = "message saved"; //dbResponse->message();

                QJsonDocument responseJsonDoc(responseObject);

                try {
                    std::string responsePayload = QString(responseJsonDoc.toJson(QJsonDocument::Compact)).toStdString();
                } catch (const std::exception& ex) {
                    responsePayload = std::string("Error: ") + ex.what();
                }

                // Create a redsponse Protocol message
                Protocol responseProtocol(MessageType::MESSAGE_TRANSFER, "send_channel_response", responsePayload);

                // Send the response back to the client
                sender->sendData(responseProtocol);
            }
        }

        //emit logMessage(senderName + ": " + message);
        break;
    }

    case MessageType::FILE_TRANSFER: {
        // Handle file transfers if implemented
        emit logMessage("File transfer received.");
        break;
    }

    default:
        emit logMessage("Unknown message type received.");
        break;
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket(this);

    sslSocket->setSocketDescriptor(socketDescriptor);
    sslSocket->setLocalCertificate(_sslLocalCertificate);
    sslSocket->setPrivateKey(_sslPrivateKey);
    sslSocket->setProtocol(_sslProtocol);
    sslSocket->startServerEncryption();

    this->addPendingConnection(sslSocket);
}

void Server::onNewConnection() {

    QSslSocket *sslSocket = qobject_cast<QSslSocket*>(this->nextPendingConnection());

    if (!sslSocket) {
        qDebug() << "Error: Failed to cast QTcpSocket to QSslSocket";
        return;
    }

    ServerWorker *worker = new ServerWorker(sslSocket, this);

    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&Server::userError, this, worker));
    connect(worker, &ServerWorker::messageReceived,this,&Server::handleMessageReceived);
    connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);

    _clients.append(worker);

    //emit logMessage(QStringLiteral("New client Connected"));
    qDebug() << "New client connected";
}


void Server::userDisconnected(ServerWorker *sender)
{
    _clients.removeAll(sender);

    QJsonObject disconnectedMessage;
    disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
    emit logMessage(QStringLiteral(" disconnected"));
    qDebug() << QStringLiteral(" disconnected");

    sender->deleteLater();
}

void Server::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QStringLiteral("Error from "));
}

void Server::stopServer()
{
    for (ServerWorker *worker : _clients) {
        worker->disconnectFromClient();
    }
    close();
}

bool Server::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(QStringLiteral("../certs/") + path);

    if (!certificateFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open certificate file:" << path;
        return false;
    }

    _sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return !_sslLocalCertificate.isNull();
}

bool Server::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile("../certs/"+fileName);

    if (!keyFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open private key file:" << fileName;
        return false;
    }

    _sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void Server::setSslProtocol(QSsl::SslProtocol Protocol)
{
    _sslProtocol = Protocol;
}
