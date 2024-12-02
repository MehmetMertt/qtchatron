import QtQuick 6.8
import QtQuick.Controls 6.8

import Client 1.0

Page {
    id: loadingPage

    Timer {
        interval: 500  // Example delay for loading simulation
        running: true
        repeat: false
        onTriggered: {
            //console.log("set loading ready page")
            Router.setLoadingReady()  // Emit the signal when loading is done
        }
    }

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

        Text {
            text: "by GROUP TWENTY ONE"
            font.pixelSize: 14
            color: "#555555"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }
    }
}
