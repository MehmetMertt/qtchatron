// Sidebar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0
import ClientObjects 1.0 as ClientData

import "../channels"

Rectangle {
    id: sidebar
    width: 80
    color: Material.background

    property list<ChannelModel> channels

    signal addChannel();

    // Friends Icon
    ToolButton {
        id: friendsIcon
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.top: parent.top

        height: 50
        width: 50

        icon.source: "qrc:/icons/contacts_icon.png"  // Replace with an actual path to your icon
        icon.color: "#FFFFFF"
        icon.height: 35
        icon.width: 35

        background: Rectangle {
            color: "#2A2A2A"  // Button background color
            radius: width / 2  // Makes the button fully round
            border.color: MainPageRouter.currentItem == MainPageRouter.DM_OVERVIEW ? "lightgrey" : "transparent"
            border.width: 1
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(MainPageRouter.currentItem != MainPageRouter.DM_OVERVIEW) {
                    MainPageRouter.setCurrentItem(MainPageRouter.DM_OVERVIEW)
                }
            }
        }
    }

    ToolSeparator {
        id: sidebarFriendsSeparator
        anchors.top: friendsIcon.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        orientation: Qt.Horizontal
    }

    ScrollView {
        id: channelScrollView
        anchors.top: sidebarFriendsSeparator.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: channelAddIcon.top
        anchors.bottomMargin: 10
        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        ListView {
            id: channelListView
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            model: ClientData.SessionUser.channelList
            delegate: ChannelIcon {}
        }
    }

    ToolButton {
        id: channelAddIcon
        width: 45
        height: 45
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.bottom: sidebarUserSeparator.top

        icon.source: "qrc:/icons/add_plus_icon.png"  // Replace with an actual path to your icon
        icon.color: Material.primary
        icon.height: 35
        icon.width: 35

        background: Rectangle {
            anchors.fill: parent
            radius: width/5
            color: "black"
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                sidebar.addChannel()
                console.log("Channel clicked: add")
            }
            hoverEnabled: true
            onEntered: {
                scaleAnimation.start()
            }
            onExited: {
                scaleDownAnimation.start()
            }

        }
    }

    PropertyAnimation {
        id: scaleAnimation
        target: channelAddIcon
        property: "scale"
        to: 1.05  // Scale up by 10%
        duration: 100
        easing.type: Easing.InOutQuad
    }

    PropertyAnimation {
        id: scaleDownAnimation
        target: channelAddIcon
        property: "scale"
        to: 1  // Back to original scale
        duration: 100
        easing.type: Easing.InOutQuad
    }

    ToolSeparator {
        id: sidebarUserSeparator
        anchors.bottom: userIcon.top
        anchors.horizontalCenter: parent.horizontalCenter
        orientation: Qt.Horizontal
    }

    // User Profile Circle
    Rectangle {
        id: userIcon
        width: 55
        height: 55
        radius: width/2
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        border.color: "#00A6E0"
        border.width: 1

        Text {
            text: ClientData.SessionUser.user.getInitials()
            color: userIconArea.containsMouse ? "#00A6E0" : "white"
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }

        MouseArea {
            id: userIconArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onClicked: {
                profileMenu.open()
            }
        }
    }

    Menu {
        id: profileMenu
        x: sidebar.width + 15
        y: sidebar.height - userIcon.height - 120

        Item {
            width: parent.width
            height: 50
            Text {
                text: ClientData.SessionUser.user.username
                font.pixelSize: 20
                color: Material.foreground
                leftPadding: 15
                topPadding: 5
            }
        }

        MenuItem {

            background: Rectangle {
                color: "transparent"
            }

            contentItem: Text {
                text: "Settings"
                font.pixelSize: 16
                color: settingsItemArea.containsMouse ? "#00A6E0" : "white"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                id: settingsItemArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onClicked: {
                    console.log("Settings clicked")
                    MainPageRouter.setCurrentItem(MainPageRouter.SETTINGS)
                    profileMenu.close()
                }
            }
        }

        MenuItem {

            background: Rectangle {
                color: "transparent"
            }

            contentItem: Text {
                text: "Logout"
                font.pixelSize: 16
                color: logoutItemArea.containsMouse ? "#00A6E0" : "white"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                id: logoutItemArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onClicked: {
                    console.log("Logout clicked")
                }
            }
        }
    }
}

