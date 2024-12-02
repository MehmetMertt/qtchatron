import QtQuick 2.15
import QtQuick.Layouts

import Client 1.0
import ClientObjects 1.0 as ClientData

Rectangle {
    id: threadCard
    height: 40
    radius: 5
    color: "transparent"
    width: parent.width

    required property var index
    property Thread thread: ClientData.SessionUser.channelList[MainPageRouter.selectedPageID].threadList[index]


    Rectangle {
        id: background
        anchors.fill: parent
        radius: parent.radius
        color: mouseArea.containsMouse ? "#565656" : "transparent"  // Light grey on hover, transparent otherwise
        opacity: 0.5  // Adjust opacity for a subtle effect
    }

    RowLayout {
        anchors.left: parent.left  // Align to the left of the parent
        anchors.right: parent.right
        spacing: 10  // Spacing between items
        anchors.fill: parent
        layoutDirection: Qt.LeftToRight

        anchors.leftMargin: 5


        // Text Label
        Text {
            text: threadCard.thread.threadName  // Display the channel or user name
            color: "white"  // Text color
            font.pixelSize: 16  // Adjust font size as needed // Vertically center the text
        }

        Item { Layout.fillWidth: true }

    }

    // MouseArea to handle hover and clicks
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            MainPageRouter.setCurrentItem(MainPageRouter.THREAD, threadCard.thread.threadName)
            console.log("Channel clicked: " + threadCard.thread.threadName)
        }

        // Optionally handle hover effect if you want a different color on mouse enter/leave
        /*onMouseAreaClicked: {
            // Handle mouse click event here if needed
        }*/
    }



}
