import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

import "../components/mainPage"
import "../components/directMessage"
import "../components/channels"
import "../components/chat"

Page {
    id: mainPage
    width: parent.width
    height: parent.height

    // Sidebar
    Sidebar{
        id: sidebar
        z: 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Topbar {
        id: topbar
        anchors.left: sidebar.right
        anchors.top: parent.top
        anchors.right: parent.right

        // Bind topbar properties to MainPageRouter
        pageTitle: MainPageRouter.topbarTitle
        pageType: MainPageRouter.topbarType

        onToggleChannelInfobar: {
            console.log("toggle")
        }
    }

    Connections {
        target: MainPageRouter
        function onCurrentItemChanged() {
            //console.log(MainPageRouter.currentItem)
            mainPage.setCurrentItem(MainPageRouter.currentItem)
        }
        function onBackButtonPressed() {
            if (mainPageStack.depth > 1) {  // Prevent popping the last page
                mainPageStack.pop();
            }
        }
    }


    function setCurrentItem(c_page_index) {
        let pageToShow;

        if (c_page_index === 0) {
            pageToShow = dmOverviewPage;
        } else if (c_page_index === 1) {
            pageToShow = channelPage;
        } else {
            pageToShow = chatViewPage;
        }

        // Check if the page is already on the stack
        let existingPage = mainPageStack.find(item => item === pageToShow, StackView.FirstToLast);

        if (existingPage) {
            // The page is already on the stack, pop to it
            mainPageStack.pop(mainPageStack.indexOf(existingPage) - mainPageStack.depth + 1);
        } else {
            // Page is not in the stack, push it
            mainPageStack.push(pageToShow);
        }
    }

    StackView {
        id: mainPageStack
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom
        visible: true

        initialItem: dmOverviewPage

    }

    Component{
        id: channelPage;
        ChannelPage{

        }
    }

    Component {
        id: dmOverviewPage
        DirectMessageOverviewPage {

        }
    }
    Component {
        id:chatViewPage;
        ChatView {

        }
    }


}
