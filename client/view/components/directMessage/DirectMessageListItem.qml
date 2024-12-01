import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material

import Client 1.0

import "../user"

Rectangle {
    id: dmListItem
    required property User user

    width: parent.width - parent.width/10
    height: 60
    radius: 10
    color: "transparent"

    Rectangle {
        id: background
        anchors.fill: parent
        radius: parent.radius
        color: mouseArea.containsMouse ? "#707070" : "transparent"  // Light grey on hover, transparent otherwise
        opacity: 0.5  // Adjust opacity for a subtle effect
    }

    RowLayout {
        anchors.left: parent.left  // Align to the left of the parent
        anchors.right: parent.right
        spacing: 10  // Spacing between items
        anchors.fill: parent
        layoutDirection: Qt.LeftToRight

        anchors.leftMargin: 5

        // User Icon (e.g., Avatar or Image)
        UserIcon {
            initial: dmListItem.user.getInitials()
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter  // Vertically center the icon
        }

        // Text Label
        Text {
            text: dmListItem.user.username  // Display the channel or user name
            color: "white"  // Text color
            font.pixelSize: 18  // Adjust font size as needed // Vertically center the text
        }

        Item { Layout.fillWidth: true }

    }

    // MouseArea to handle hover and clicks
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            console.log("DM clicked: " + dmListItem.user.username)
            MainPageRouter.setCurrentItem(MainPageRouter.CHAT, dmListItem.user.username)
            //MainPageRouter.setTopbarTitle(dmListItem.name)
        }

        // Optionally handle hover effect if you want a different color on mouse enter/leave
        /*onMouseAreaClicked: {
            // Handle mouse click event here if needed
        }*/
    }




/*
    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Channel clicked: " + model.name)
    }
*/
}
