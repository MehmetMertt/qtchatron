#include "server.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    setSslLocalCertificate("server.crt");
    setSslPrivateKey("server.key");
    setSslProtocol(QSsl::TlsV1_3OrLater);
}

void Server::start() {
    QHostAddress address = QHostAddress::Any;
    quint16 port = 45000;

    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (this->listen(address, port))
        qDebug().nospace() << "Now listening on " << qPrintable(address.toString()) << ":" << port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;
}

void Server::onNewConnection() {
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    QSslSocket *sslSocket = qobject_cast<QSslSocket*>(this->nextPendingConnection());

    if (!sslSocket) {
        qDebug() << "Error: Failed to cast QTcpSocket to QSslSocket";
        return;
    }

    ServerWorker *worker = new ServerWorker(sslSocket, this);

    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&Server::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    m_clients.append(worker);
    // we log the event
    emit logMessage(QStringLiteral("New client Connected"));
    qDebug() << "New client connected";
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket(this);
    sslSocket->setSocketDescriptor(socketDescriptor);
    sslSocket->setLocalCertificate(m_sslLocalCertificate);
    sslSocket->setPrivateKey(m_sslPrivateKey);
    sslSocket->setProtocol(m_sslProtocol);
    sslSocket->startServerEncryption();

    this->addPendingConnection(sslSocket);
}

void Server::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}
void Server::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void Server::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void Server::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
}

void Server::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}

void Server::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void Server::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : std::as_const(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("success")] = false;
            message[QStringLiteral("reason")] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("success")] = true;
    sendJson(sender, successMessage);
    QJsonObject connectedMessage;
    connectedMessage[QStringLiteral("type")] = QStringLiteral("newuser");
    connectedMessage[QStringLiteral("username")] = newUserName;
    broadcast(connectedMessage, sender);
}

void Server::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue textVal = docObj.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;
    message[QStringLiteral("sender")] = sender->userName();
    broadcast(message, sender);
}

void Server::setSslLocalCertificate(const QSslCertificate &certificate)
{
    m_sslLocalCertificate = certificate;
}

bool Server::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile("../certs/"+path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    m_sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}


void Server::setSslPrivateKey(const QSslKey &key)
{
    m_sslPrivateKey = key;
}

bool Server::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile("../certs/"+fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    m_sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void Server::setSslProtocol(QSsl::SslProtocol protocol)
{
    m_sslProtocol = protocol;
}
