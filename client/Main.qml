import QtQuick

Window {
    width: 1080
    height: 680
    visible: true
    title: qsTr("QChatron")

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

}
