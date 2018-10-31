import QtQuick 2.0

Rectangle{
    id:delegeteView
    width: 200
    height: 40
    color:ma.containsMouse?"lightblue":"green"
    Text {
        width: 60
        height: 40
        text: qsTr("消息内容")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Text{
        id: msgContentText
        x: 66
        y: 0
        width: 134
        height: 40
        text:msgContent;
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea{
        id:ma
        anchors.fill: parent
        z:20
        onClicked: {
            console.log("index: " + index);
            delegeteView.ListView.currentIndex = index;
//            delegeteView.color = "#22222222";
        }
        onEntered: delegeteView.color = "#11111111";
        onExited: delegeteView.color = "#33333333";
        onPressed: delegeteView.color = "#44444444";
        onReleased: delegeteView.color = "green";

    }

}
