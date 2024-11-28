import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

Page {
    id: loginPage
    title: "Login"

    AuthModel{id: authModel}

    function setError(reason) {
        errorMessage.visible = true
        errorMessage.text = reason
    }

    Rectangle {
        anchors.fill: parent
        color: Material.background // Background color
    }

    ColumnLayout {
        id: formLayout
        anchors.centerIn: parent
        spacing: 20
        width: parent.width * 0.25


        // Title
        Text {
            text: "Login"
            font.pixelSize: 36
            font.bold: true
            font.family: "Roboto"
            color: Material.foreground
            Layout.alignment: Qt.AlignHCenter
        }

        // Username Field
        TextField {
            id: usernameField
            placeholderText: "Username"
            font.pixelSize: 18
            Layout.fillWidth: true
            text: authModel.username
            onTextChanged: authModel.username = text
        }

        // Password Field
        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            font.pixelSize: 18
            Layout.fillWidth: true
            text: authModel.password
            onTextChanged: authModel.password = text
        }

        Button {
            id: signupButton
            text: qsTr("Login")
            Layout.fillWidth: true
            font.pixelSize: 22
            //flat: true
            hoverEnabled: true
            Material.elevation: 0
            Material.roundedScale: Material.SmallScale
            Material.background: Material.primary

            contentItem: Text {
                text: qsTr("Login")
                font.pixelSize: 22
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                authModel.login()
            }
        }

        // Error Handling
        Text {
            id: errorMessage
            visible: false
            color: "red"
            font.pixelSize: 14
            Layout.alignment: Qt.AlignHCenter
        }

        Connections {
            target: authModel
            function onAuthMethodSuccessful() {
                console.log("Login successful!");
                Router.setCurrentPage(1); // Navigate to MainPage
            }
            function onAuthMethodFailed (reason) {
                loginPage.setError(reason)
            }
        }

        Text {
            text: "Forgot password?"
            color: Material.primary
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: console.log("Forgot password clicked!")
            }
        }

        Text {
            text: "Signup instead?"
            color: Material.primary
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Router.setCurrentPage(3)
                    console.log("Signup instead clicked!")
                }
            }
        }
    }
}
