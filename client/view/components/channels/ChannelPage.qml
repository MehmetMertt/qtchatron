import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Effects

import "../chat"

import Client 1.0

Rectangle {
    id: channelPage
    color: "#252328"

    property ChannelModel channelModel: ChannelModel

    property bool isChannelInfobarVisible: true
    function toggleInfobarVisibility() {
        channelPage.isChannelInfobarVisible = !channelPage.isChannelInfobarVisible
    }

    ChatView {
        id: chatView
        anchors.left: parent.left
        anchors.right: channelInfobar.visible ? channelInfobar.left : parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

    }

    ChannelInfobar {
        id: channelInfobar
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        visible: MainPageRouter.showChannelInfo

    }
}

