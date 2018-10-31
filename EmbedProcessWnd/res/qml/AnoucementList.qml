import QtQuick 2.9
import QtQuick.Controls 2.2

Item{
    id:root
    Image {
        id: image
        y: 0
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        source: "../images/windowContainerBg.png"

        ToolButton {
            id: toolButton
            x: 584
            y: 0
            width: 40
            height: 30
            text: qsTr("关闭")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: frontWorker.close();
        }
    }

    ListView{
        id:listView
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: image.bottom
        anchors.topMargin: 0
        model:frontWorker.anoucementMsgs();
        delegate:AnoucementDelegate{
        }
    }

}

