import QtQuick 6.8
import QtQuick.Controls 6.8

import "../components/utils"

Page {
    id: mainPage
    visible: true
    width: parent.width
    height: parent.height


    // Sidebar
    Rectangle {
        id: sidebar
        width: 80
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#e0e3e6"  // Dark color for sidebar (like Discord)

        Text {
            text: "Sidebar"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            font.bold: true
            font.pixelSize: 20
        }

        // Add sidebar content here (e.g., list of channels)
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
            color: "#F2F3F5"  // Light gray background

            Text {
                text: "Main Content Area"
                anchors.centerIn: parent
                font.pixelSize: 24
                color: "#333333"
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
        color: "#F2F3F5"  // Discord's brand color (bluish)

        CustomBorder
        {
            commonBorder: false
            lBorderwidth: 0
            rBorderwidth: 0
            tBorderwidth: 0
            bBorderwidth: 1
            borderColor: "#b0b2b5"
        }

        Text {
            text: "Topbar"
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }
}
