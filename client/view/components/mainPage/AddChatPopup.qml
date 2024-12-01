import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Client 1.0

Rectangle {
    id: chatPopupContent
    color: "transparent"

    ColumnLayout {
        width: parent.width/2
        height: parent.height - parent.height/5
        anchors.centerIn: parent
        spacing: 5

        // Title
        Text {
            text: "Add a new Chat"
            font.pixelSize: 20
            font.bold: true
            font.family: "Roboto"
            color: "#c9c9c9"
            Layout.alignment: Qt.AlignHCenter
        }

        // Username Field
        TextField {
            id: usernameField
            placeholderText: "Username"
            topPadding: 10
            bottomPadding: 10
            font.pixelSize: 16
            Layout.fillWidth: true
            background: Rectangle {
                color: "transparent" // Light gray background
                border.color: "#f7f7f7"
                radius: 5
            }
        }


        // Buttons Layout
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                id: cancleButton
                text: qsTr("Cancel")
                Layout.fillWidth: true
                font.pixelSize: 16
                flat: true
                hoverEnabled: true
                background: Rectangle {
                    color: "transparent"
                    border.color: cancleButtonArea.containsMouse ? "white" : "#6d6d6d"
                    radius: 5
                }

                MouseArea {
                    id: cancleButtonArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        MainPageRouter.closeNewChatPopup()
                    }
                }
            }

            Button {
                id: startChatButton
                text: qsTr("Start Chat")
                Layout.fillWidth: true
                font.pixelSize: 18
                flat: true
                hoverEnabled: true

                background: Rectangle {
                    color: startChatButtonArea.containsMouse ? "#00A6E0" : "transparent"
                    border.width: 1
                    border.color: "#00A6E0"
                    radius: 5
                }

                MouseArea {
                    id: startChatButtonArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        console.log("Starting chat with: " + usernameField.text)
                        MainPageRouter.closeNewChatPopup()
                    }
                }
            }
        }
    }


}
