import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Client 1.0


import "pages"


Window {
    id: root
    width: 1080
    height: 680
    visible: true
    title: qsTr("QChatron")

    Material.theme: Material.Dark // or Material.Dark
    Material.accent: Material.Blue
    Material.primary: Material.Blue

    Component.onCompleted: {
        clientController.runClient()
    }

    ClientController {
        id: clientController

        onClientReady: {
            //mainStack.push(mainPage)
        }
    }


    StackView {
        id: mainStack
        anchors.fill: parent
        initialItem: LoginPage{}

        Component{
            id: mainPage
            MainPage{

            }
        }

        Component{
            id: loginPage
            LoginPage{

            }
        }

        Component{
            id: signupPage
            SignupPage{

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
