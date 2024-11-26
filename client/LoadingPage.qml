import QtQuick 6.8
import QtQuick.Controls 6.8

Page {
    id: loadingPage
    signal loadingFinished

    Rectangle {
        id: loadingPageBackground
        anchors.fill: parent
        color: "white"

        Column {
            anchors.centerIn: parent
            spacing: 12  // Space between the header and subheader

            Text {
                text: "Welcome to QChatron"
                font.pixelSize: 36
                font.bold: true
                font.family: "Roboto"
                color: "#333333"
                anchors.horizontalCenter: parent.horizontalCenter  // Center horizontally
            }

            Text {
                text: "Loading..."
                font.pixelSize: 18      // Smaller font for the subheader
                color: "#555555"        // Lighter gray for subtlety
                anchors.horizontalCenter: parent.horizontalCenter  // Center horizontally
            }
        }


        // Simulate loading (trigger in C++ backend for real tasks)
        Timer {
            interval: 3000  // 3 seconds for demo
            running: true
            repeat: false
            onTriggered: loadingPage.loadingFinished()
        }
    }
}
