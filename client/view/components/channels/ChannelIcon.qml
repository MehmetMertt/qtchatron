import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0
import ClientObjects 1.0 as ClientData

Rectangle {
    id: channelIcon
    width: 50
    height: 50
    radius: width/5
    color: "black"
    anchors.horizontalCenter: parent.horizontalCenter
    scale: 1

    required property var index
    property Channel channel: ClientData.SessionUser.channelList[index]

    Component.onCompleted: {
        console.log(channel.channelID)
        console.log(ClientData.SessionUser.channelList.length)
    }

    Connections {
        target: MainPageRouter
        function onTopbarTitleChanged() {
            if(MainPageRouter.topbarTitle != channelIcon.channel.channelName) {
                hoverIndicator.visible = false
                scaleDownAnimation.start()
            }
        }
    }

    Text {
        anchors.centerIn: parent
        text: channelIcon.channel.channelName[0] + channelIcon.channel.channelName[1]
        color: "white"
        font.pixelSize: 20
        anchors.horizontalCenterOffset: -2
    }

    Rectangle {
        id: hoverIndicator
        width: 2
        height: 10
        color: "white"  // Green indicator
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        visible: MainPageRouter.topbarTitle == channelIcon.channel.channelName ? true : false  // Initially hidden
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ChannelModel.setChannel(channelIcon.channel)
            MainPageRouter.setSelectedPageID(channelIcon.index)
            MainPageRouter.setCurrentItem(MainPageRouter.CHANNEL, channelIcon.channel.channelName)
            console.log("Channel clicked: " + channelIcon.channel.channelName)
        }
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onEntered: {
            hoverIndicator.visible = true
            scaleAnimation.start()
        }
        onExited: {
            if(MainPageRouter.topbarTitle != channelIcon.channel.channelName) {
                hoverIndicator.visible = false
                scaleDownAnimation.start()
            }
        }

    }

    PropertyAnimation {
        id: scaleAnimation
        target: channelIcon
        property: "scale"
        to: 1.05  // Scale up by 10%
        duration: 100
        easing.type: Easing.InOutQuad
    }

    PropertyAnimation {
        id: scaleDownAnimation
        target: channelIcon
        property: "scale"
        to: 1  // Back to original scale
        duration: 100
        easing.type: Easing.InOutQuad
    }
}
