#include "router.h"

Router::Router(QObject *parent)
    : QObject{parent}
{}

Router::Page Router::currentPage() const
{
    return _currentPage;
}

void Router::setCurrentPage(Page newCurrentPage)
{
    qDebug() << "invoked: " << newCurrentPage;
    if (_currentPage == newCurrentPage)
        return;
    _currentPage = newCurrentPage;
    emit currentPageChanged();
}
