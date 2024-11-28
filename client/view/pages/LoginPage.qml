import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: loginPage


    Rectangle {
        anchors.fill: parent
        color: "white" // Background color
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
            color: "#333333"
            horizontalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // Username Field
        TextField {
            id: usernameField
            placeholderText: "Username"
            topPadding: 10
            bottomPadding: 10
            font.pixelSize: 18
            Layout.fillWidth: true
            background: Rectangle {
                color: "#f7f7f7" // Light gray background
                border.color: "#cccccc"
                radius: 5
            }
        }

        // Password Field
        TextField {
            id: passwordField
            placeholderText: "Password"
            topPadding: 10
            bottomPadding: 10
            echoMode: TextInput.Password
            font.pixelSize: 18
            Layout.fillWidth: true
            background: Rectangle {
                color: "#f7f7f7" // Light gray background
                border.color: "#cccccc"
                radius: 5
            }
        }

        Button {
            id: loginButton
            text: qsTr("Login")
            Layout.fillWidth: true
            font.pixelSize: 22
            flat: true
            hoverEnabled: true


            background: Rectangle {
                id: buttonBackground
                color: loginButton.hovered ? "#00A6E0" : "white"
                radius: 5
                border.color: "#00A6E0"
                border.width: 1
            }

            contentItem: Text {
                text: qsTr("Login")
                font.pixelSize: 22
                color: loginButton.hovered ? "white" : "#00A6E0"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                //AuthController.login()
            }
        }

        // Forgot Password
        Text {
            text: "Forgot Password?"
            color: "#00A6E0"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: console.log("Forgot Password clicked!")
            }
        }

        Text {
            text: "Signup instead?"
            color: "#00A6E0"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: console.log("Signup instead clicked!")
            }
        }
    }
}
