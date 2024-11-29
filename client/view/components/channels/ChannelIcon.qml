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

    Text {
        anchors.centerIn: parent
        text: model.name // Display the channel name
        color: "white"
        font.pixelSize: 14
    }

    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Channel clicked: " + model.name)
    }
}
