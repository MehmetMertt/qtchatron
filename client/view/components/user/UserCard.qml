import QtQuick 2.15
import QtQuick.Layouts

import Client 1.0

Rectangle {
    id: userCard
    height: 40
    radius: 5
    color: "transparent"
    width: parent.width

    required property var index
    property User user: ChannelModel.memberList[index]


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

        // User Icon (e.g., Avatar or Image)
        UserIcon {
            scaleI: 0.8
            initial: userCard.user.getInitials()
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter  // Vertically center the icon
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
        }

        // Text Label
        Text {
            text: userCard.user.username  // Display the channel or user name
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
            MainPageRouter.setCurrentItem(MainPageRouter.CHAT, userCard.user.username)
            console.log("Channel clicked: " + userCard.user.username)
        }

        // Optionally handle hover effect if you want a different color on mouse enter/leave
        /*onMouseAreaClicked: {
            // Handle mouse click event here if needed
        }*/
    }



}
