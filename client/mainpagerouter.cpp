#include "mainpagerouter.h"

MainPageRouter::MainPageRouter(QObject *parent) : QObject(parent),
    _currentItem(DM_OVERVIEW),
    _topbarTitle("Direct Messages"),
    _topbarType("dm"),
    _showChannelInfo(true)
{}

MainPageRouter::MainArea MainPageRouter::currentItem() const {
    return _currentItem;
}

void MainPageRouter::setCurrentItem(MainPageRouter::MainArea newCurrentItem, QString newTitle) {
    if (_currentItem != newCurrentItem || newTitle != _topbarTitle) {
        _currentItem = newCurrentItem;

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

void MainPageRouter::triggerBack()
{
    _topbarTitle = "Direct Messages";
    _topbarType = "dm";
    _currentItem = MainArea::DM_OVERVIEW;
    emit backButtonPressed();  // Call this when the back button is pressed
    emit topbarTitleChanged();
    emit topbarTypeChanged();
    emit currentItemChanged();
}

void MainPageRouter::closeNewChatPopup()
{
    emit closePopup();
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

bool MainPageRouter::showChannelInfo() const
{
    return _showChannelInfo;
}

int MainPageRouter::selectedPageID() const
{
    return _selectedPageID;
}

void MainPageRouter::setSelectedPageID(int newSelectedPageID)
{
    if (_selectedPageID == newSelectedPageID)
        return;
    _selectedPageID = newSelectedPageID;
    emit selectedPageIDChanged();
}

void MainPageRouter::setShowChannelInfo(bool newShowChannelInfo)
{
    if (_showChannelInfo == newShowChannelInfo)
        return;
    _showChannelInfo = newShowChannelInfo;
    emit showChannelInfoChanged();
}

