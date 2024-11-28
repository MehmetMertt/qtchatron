import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

Item {
    id: signupPage

    signal switchToLogin

    function setError(reason) {
        errorMessage.visible = true
        errorMessage.text = reason
    }

    AuthModel{id: authModel;}

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
            text: "Signup"
            font.pixelSize: 36
            font.bold: true
            font.family: "Roboto"
            color: Material.foreground
            horizontalAlignment: Text.AlignVCenter
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
            text: qsTr("Signup")
            Layout.fillWidth: true
            font.pixelSize: 22
            //flat: true
            hoverEnabled: true
            Material.elevation: 0
            Material.roundedScale: Material.SmallScale
            Material.background: Material.primary

            contentItem: Text {
                text: qsTr("Signup")
                font.pixelSize: 22
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                authModel.signup()
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
            function onLoginSuccessful() {
                Router.setCurrentPage(2); // Navigate to Login
            }
            function onLoginFailed(reason) {
                signupPage.setError(reason)
            }
        }

        Text {
            text: "Login instead?"
            color: Material.primary
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Router.setCurrentPage(2)
                    //signupPage.switchToLogin()
                    console.log("Login instead clicked!")
                }
            }
        }
    }
}
