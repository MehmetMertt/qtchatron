#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QtQml>

class Router : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(Page currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)
public:
    explicit Router(QObject *parent = nullptr);

    enum Page {
        LOADING,
        MAIN,
        LOGIN,
        SIGNUP
    };
    Q_ENUM(Page)



    Page currentPage() const;

    Q_INVOKABLE void setCurrentPage(Page newCurrentPage);

private:
    Page _currentPage;





signals:
    void currentPageChanged();
};

#endif // ROUTER_H
