import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Client 1.0


//import "../components/messageItem.qml"
pragma ComponentBehavior: Bound

Rectangle {
    id: root
    anchors.fill: parent

    property list<ChatMessageItem> chatList: ChatMessageList.chatMessageList


    Rectangle{
        id: clientChat
        height: parent.height
        width: parent.width
        anchors.bottom: root.bottom
        color: "#252328" // <- das ein scheiß

        ScrollView {
            anchors.fill: parent

            clip: true

            ListView{
                id: chatListView
                anchors.fill: parent
                model: root.chatList
                spacing: 8

                highlightFollowsCurrentItem: true

                delegate: Item{
                    id: itemRoot
                    anchors.left: parent.left
                    anchors.right: parent.right

                    required property string sender
                    required property string message
                    required property string time
                    required property int index


                    Component.onCompleted: {
                        console.log("delegate loaded");
                        console.log(root.chatList[index].sender)
                    }

                    //height: showTime ? messageRectangle.height + 25 : messageRectangle.height
                    height: 40
                    width: messageRectangle.width
                    x: sender ? 0 : chatListView.width - width



                    property bool showTime: root.chatList.length -1 === index ? true : root.chatList[index].sender !== sender

                    Rectangle{
                        id: messageRectangle
                        width: Math.min(messageText.implicitWidth + 24, (chatListView.width * 0.8))
                        anchors.fill: parent
                        color: "transparent"

                        Text{
                            id: messageText
                            text: itemRoot.message
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                            color: Material.foreground
                            font.pixelSize: 18
                            verticalAlignment: Qt.AlignVCenter
                            horizontalAlignment: itemRoot.sender == "flo" ? Qt.AlignLeft : Qt.AlignRight
                        }
                    }
                    Text{
                        anchors.top: messageRectangle.bottom
                        anchors.topMargin: 10
                        anchors.right: itemRoot.sender ? undefined : parent.right
                        horizontalAlignment: itemRoot.sender ? Qt.AlignLeft : Qt.AlignRight
                        text: itemRoot.time
                        width: messageRectangle.width
                        height:20
                        visible: itemRoot.showTime
                    }
                }
                //*/
            }
        }
    }

    Rectangle{
        id: bottomBar
        width: parent.width
        height: 50
        anchors.bottom: clientChat.bottom
        anchors.horizontalCenter: clientChat.horizontalCenter
        color: "#1E2225"
    }

    Rectangle{
        id: inputFieldBackground
        width: bottomBar.width - 20
        height: bottomBar.height - 20
        anchors.top: bottomBar.top
        anchors.horizontalCenter: bottomBar.horizontalCenter
        anchors.margins: +10 // fürs erste von allen seiten 10, weil ka was alles rund herum ums input field kommt
        color: "#1E88E5"
        radius: 3 // damit das so schön mit dem automatischen border von textfield überinpasst

        TextField {
            id: inputField
            anchors.bottom: inputFieldBackground.bottom
            anchors.left: inputFieldBackground.left
            anchors.right: inputFieldBackground.right
            width: inputFieldBackground.width
            height: inputFieldBackground.height
            text: qsTr("Enter your message ...")
            color: "#FFFFFF" // Platzhalter-Farbe
            onFocusChanged: {
                if (focus && text === qsTr("Enter your message ...")) {
                    text = "";
                    color = "#FFFFFF"; // Textfarbe nach Fokuserhalt ändern
                } else if (!focus && text === "") {
                    text = qsTr("Enter your message ...");
                    color = "#FFFFFF";
                }
            }
        }
    }
    //*/
}
