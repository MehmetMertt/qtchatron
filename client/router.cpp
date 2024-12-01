#include "router.h"

Router::Router(QObject *parent)
    : QObject{parent},
    _loadingReady(false)
{}

Router::Page Router::currentPage() const
{
    return _currentPage;
}

void Router::setCurrentPage(Page newCurrentPage, QString message)
{
    setPageMessage(message);
    //qDebug() << "invoked: " << newCurrentPage;
    if (_currentPage == newCurrentPage)
        return;
    _currentPage = newCurrentPage;
    emit currentPageChanged();
}

void Router::setLoadingReady(bool loadingState)
{
    _loadingReady = loadingState;
    emit loadingReadyChanged();
}

QString Router::pageMessage() const
{
    return _pageMessage;
}

void Router::setPageMessage(const QString &newPageMessage)
{
    if (_pageMessage == newPageMessage)
        return;
    _pageMessage = newPageMessage;
    emit pageMessageChanged();
}
