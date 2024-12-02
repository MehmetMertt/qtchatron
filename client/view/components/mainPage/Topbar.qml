// Topbar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Basic

import Client 1.0
import ClientObjects 1.0 as ClientData

Rectangle {
    id: topbar
    height: 50
    color: "#252328"
    clip: true

    signal newChatClicked()

    Connections {
        target: ClientData.SessionUser
        function onThreadPopupSuccess(threadname, channelID, threadId) {
            console.log(threadname)
            console.log(threadId)
            console.log(channelID)
            MainPageRouter.setSelectedPageID(channelID)
            MainPageRouter.setSelectedSubPageID(threadId)
            console.log(ClientData.SessionUser.channelList[channelID].threadList[threadId])

            ThreadModel.currentThread = ClientData.SessionUser.channelList[channelID].threadList[threadId]

            addThreadInput.visible = false
            MainPageRouter.setCurrentItem(MainPageRouter.THREAD, threadname)
        }

        function onThreatCreationFailure(message) {

        }
    }

    Rectangle {
        color: "transparent"
        anchors.fill: parent
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
        anchors.leftMargin: -border.width
        border.width: 1
        border.color: "#222323"
    }

    Rectangle {
        id: addThreadInput
        width: 300
        height: parent.height
        color: "transparent"
        visible: false
        anchors.centerIn: parent


        RowLayout {
            TextField {
                id: threadNameField
                placeholderText: "Enter thread name"
                topPadding: 5
                bottomPadding: 5
                font.pixelSize: 16
                background: Rectangle {
                    color: "transparent"
                    border.color: "#cccccc"
                    radius: 5
                }
            }

            Button {
                id: actionButton
                text: "Create"
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
                    text: "Create"
                    font.pixelSize: 18
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
                        ClientData.SessionUser.processThreadCreation(threadNameField.text, MainPageRouter.selectedPageID)
                    }
                }
            }


        }
    }


        RowLayout {
            id: rowLayout
            anchors.fill: parent
            spacing: 10
            anchors.leftMargin: 15
            anchors.rightMargin: 15


            ToolButton {
                id: backButton
                icon.source: "qrc:/icons/back_icon.png"  // Replace with an actual path to your icon
                icon.color: "#686868"
                icon.height: 30
                icon.width: 40

                visible: MainPageRouter.currentItem !== MainPageRouter.DM_OVERVIEW  // Conditional visibility


                background: Rectangle {
                    color: "transparent"  // Make background transparent
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        MainPageRouter.triggerBack();  // Call the back method
                    }
                }
            }


            Text {
                id: pageTitle
                text: MainPageRouter.topbarTitle
                font.pixelSize: 24
                color: "#c2c4c4"
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }

            Item { Layout.fillWidth: true }

            Button {
                id: addDirectMessage
                text: "New"
                font.pixelSize: 18
                Layout.preferredHeight: 45
                flat: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                background: Rectangle {
                    color: "transparent"
                }

                visible: (MainPageRouter.currentItem == MainPageRouter.DM_OVERVIEW)

                contentItem: Text {
                    text: addDirectMessage.text
                    font.pixelSize: 18
                    color: "#00A6E0"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: addDirectMessageArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        console.log("new chat clicked")
                        topbar.newChatClicked()
                    }
                }
            }

            Button {
                id: addThread
                text: "Create Thread"
                font.pixelSize: 18
                Layout.preferredHeight: 45
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                flat: true

                visible: (MainPageRouter.currentItem == MainPageRouter.CHANNEL)

                contentItem: Text {
                    text: addThread.text
                    font.pixelSize: 18
                    color: "#00A6E0"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: addThreadArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        addThreadInput.visible = !addThreadInput.visible;
                    }
                }
            }



            Button {
                id: showInfo
                text: "Info"
                font.pixelSize: 18
                Layout.preferredHeight: 45
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                flat: true

                visible: (MainPageRouter.currentItem == MainPageRouter.CHANNEL)

                contentItem: Text {
                    text: showInfo.text
                    font.pixelSize: 18
                    color: "#00A6E0"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: showInfoArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        MainPageRouter.showChannelInfo = !MainPageRouter.showChannelInfo
                    }
                }
            }


        }


}
