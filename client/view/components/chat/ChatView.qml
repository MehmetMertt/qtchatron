import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Client 1.0


//import "../components/messageItem.qml"

Rectangle {
    id: root
    color: "#252328"

    property list<ChatMessageItem> chatList: MessageModel.messageList
    property var messageModel: MessageModel

    Connections{
        target: root.messageModel
        function onSendMessageSuccess() {
            messageField.text = ""
            chatListView.positionViewAtEnd();
        }
    }

    Rectangle{
        id: clientChat
        anchors.top: parent.top
        width: root.width
        anchors.bottom: bottomBar.top

        color: "transparent"

        ScrollView {
            anchors.fill: parent
            clip: true


            ListView{
                id: chatListView
                anchors.fill: parent
                anchors.margins: 20
                model: root.chatList
                spacing: 8

                onMovementEnded: {
                    chatListView.returnToBounds();  // Stops the list immediately
                }
/*
                highlightMoveDuration: 1000
                highlightMoveVelocity: -1
                */

                highlightFollowsCurrentItem: true

                delegate:
                    ChatListItem {}
            }
        }
    }

    // Add a MouseArea for the entire screen or the parent Rectangle to unfocus the input field
    MouseArea {
        id: screenMouseArea
        anchors.fill: parent
        onClicked: {
            // Unfocus the input field if clicked anywhere outside
            if (messageField.activeFocus && !inputFocusArea.containsMouse) {
                forceActiveFocus() // Remove focus
            }
        }
    }

    Rectangle {
        id: bottomBar
        width: parent.width
        height: 80
        anchors.bottom: parent.bottom
        color: "#121212"

        RowLayout {
            anchors.fill: parent
            spacing: 12
            anchors.margins: 10

            // Upload Button (Plus Icon)
            ToolButton {
                icon.source: "qrc:/icons/add_plus_icon.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                icon.height: 35
                icon.width: 35
                Layout.alignment: Qt.AlignVCenter

                background: Rectangle {
                    color: "#2A2A2A"  // Button background color
                    radius: width / 2  // Makes the button fully round
                }
            }

            // Input Field Background
            Rectangle {
                id: inputFieldContainer
                Layout.fillWidth: true
                Layout.minimumHeight: 50
                Layout.fillHeight: true
                border.color: "#3A3A3A"
                border.width: 1
                color: "#2A2A2A" // Dark background for the input field
                radius: 25  // Rounded corners

                // Behavior for smooth border color change
                Behavior on border.color {
                    ColorAnimation {
                        duration: 100  // Duration for the fade-in effect (100ms)
                        easing.type: Easing.InOutQuad  // Optional easing for smooth transition
                    }
                }

                // MouseArea to detect focus inside the input field
                MouseArea {
                    id: inputFocusArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        messageField.forceActiveFocus()  // Manually set focus on the TextArea
                    }
                }

                ScrollView {
                    id: view
                    anchors.fill: parent
                    anchors.margins: 10

                    TextArea {
                        id: messageField

                        //verticalAlignment: Qt.AlignTop
                        wrapMode: TextArea.Wrap
                        placeholderText: qsTr("Type your message here...")

                        font.pixelSize: 16
                        color: "#D0D0D0" // Lighter text color
                        background: Rectangle {
                            color: "transparent"
                        }
                        opacity: 0.9
                        selectByMouse: true

                        // Focus change event to update border color
                        onActiveFocusChanged: {
                            if (activeFocus) {
                                inputFieldContainer.border.color = "#1E88E5"  // Blue border on focus
                            } else {
                                inputFieldContainer.border.color = "#2A2A2A"  // Default border color when not focused
                            }
                        }
                        Keys.onPressed: (event)=> {
                            if ((event.key+1 == Qt.Key_Enter && (event.modifiers == 0 || event.modifiers == Qt.ControlModifier))){
                                sendButton.sendMessage()
                                event.accepted = true;
                            }
                        }
                        // Dynamically update height based on the number of lines
                        onTextChanged: {
                            // Count the number of lines (using "\n" as line break delimiter)
                            var lines = messageField.text.split("\n").length;
                            //console.log(lines)
                            // Limit the height to 4 rows (80px) maximum
                            //inputFieldContainer.height = Math.min(((lines-1) * 20 + 50), 110);
                            bottomBar.height = Math.min((lines-1)*20 + 80, 180);
                            //console.log(inputFieldContainer.height)

                            root.messageModel.inputMessage = messageField.text
                        }



                    }

                    /*
                    Shortcut{
                        sequence: messageField.visible ? "Ctrl+Return" : ""
                        onActivated: sendButton.sendMessage()
                    }
                    */
                }

            }

            // Emoji Button
            ToolButton {
                icon.source: "qrc:/icons/emoji_icon.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                icon.height: 35
                icon.width: 35
                Layout.alignment: Qt.AlignVCenter

                background: Rectangle {
                    color: "#2A2A2A"  // Button background color
                    radius: width / 2  // Makes the button fully round
                }
            }

            // GIF Button
            ToolButton {
                icon.source: "qrc:/icons/gif2_icon.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                icon.height: 35
                icon.width: 35
                Layout.alignment: Qt.AlignVCenter

                background: Rectangle {
                    color: "#2A2A2A"  // Button background color
                    radius: width / 2  // Makes the button fully round
                }
            }

            // Send Button
            Rectangle {
                id: sendButton
                Layout.preferredWidth: 80
                Layout.preferredHeight: 45
                radius: 25
                color: "#1E88E5"
                Layout.alignment: Qt.AlignVCenter

                Image {
                    anchors.centerIn: parent
                    source: "qrc:/icons/send_icon.png"  // Replace with an actual path to your icon
                    width: 30
                    height: 30
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        sendButton.sendMessage()
                    }
                }

                function sendMessage(){
                    let trimmedMessage = messageField.text.trim();  // Remove leading and trailing whitespace

                    // Check if the message is empty after trimming
                    if(trimmedMessage === "") {
                        return;  // Don't send if the message is empty
                    }
                    root.messageModel.inputMessage = trimmedMessage
                    root.messageModel.sendMessage()
                    messageField.text = ""
                }
            }

        }
    }



    //*/
}
