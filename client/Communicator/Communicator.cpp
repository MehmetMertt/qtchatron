#include "Communicator.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSslConfiguration>
#include <QFile>

Communicator::Communicator(QObject *parent)
    : QObject(parent)
    , _clientSocket(new QSslSocket(this))
{
    setSslCaCertificate("server.crt");
    setSslProtocol(QSsl::TlsV1_3OrLater);

    connect(_clientSocket, &QSslSocket::encrypted, this, &Communicator::onEncrypted);
    connect(_clientSocket, &QTcpSocket::connected, this, &Communicator::onConnected);
    connect(_clientSocket, &QTcpSocket::disconnected, this, &Communicator::disconnected);
    connect(_clientSocket, &QTcpSocket::readyRead, this, &Communicator::onReadyRead);
    connect(_clientSocket, &QAbstractSocket::errorOccurred, this, &Communicator::error);
    connect(_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{});
}

void Communicator::connectToServer(const QString &address, quint16 port)
{
    // Configure SSL settings
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.addCaCertificate(_sslCaCertificate);
    _clientSocket->setSslConfiguration(sslConfig);
    _clientSocket->setProtocol(_sslProtocol);

    qDebug() << "connecting ...";
    _clientSocket->connectToHostEncrypted(address, port);
}

void Communicator::onConnected() {
    if (!_clientSocket->waitForEncrypted(5000)) {  // Wait up to 5 seconds for the connection
        qWarning() << "SSL handshake failed:" << _clientSocket->errorString();
        return;
    }

}

void Communicator::onEncrypted() {
    qDebug() << "Encrypted connection established";
    sendMessage("Hello from Client", "hello");
}

void Communicator::disconnectFromHost()
{
    _clientSocket->disconnectFromHost();
}

void Communicator::sendMessage(const QString &text, const QString &command)
{
    if(!_clientSocket->isEncrypted()) {
        _clientSocket->waitForEncrypted(2000);
    }
    qDebug() << "send message";
    if (text.isEmpty())
        return; // We don't send empty messages
    // create a QDataStream operating on the socket
    QDataStream clientStream(_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_6_8);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("command")] = command;
    message[QStringLiteral("text")] = text;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
    qDebug() << "sent";
}

void Communicator::jsonReceived(const QJsonObject &docObj)
{
    qDebug() << "receive message";
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    qDebug() << typeVal.toString();
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //New message
        qDebug() << "recv message";
        // we extract the text field containing the chat text
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        //if (senderVal.isNull() || !senderVal.isString())
        //    return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal
        qDebug() << textVal.toString();
        emit messageReceived(senderVal.toString(), textVal.toString());
    }
}

void Communicator::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_6_8);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                // if the data was indeed valid JSON and is a JSON object
                jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}

bool Communicator::setSslCaCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(":/certs/"+path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        qWarning() << "Failed to open certificate file:" << path;
        return false;

    _sslCaCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}

void Communicator::setSslProtocol(QSsl::SslProtocol protocol)
{
    _sslProtocol = protocol;
}
