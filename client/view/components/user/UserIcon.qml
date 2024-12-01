import QtQuick 2.15
import QtQuick.Controls.Material 2.15


Rectangle {
    id: userIcon

    property var initial: "P"

    width: 45
    height: 45
    radius: width / 2
    color: Material.Grey

    // Profile initials or icon
    Text {
        id: initialText
        text: userIcon.initial // Placeholder for profile initial or icon
        color: "white"
        font.pixelSize: 24
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        // Fine-tune the centering with explicit offsets if needed
        anchors.verticalCenterOffset: -2 // Adjust for subtle visual offsets
    }
}
