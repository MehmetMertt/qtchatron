import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.15

import Client 1.0

Item {
    id: signupPage

    signal switchToLogin




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

        }

        // Password Field
        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            font.pixelSize: 18
            Layout.fillWidth: true
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


/*
            background: Rectangle {
                id: buttonBackground
                color: loginButton.hovered ? "#00A6E0" : "white"
                radius: 5
                border.color: "#00A6E0"
                border.width: 1
            }
*/
            contentItem: Text {
                text: qsTr("Signup")
                font.pixelSize: 22
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                //AuthController.login()
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
