import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

Rectangle {
    id: channelIcon
    width: 50
    height: 50
    radius: width/5
    color: "black"
    anchors.horizontalCenter: parent.horizontalCenter
    scale: 1

    Text {
        anchors.centerIn: parent
        text: "C" // Display the channel name
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
        visible: false  // Initially hidden
    }

    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Channel clicked: " + model.name)
        hoverEnabled: true
        onEntered: {
            hoverIndicator.visible = true
            scaleAnimation.start()
        }
        onExited: {
            hoverIndicator.visible = false
            scaleDownAnimation.start()
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
