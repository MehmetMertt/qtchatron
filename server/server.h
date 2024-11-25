#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QSslSocket>
#include <QSslServer>
#include <QTcpServer>
#include <QHash>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);

public slots:
    void sendMessage(const QString &message);
    void printClients();

private slots:
    void onNewConnection();           // Handle new TCP connection and upgrade to SSL
    void onReadyRead();               // Handle data received from clients
    void onClientEncrypted();         // Handle successful SSL encryption
    void onClientDisconnected();      // Handle client disconnection
    void onNewMessage(const QByteArray &ba);  // Broadcast messages to all clients

private:
    bool loadSslCertificate();        // Load SSL certificate and private key
    QString getClientKey(const QSslSocket *client) const;  // Generate unique client key

private:
    QTcpServer _tcpServer;            // TCP server to listen for incoming connections
    QHash<QString, QSslSocket*> _clients;  // Map of connected clients (SSL sockets)
    QSslSocket _sslSocket;               // SSL socket for the server
};

#endif // SERVER_H
