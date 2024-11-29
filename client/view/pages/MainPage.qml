import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

import "../components/mainPage"
import "../components/directMessage"

Page {
    id: mainPage
    width: parent.width
    height: parent.height

    // Sidebar
    Sidebar{
        id: sidebar
    }

    Topbar {
        id: topbar
        anchors.left: sidebar.right
        pageTitle: qsTr("Myy Channel")
    }

    // Main Content Area
    DirectMessageOverviewPage {
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topbar.bottom
    }


}
