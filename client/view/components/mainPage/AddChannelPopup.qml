import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic

Rectangle {
    id: channelPopupContent
    color: "transparent"
    anchors.fill: parent

    ColumnLayout {
        spacing: 5
        anchors.centerIn: parent
        width: parent.width/5 * 3
        height: parent.height - parent.height/10

        TabBar {
            Layout.fillWidth: true
            id: tabBar
            font.pixelSize: 14
            background: Rectangle {
                color: "transparent"
            }
            TabButton {
                text: "Join Channel"
                contentItem: Text {
                    text: qsTr("Join Channel")
                    font.pixelSize: 14
                    color: "#f7f7f7"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: "transparent"
                    border.color: tabBar.currentIndex == 0 ? "#00A6E0" : "transparent"
                    border.width: 1
                    radius: 5
                }

            }
            TabButton {
                text: "Create Channel"

                contentItem: Text {
                    text: qsTr("Create Channel")
                    font.pixelSize: 14
                    color: "#f7f7f7"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: "transparent"
                    border.color: tabBar.currentIndex == 1 ? "#00A6E0" : "transparent"
                    border.width: 1
                    radius: 5
                }
            }


        }

        ColumnLayout {
            Layout.alignment: Qt.AlignJustify
            Layout.margins: 10
            Layout.bottomMargin: 0
            spacing: 10

            Label {
                text: "Channel Name:"
                color: "white"
                font.pixelSize: 16
            }
            TextField {
                id: channelNameField
                placeholderText: "Enter channel name"
                topPadding: 10
                bottomPadding: 10
                font.pixelSize: 14
                Layout.fillWidth: true
                background: Rectangle {
                    color: "transparent"
                    border.color: "#cccccc"
                    radius: 5
                }
            }
        }

        StackLayout {
            id: tabContent
            currentIndex: tabBar.currentIndex
            Layout.fillWidth: true
            Layout.margins: 10

            ColumnLayout {
                Layout.alignment: Qt.AlignJustify
                spacing: 10


                Label {
                    text: "Secret Key:"
                    color: "white"
                    font.pixelSize: 16
                }
                TextField {
                    id: secretKeyField
                    placeholderText: "Enter secret key (optional)"
                    topPadding: 10
                    bottomPadding: 10
                    font.pixelSize: 14
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: "transparent"
                        border.color: "#cccccc"
                        radius: 5
                    }
                }
            }

            ColumnLayout {
                spacing: 10
                Row {
                    spacing: 10
                    ButtonGroup { id: visibilityButtonGroup }
                    CheckBox {
                        text: "Private Server"
                        ButtonGroup.group: visibilityButtonGroup
                    }
                    CheckBox {
                        text: "Public Server"
                        ButtonGroup.group: visibilityButtonGroup
                    }
                }
                Row {
                    spacing: 10
                    ButtonGroup { id: channelTypeButtonGroup }
                    CheckBox {
                        text: "Text Channel"
                        ButtonGroup.group: channelTypeButtonGroup
                    }
                    CheckBox {
                        text: "Voice Channel"
                        ButtonGroup.group: channelTypeButtonGroup
                    }
                }
            }
        }

        Button {
            id: actionButton
            text: tabBar.currentIndex === 0 ? "Join" : "Create"
            Layout.fillWidth: true
            font.pixelSize: 16
            flat: true
            hoverEnabled: true


            background: Rectangle {
                id: buttonBackground
                color: actionButton.hovered ? "#00A6E0" : "transparent"
                radius: 5
                border.color: "#00A6E0"
                border.width: 1
            }

            contentItem: Text {
                text: tabBar.currentIndex === 0 ? "Join" : "Create"
                font.pixelSize: 22
                color: actionButton.hovered ? "white" : "#00A6E0"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                id: actionButtonArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                onClicked: {
                    if (tabBar.currentIndex === 0) {
                        console.log("Join Channel with details entered")
                    } else {
                        console.log("Create Channel with details entered")
                    }
                }
            }
        }
    }
}
