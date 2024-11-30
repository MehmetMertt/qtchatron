#include "mainpagerouter.h"

MainPageRouter::MainPageRouter(QObject *parent) : QObject(parent), _currentItem(DM_OVERVIEW), _topbarTitle("Direct Messages"), _topbarType("dm") {}

MainPageRouter::MainArea MainPageRouter::currentItem() const {
    return _currentItem;
}

void MainPageRouter::setCurrentItem(MainPageRouter::MainArea newCurrentItem, QString newTitle) {
    if (_currentItem != newCurrentItem) {
        _currentItem = newCurrentItem;

         _navigationStack.push(newCurrentItem);
        // Update the title and type based on the new page
        switch (_currentItem) {
        case DM_OVERVIEW:
            _topbarTitle = newTitle != nullptr ? newTitle : "Direct Messages";
            _topbarType = "dm";
            break;
        case CHANNEL:
            _topbarTitle = newTitle != nullptr ? newTitle : "My Channel";
            _topbarType = "channel";
            break;
        case CHAT:
            _topbarTitle = newTitle != nullptr ? newTitle : "Chat";
            _topbarType = "chat";
            break;
        }

        emit currentItemChanged();
        emit topbarTitleChanged();
        emit topbarTypeChanged();
    }
}

void MainPageRouter::back() {
    if (!_navigationStack.isEmpty()) {
        // Pop the last page from the stack
        _navigationStack.pop();
        if (!_navigationStack.isEmpty()) {
            // Set the new current item based on the last item in the stack
            setCurrentItem(_navigationStack.top());
        }
    }
}

void MainPageRouter::triggerBack()
{
    _topbarTitle = "Direct Messages";
    _topbarType = "dm";
    _currentItem = MainArea::DM_OVERVIEW;
    emit backButtonPressed();  // Call this when the back button is pressed
    emit topbarTitleChanged();
    emit currentItemChanged();
}

void MainPageRouter::setTopbarTitle(QString newTitle)
{

    _topbarTitle = newTitle;
}

QString MainPageRouter::topbarTitle() const {
    return _topbarTitle;
}

QString MainPageRouter::topbarType() const {
    return _topbarType;
}

