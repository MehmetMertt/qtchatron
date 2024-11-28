import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import Client 1.0

// import "styles"

import "pages"


Window {
    id: root
    width: 1080
    height: 680
    visible: true
    title: qsTr("QChatron")

    /*
    Material.primary: Style.primary
    Material.accent:  Style.accent
    Material.theme:   Style.theme
    */

    Component.onCompleted: {
        clientController.runClient()
    }

    ClientController {
        id: clientController

        onClientReady: {
            mainStack.push(mainPage)
        }
    }


    StackView {
        id: mainStack
        anchors.fill: parent
        initialItem: LoadingPage{}

        Component{
            id: mainPage
            MainPage{

            }
        }
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
