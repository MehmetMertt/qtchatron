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
        console.log(mainStack.currentItem)
    }

    ClientController {
        id: clientController

        onClientReady: {
            //mainStack.push(mainPage)
        }
    }

    Connections {
        target: Router
        function onCurrentPageChanged() {
            console.log(Router.currentPage)
            root.setCurrentPage(Router.currentPage)
        }
    }

    /*Router{
        onCurrentPageChanged: () => {
            console.log(router.currentPage)
        }
    }*/


    function setCurrentPage(c_page_index) {
        let pageToShow;

        if (c_page_index === 1) {
            pageToShow = mainPage;
        } else if (c_page_index === 2) {
            pageToShow = loginPage;
        } else {
            pageToShow = signupPage;
        }

        // Check if the page is already on the stack
        let existingPage = mainStack.find(item => item === pageToShow, StackView.FirstToLast);

        if (existingPage) {
            // The page is already on the stack, pop to it
            mainStack.pop(mainStack.indexOf(existingPage) - mainStack.depth + 1);
        } else {
            // Page is not in the stack, push it
            mainStack.push(pageToShow);
        }
    }


    StackView {
        id: mainStack
        anchors.fill: parent
        visible: true

        initialItem: loginPage


    }

    Component{
        id:signupPage;
        SignupPage{

            //onSwitchToLogin: root.mainStack.pop()
        }
    }

    Component {
        id: mainPage
        MainPage {

        }
    }
    Component {
        id:loginPage;
        LoginPage{

            //onSwitchToSignup: mainStack.push(signupPage)
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
