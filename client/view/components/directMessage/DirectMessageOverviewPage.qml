import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import Client 1.0

pragma ComponentBehavior: Bound

Item {
    id: dmOverviewPage

    property list<User> userDmList: SessionUser.dmList

    Rectangle {
        anchors.fill: parent
        color: "#252328"

        ScrollView {
            id: dmScrollView
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
                model: dmOverviewPage.userDmList

                delegate: Item {
                    id: listItem
                    required property var index
                    width: parent.width  // Ensure it matches ListView width
                    height: 60  // Adjust according to your item size

                    ColumnLayout {
                      anchors.fill: parent  // Fill the entire delegate area
                      spacing: 5

                      DirectMessageListItem {
                          user: dmList.model[listItem.index]
                          Layout.preferredWidth: parent.width - parent.width/10  // Expand to use full width
                          Layout.preferredHeight: 50  // Adjust according to content
                      }

                      Rectangle {
                          color: Material.background  // Separator color
                          Layout.preferredHeight: 1
                          Layout.preferredWidth: parent.width - parent.width/10  // Use the full width
                          visible: (listItem.index !== dmList.count - 1)  // Hide separator for the last item
                      }
                    }
                    }

            }

        }
    }
}
