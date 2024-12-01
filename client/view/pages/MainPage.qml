import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material

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

        onAddChannel: {
            popupLoader.setSource("../components/mainPage/AddChannelPopup.qml")
            addChatPopup.open()
        }
    }

    Topbar {
        id: topbar
        anchors.left: sidebar.right
        anchors.top: parent.top
        anchors.right: parent.right

        onNewChatClicked: {
            popupLoader.setSource("../components/mainPage/AddChatPopup.qml")
            addChatPopup.open()
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

        function onClosePopup() {
            addChatPopup.close()
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

    Component {
        id: addChannel
        AddChannelPopup{}
    }

    Popup {
        id: addChatPopup
        modal: true
        focus: true
        anchors.centerIn: parent
        width: parent.width/2
        height: parent.height/2

        // Using Loader to load different content dynamically
        Loader {
            id: popupLoader
            anchors.fill: parent

            // Initially load AddNewChat
            sourceComponent: addNewChat
        }

        // Close the popup on clicking outside of it

    }

    Component {
        id: addNewChat
        AddChatPopup {

        }
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
