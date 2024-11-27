#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool _loading READ loading WRITE setLoading NOTIFY loadingChanged)

public:
    explicit Client(QObject *parent = nullptr);
    void start();

    bool loading() const;
    void setLoading(bool newLoading);

private:
    QPair<QString, quint16> loadConfiguration();
    bool _loading;

signals:
    void loadingChanged();
};

#endif // CLIENT_H
