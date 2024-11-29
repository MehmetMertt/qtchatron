import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
    id: dmOverviewPage

    Rectangle {
        anchors.fill: parent
        color: "#252328"

        ScrollView {
            id: dmScrolLView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.fill: parent

            anchors.topMargin: 20
            anchors.leftMargin: 40


            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AsNeeded


            ListView {
                id: dmList

                anchors.left: parent.left


                spacing: 10
                model: ListModel {
                    ListElement { name: "Flo" }
                    ListElement { name: "Mehmet" }
                    ListElement { name: "Michi" }
                    ListElement { name: "Martin" }
                    // Add more channels as needed
                }

                delegate: Item {
                    width: parent.width  // Ensure it matches ListView width
                    height: 60  // Adjust according to your item size

                    ColumnLayout {
                      anchors.fill: parent  // Fill the entire delegate area
                      spacing: 5

                      DirectMessageListItem {
                          Layout.preferredWidth: parent.width - parent.width/10  // Expand to use full width
                          Layout.preferredHeight: 50  // Adjust according to content
                      }

                      Rectangle {
                          color: Material.background  // Separator color
                          Layout.preferredHeight: 1
                          Layout.preferredWidth: parent.width - parent.width/10  // Use the full width
                          visible: (index !== dmList.count - 1)  // Hide separator for the last item
                      }
                    }
                    }

            }

        }
    }
}
