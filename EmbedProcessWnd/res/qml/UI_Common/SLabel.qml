import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle{
    color: "red"
//    RowLayout{
//        anchors.fill: parent
        Text{
            text: "这个手动阀抖擞了放假了"
            x:0
            y:0
            font.pixelSize: 13
        }

        Button
        {
            id:sLabel
            x:100
            y:0
            width:200 * mainView.horizontalRatio
            height: 26 * mainView.verticalRatio
            text: "类型"
            tooltip: "我的标签"
            onWidthChanged: console.log("sLabel.width: " + width)
            onHeightChanged: console.log("sLabel.height: " + height)
        }
//    }
}
