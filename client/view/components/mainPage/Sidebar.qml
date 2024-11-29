// Sidebar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import "../channels"

Rectangle {
    id: sidebar
    width: 80
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: Material.background

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
                // show friends page in main area
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

        Text {
            text: "A"
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
            width: 200
            height: 50
            RowLayout {
                anchors.fill: parent
                spacing: 10
                Text {
                    text: "Username"
                    font.pixelSize: 16
                    color: Material.foreground
                    Layout.alignment: Qt.AlignLeft
                    leftPadding: 5
                }
            }
        }

        MenuItem {
            text: "Settings"
            onTriggered: console.log("Settings clicked")
        }

        MenuItem {
            text: "Logout"
            onTriggered: {
                console.log("logout clicked")
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
