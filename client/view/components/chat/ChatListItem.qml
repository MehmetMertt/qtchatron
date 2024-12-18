import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import ClientObjects 1.0 as ClientData

import "../user"

Item {
    id: itemRoot
    width: parent ? parent.width : 0  // Match ListView width
    height: messageItem.height + 20  // Height based on content

    required property var model  // Model passed from ListView

    property string sender: model.sender
    property string message: model.message
    property string time: model.time
    property int index: model.index

    // Determine if the sender is the current user (e.g., "michi")
    property bool isCurrentUser: sender === ClientData.SessionUser.user.username

    // Align message based on sender

    Row {
        spacing: 8
        anchors.left: itemRoot.isCurrentUser ? undefined : parent.left
        anchors.right: itemRoot.isCurrentUser ? parent.right : undefined
        layoutDirection: itemRoot.isCurrentUser ? Qt.RightToLeft : Qt.LeftToRight
        width: Math.min(messageText.implicitWidth + 24, (itemRoot ? itemRoot.width * 0.45 : 100))

        // User icon
        UserIcon {
            initial: itemRoot.sender[0]
        }

        Column {
            id: messageContainer
            spacing: 4
            width: parent.width
            height: messageText.implicitHeight + 32
            // Message Bubble with Text and Time
            Rectangle {
                id: messageItem
                width: parent.width
                height: parent.height - 14
                radius: 12
                color: itemRoot.isCurrentUser ? "#1565C0" : "#515151"

                // Hover effect
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: messageItem.color = itemRoot.isCurrentUser ? "#1E88E5" : "#5b5b5b"
                    onExited: messageItem.color = itemRoot.isCurrentUser ? "#1565C0" : "#515151"
                    //onExited: messageItem.color = "transparent"
                }

                // Message Text
                Text {
                    id: messageText
                    text: itemRoot.message
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Label.Wrap
                    color: Material.foreground
                    font.pixelSize: 16
                }

            }

            // Time Text
            Text {
                id: timeText
                width: parent.width
                horizontalAlignment: itemRoot.isCurrentUser ? Text.AlignRight : Text.AlignLeft
                text: itemRoot.time
                font.pixelSize: 12
                //color: itemRoot.isCurrentUser ? "#BBDEFB" : "#888888"
                color: Material.foreground
                opacity: 0.6
            }
        }
    }
}
