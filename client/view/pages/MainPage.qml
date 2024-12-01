import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

import "../components/utils"

Page {
    id: mainPage
    width: parent.width
    height: parent.height

    // Sidebar
    Rectangle {
        id: sidebar
        width: 80
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: Material.background

        // User Profile Circle
        Rectangle {
            id: profileCircle
            width: 60
            height: 60
            radius: 30
            color: Material.primary
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

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
            y: sidebar.height - profileCircle.height - 80 // Adjust y-position to match the circle

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
                    */
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

    // Main Content Area
    Item {
        id: mainContent
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom

        Rectangle {
            anchors.fill: parent
            color: Material.background  // Light gray background

            Text {
                text: "Main Content Area"
                anchors.centerIn: parent
                font.pixelSize: 24
                color: Material.primary
            }
        }
    }

    // Topbar
    Rectangle {
        id: topbar
        height: 50
        anchors.top: parent.top
        anchors.left: sidebar.right
        anchors.right: parent.right
        color: Material.background

        CustomBorder
        {
            commonBorder: false
            lBorderwidth: 0
            rBorderwidth: 0
            tBorderwidth: 0
            bBorderwidth: 1
            borderColor: Material.Grey
        }

        Text {
            text: "Topbar"
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }
}
