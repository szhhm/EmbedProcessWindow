import QtQuick 2.9

Rectangle {
    id: lamp
    property string curText: ""
    signal textScrollFinished()

    visible: "" !== curText
    height: 40
    color:"#585858"
    clip: true


    Text {
        id: cycleScrollText
        x:lamp.width
        height:lamp.height
        text: curText
        color:"#C8C8C8"
        font.family: "黑体"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12

        onTextChanged: {
            //首先计算文字的长度
//            var textLength = frontWorker.computeTextWidth(curText, "黑体", 12);
            //计算控件位置，设置控件的长度
            cycleScrollText.x = lamp.width
        }

        MouseArea{
            id:ma
            hoverEnabled: true
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 13
        height: 40
        color: "#373737"
    }

    Timer{
        id:timer
        running: "" !== cycleScrollText.text && !ma.containsMouse;
        repeat: true;
        interval: 20
        onTriggered: {
            if(-cycleScrollText.width < cycleScrollText.x)
                --cycleScrollText.x;
            else{
                cycleScrollText.x = lamp.width
                lamp.textScrollFinished();
            }
        }
    }

    Rectangle {
        id: rectangle1
        x: 584
        y: 0
        width: 13
        height: 40
        color: "#373737"
        anchors.right: parent.right
        anchors.rightMargin: 0
    }
}
