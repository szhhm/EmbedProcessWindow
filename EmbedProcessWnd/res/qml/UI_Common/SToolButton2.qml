import QtQuick 2.9
import QtQuick.Controls 2.2

ToolButton
{
    id:control
    background: Rectangle {
        anchors.fill: parent
        border.width: control.pressed ? 2 : 1
        border.color: control.hovered ? control.pressed ? "#ffbfff" : "#acd6ff" : "transparent"
        radius: 2
//        gradient: Gradient {
//            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
//            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
//        }
        color: control.hovered ? control.pressed ? "#66b3ff" : "#80ffff" : "transparent"
    }
    ToolTip.visible: control.hovered
}

