import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Effects

Rectangle {
    id: channelPage
    color: "#252328"

    property bool isChannelInfobarVisible: true
    function toggleInfobarVisibility() {
        channelPage.isChannelInfobarVisible = !channelPage.isChannelInfobarVisible
    }

    ChannelInfobar {
        id: channelInfobar
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        visible: channelPage.isChannelInfobarVisible

    }
}

