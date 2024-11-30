import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Client 1.0


//import "../components/messageItem.qml"
pragma ComponentBehavior: Bound



Rectangle {
    id: root
    anchors.fill: parent
    color: "#252328"

    property list<ChatMessageItem> chatList: ChatMessageList.chatMessageList



    Rectangle{
        id: clientChat
        anchors.top: parent.top
        width: root.width
        anchors.bottom: root.bottom

        color: "transparent"

        ScrollView {
            anchors.fill: parent
            anchors.margins: 15
            clip: true

            ListView{
                id: chatListView
                anchors.fill: parent
                model: root.chatList
                spacing: 8

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
                icon.source: "qrc:/icons/upload.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                Layout.alignment: Qt.AlignVCenter
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
                        anchors.fill: parent

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

                        // Dynamically update height based on the number of lines
                        onTextChanged: {
                            // Count the number of lines (using "\n" as line break delimiter)
                            var lines = messageField.text.split("\n").length;
                            console.log(lines)
                            // Limit the height to 4 rows (80px) maximum
                            //inputFieldContainer.height = Math.min(((lines-1) * 20 + 50), 110);
                            bottomBar.height = Math.min((lines-1)*20 + 80, 180);
                            console.log(inputFieldContainer.height)
                        }


                    }
                }

            }

            // Emoji Button
            ToolButton {
                icon.source: "qrc:/icons/emoji.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                Layout.alignment: Qt.AlignVCenter
            }

            // GIF Button
            ToolButton {
                icon.source: "qrc:/icons/gif.png"  // Replace with an actual path to your icon
                icon.color: "#FFFFFF"
                Layout.alignment: Qt.AlignVCenter
            }

            // Send Button
            Rectangle {
                Layout.preferredWidth: 50
                Layout.preferredHeight: 50
                radius: 25
                color: "#1E88E5"
                Layout.alignment: Qt.AlignVCenter

                Image {
                    anchors.centerIn: parent
                    source: "qrc:/icons/send.png"  // Replace with an actual path to your icon
                    width: 30
                    height: 30
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Handle send action here
                    }
                }
            }
        }
    }



    //*/
}
