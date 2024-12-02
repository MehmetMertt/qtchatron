import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Client 1.0

Rectangle {
    id: settingsPage
    color: "#252328" // Dark theme background color

    property color accentColor: "#00A6E0" // Default accent color (cyan)

    Rectangle {
        width: settingsPage.width / 5 * 3
        height: parent.height - parent.height/10
        anchors.centerIn: parent
        anchors.topMargin: 20
        color: "transparent" // Slightly lighter background for the inner section

        ColumnLayout {
            spacing: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.fill: parent
            anchors.margins: 20

            RowLayout {
                spacing: 10
                Layout.fillWidth: true

                Label {
                    text: "Username:"
                    color: "white"
                    font.pixelSize: 20
                    Layout.preferredWidth: 150
                }
                TextField {
                    id: channelNameField
                    placeholderText: "Enter a username"
                    text: SessionUser.user.username
                    topPadding: 10
                    bottomPadding: 10
                    font.pixelSize: 18
                    Layout.preferredWidth: 300
                    Layout.maximumWidth: 300
                    background: Rectangle {
                        color: "transparent"
                        border.color: "#cccccc"
                        radius: 5
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                Label {
                    text: "Password:"
                    color: "white"
                    font.pixelSize: 20
                    Layout.preferredWidth: 150
                }
                TextField {
                    Layout.minimumWidth: parent.width/3*2
                    id: passwordField
                    placeholderText: "Enter a new password"
                    topPadding: 10
                    bottomPadding: 10
                    font.pixelSize: 18
                    Layout.preferredWidth: 300
                    Layout.maximumWidth: 300
                    echoMode: TextInput.Password
                    background: Rectangle {
                        color: "transparent"
                        border.color: "#cccccc"
                        radius: 5
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                Label {
                    text: "Theme:"
                    color: "white"
                    font.pixelSize: 20
                    Layout.preferredWidth: 150
                }
                ComboBox {
                    id: themeSelector
                    Layout.preferredWidth: 150
                    Layout.maximumWidth: 150
                    model: ["Dark", "White"]
                    currentIndex: 0
                    onCurrentIndexChanged: {
                        //settingsPage.color = currentIndex === 0 ? "#2d2d2d" : "#ffffff";
                    }
                    background: Rectangle {
                        color: "transparent"
                        radius: 5
                        border.color: "#f7f7f7"
                    }
                    contentItem: Text {
                        text: themeSelector.currentValue
                        font.pixelSize: 18
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
                        padding: 8
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                Label {
                    text: "Accent Color:"
                    color: "white"
                    font.pixelSize: 20
                    Layout.preferredWidth: 150
                }
                ComboBox {
                    id: accentColorSelector
                    Layout.preferredWidth: 150
                    Layout.maximumWidth: 150
                    model: ["Cyan", "Red", "Green"]
                    currentIndex: 0
                    onCurrentIndexChanged: {
                        settingsPage.accentColor = currentIndex === 0 ? "#00A6E0" : (currentIndex === 1 ? "#ff0000" : "#00ff00");
                    }
                    background: Rectangle {
                        color: "transparent"
                        radius: 5
                        border.color: "#f7f7f7"
                    }
                    contentItem: Text {
                        text: accentColorSelector.currentValue
                        font.pixelSize: 18
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
                        padding: 8
                    }
                }
            }

            Button {
                id: saveButton
                text: qsTr("Save")
                Layout.alignment: Qt.AlignHCenter
                Layout.minimumWidth: 150
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
                        console.log("Saved settings")
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }


}
