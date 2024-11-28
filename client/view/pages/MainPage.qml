import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Controls.Material 2.15

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
        color: Material.background  // Dark color for sidebar (like Discord)

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
