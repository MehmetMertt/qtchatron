import QtQuick
import QtQuick.Controls 6.8
import QtQuick.Controls.Material

import "styles"

import "pages"


Window {
    width: 1080
    height: 680
    visible: true
    title: qsTr("QChatron")

    Material.primary: Style.primary
    Material.accent:  Style.accent
    Material.theme:   Style.theme

    StackView {
        id: mainStack
        anchors.fill: parent
        initialItem: LoginPage{}
    }



/*
    LoadingPage {
        id: loadingPage
        anchors {
            fill: parent
        }

        onLoadingFinished: {
            mainPage.visible = true
            loadingPage.visible = false
        }
    }

    MainPage {
        id: mainPage
        anchors {
            fill: parent
        }
        visible: false
    }
*/
}
