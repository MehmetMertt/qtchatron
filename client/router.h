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
    Q_PROPERTY(bool loadingReady WRITE setLoadingReady NOTIFY loadingReadyChanged FINAL)
    Q_PROPERTY(QString pageMessage READ pageMessage WRITE setPageMessage NOTIFY pageMessageChanged FINAL)
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

    Q_INVOKABLE void setCurrentPage(Page newCurrentPage, QString message = nullptr);
    Q_INVOKABLE void setLoadingReady(bool loadingState = true);

    QString pageMessage() const;
    void setPageMessage(const QString &newPageMessage);

private:
    Page _currentPage;
    bool _loadingReady;
    QString _pageMessage;



signals:
    void currentPageChanged();
    void loadingReadyChanged();
    void pageMessageChanged();
};

#endif // ROUTER_H
