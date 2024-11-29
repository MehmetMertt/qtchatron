// Topbar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    id: topbar
    height: 50
    color: "#252328"
    clip: true

    property var pageTitle: "Direct Messages"
    property var pageType: "dm"

    signal toggleChannelInfobar()

    Rectangle {
        color: "transparent"
        anchors.fill: parent
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
        anchors.leftMargin: -border.width
        border.width: 1
        border.color: Material.background
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10
        anchors.leftMargin: 15
        anchors.rightMargin: 15

        Text {
            id: pageTitle
            text: topbar.pageTitle
            font.pixelSize: 24
            color: Material.foreground
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }

        Item { Layout.fillWidth: true }

        Button {
            id: addDirectMessage
            text: "New"
            font.pixelSize: 18
            Layout.preferredHeight: 45
            Material.elevation: 0
            Material.roundedScale: Material.SmallScale
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            flat: true

            visible: (topbar.pageType === "dm")

            contentItem: Text {
                text: addDirectMessage.text
                font.pixelSize: 18
                color: Material.primary
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            id: showInfo
            text: "Info"
            font.pixelSize: 18
            Layout.preferredHeight: 45
            Material.elevation: 0
            Material.roundedScale: Material.SmallScale
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            flat: true

            visible: (topbar.pageType === "channel")

            contentItem: Text {
                text: showInfo.text
                font.pixelSize: 18
                color: Material.foreground
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                topbar.toggleChannelInfobar()
            }
        }

    }
}
