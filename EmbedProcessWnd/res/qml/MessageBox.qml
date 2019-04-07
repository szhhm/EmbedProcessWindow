import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "UI_Common"

Window {
    id:control
    color:"red"
    width:800
    height: 600
//    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    visible: false
    MouseArea{
        width:parent.width
        height: 40
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: clickPos = Qt.point(mouse.x, mouse.y)
        onPositionChanged: {
            //鼠标偏移量
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            control.setX(control.x + delta.x)
            control.setY(control.y + delta.y)
        }
    }

    Button{
        anchors.right: control.right
        width:80
        height: 40
        text:"关闭"
        onClicked: control.hide()
        z:1
    }

    Image{
        anchors.fill: parent
        source:"../images/" + Settings.styleName + "/1.png"
    }
    Image {
        id: aa
        x:100
        y:100
        width:300
        height: 300
        source: "../images/" + Settings.styleName + "/2.png"
    }
}
