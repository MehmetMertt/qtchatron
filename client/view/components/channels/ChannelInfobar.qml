import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../user"

Rectangle {
    id: channelInfobar
    width: 225
    color: "#232226" //bit darker dark

    //Border
    Rectangle {
        color: "transparent"
        anchors.fill: parent
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
        anchors.bottomMargin: -border.width
        border.width: 1
        border.color: Material.background
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width - 20
        anchors.topMargin: 10
        anchors.leftMargin: 10


        ColumnLayout {
            Text {
                id: membersTitle
                text: qsTr("Members:")
                font.pixelSize: 18
                color: Material.foreground
                Layout.fillWidth: true
            }

            ScrollView {
                id: memberScrollView
                Layout.fillWidth: true
                Layout.fillHeight: true

                clip: true

                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AsNeeded


                ListView {
                    id: memberList
                    anchors.left: parent.left
                    spacing: 5
                    model: ListModel {
                        ListElement { name: "Flo" }
                        ListElement { name: "Mehmet" }
                        ListElement { name: "Michi" }
                        ListElement { name: "Martin" }
                        // Add more channels as needed
                    }

                    delegate: UserCard {}
                }
            }
        }

        /*
        ColumnLayout {
            Text {
                id: threatsTitle
                text: qsTr("Threads:")
                font.pixelSize: 18
                color: Material.foreground
                Layout.fillWidth: true
            }

            ScrollView {
                id: threadsScrollView
                Layout.fillWidth: true
                Layout.fillHeight: true

                clip: true

                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AsNeeded


                ListView {
                    id: threadsList
                    anchors.left: parent.left
                    spacing: 5
                    model: ListModel {
                        ListElement { name: "Thread1" }
                        ListElement { name: "Was ist denn das" }
                        ListElement { name: "Yooooo" }
                        // Add more channels as needed
                    }

                    delegate: Item {

                        Text {
                            text: qsTr("# " + name)
                        }

                    }
                }
            }
        }
        */


    }

}
