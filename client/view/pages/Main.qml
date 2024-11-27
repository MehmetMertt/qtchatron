import QtQuick
import QtQuick.Controls 2.5

import "MainPage.qml"


Window {
    width: 1080
    height: 680
    visible: true
    title: qsTr("QChatron")


    StackView {
        id: mainStack
        anchors.fill: parent
        initialItem: MainPage
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
