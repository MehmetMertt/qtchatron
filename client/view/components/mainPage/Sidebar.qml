// Sidebar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

import "../channels"

Rectangle {
    id: sidebar
    width: 80
    color: Material.background

    property list<ChannelModel> channels

    signal addChannel();

    // Friends Icon
    Rectangle {
        id: friendsIcon
        width: 50
        height: 50
        radius: 30
        color: "black"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.top: parent.top

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                MainPageRouter.setCurrentItem(MainPageRouter.DM_OVERVIEW)
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
            model: SessionUser.channelList
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
        width: 60
        height: 60
        radius: width/2
        color: Material.primary
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        Text {
            text: SessionUser.user.getInitials()
            color: "white"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
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
                text: SessionUser.user.username
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

/*
    Rectangle {
        id: sidebar
        width: 80
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: Material.background


        Rectangle {
            id: friendsIcon
            width: 50
            height: 50
            radius: 30
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            anchors.top: parent.top



            // Menu on Click
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    //show friends page in main area
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
            anchors.bottom: sidebarUserSeparator.top
            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff


            ListView {
                id: channelList

                anchors.horizontalCenter: parent.horizontalCenter

                spacing: 10
                model: ListModel {
                    ListElement { name: "Channel 1" }
                    ListElement { name: "Channel 2" }
                    ListElement { name: "Channel 3" }
                    ListElement { name: "Channel 4" }
                    // Add more channels as needed
                }

                delegate: ChannelIcon {}
            }

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
            width: 60
            height: 60
            radius: width/2
            color: Material.primary
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            // Profile initials or icon
            Text {
                text: "A" // Placeholder for profile initial or icon
                color: "white"
                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
            }

            // Menu on Click
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    profileMenu.open()
                }
            }
        }

        // Popup Menu
        Menu {
            id: profileMenu
            x: sidebar.width + 15 // Position near the sidebar
            y: sidebar.height - userIcon.height - 120 // Adjust y-position to match the circle

            Item {
                width: 200
                height: 50

                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    // Left-Aligned Username
                    Text {
                        text: "Username" // Replace with dynamic username
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        Layout.alignment: Qt.AlignLeft
                        color: Material.foreground
                        leftPadding: 5
                    }

                    /*
                    // Right-Aligned Icons
                    RowLayout {
                        Layout.alignment: Qt.AlignRight

                        // Mute Icon
                        Image {
                            source: "mute-icon.png" // Replace with your mute icon path
                            Layout.preferredWidth: 24
                            Layout.preferredHeight: 24
                            fillMode: Image.PreserveAspectFit
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: console.log("Mute clicked")
                            }
                        }

                        // Deaf Icon
                        Image {
                            source: "deaf-icon.png" // Replace with your deaf icon path
                            Layout.preferredWidth: 24
                            Layout.preferredHeight: 24
                            fillMode: Image.PreserveAspectFit
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: console.log("Deaf clicked")
                            }
                        }
                    }

                }
            }

            // Settings Action
            MenuItem {
                text: "Settings"
                onTriggered: console.log("Settings clicked")
            }

            // Logout Action
            MenuItem {
                text: "Logout"
                onTriggered: {
                    console.log("logout: " + SessionModel.currentUsername)
                    console.log("Logout clicked")
                }
            }
        }
    }

*/
