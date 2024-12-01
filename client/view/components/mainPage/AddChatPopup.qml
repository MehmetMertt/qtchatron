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
            font.pixelSize: 24
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
            font.pixelSize: 18
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
                text: qsTr("Cancel")
                Layout.fillWidth: true
                font.pixelSize: 18
                flat: true
                hoverEnabled: true
                background: Rectangle {
                    color: "transparent"
                    border.color: "#6d6d6d"
                    radius: 10
                }

                onClicked: {
                    MainPageRouter.closeNewChatPopup()  // Hide the popup
                }
            }

            Button {
                text: qsTr("Start Chat")
                Layout.fillWidth: true
                font.pixelSize: 18
                flat: true
                hoverEnabled: true
                background: Rectangle {
                    color: "#1E88E5"
                    radius: 10
                }

                onClicked: {
                    // Implement chat creation logic here
                    console.log("Starting chat with: " + usernameField.text)
                    MainPageRouter.closeNewChatPopup()  // Hide the popup after action
                }
            }
        }
    }


}
