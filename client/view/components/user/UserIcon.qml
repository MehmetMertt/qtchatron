import QtQuick 2.15
import QtQuick.Controls.Material 2.15


Rectangle {
    id: userIcon

    property var initial: "P"
    property double scaleI: 1

    width: 40
    height: 40
    radius: width / 2
    color: Material.Grey

    // Profile initials or icon
    Text {
        id: initialText
        text: userIcon.initial // Placeholder for profile initial or icon
        color: "white"
        font.pixelSize: 24 * userIcon.scaleI
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        // Fine-tune the centering with explicit offsets if needed
        anchors.verticalCenterOffset: -2 // Adjust for subtle visual offsets
    }
}
