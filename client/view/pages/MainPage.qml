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
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Topbar {
        id: topbar
        anchors.left: sidebar.right
        anchors.top: parent.top
        anchors.right: parent.right
        pageTitle: qsTr("Myyy Channel")
        pageType: qsTr("channel")

        onToggleChannelInfobar: () => {
            console.log("toggle")
            channelPage.toggleInfobarVisibility()
        }
    }

    // Main Content Area
    ChannelPage {
        id: channelPage
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom
    }

    /*
    ChatView {
        id: chatViewPage
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom
    }
    */

    /*
    DirectMessageOverviewPage {
        id: dmOverviewPage
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom
    }
*/

}
