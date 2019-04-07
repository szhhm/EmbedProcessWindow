import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "UI_Common"

Rectangle {
    id: bottomBtnImg
    color: "#565656"
    ListModel{
        id:appModel
        Component.onCompleted: {
           appModel.append({'name':'360','icon':'1.png','displayName':'大酒店','type':1})
            appModel.append({'name':'360','icon':'2.png','displayName':'范德','type':2})
            appModel.append({'name':'360','icon':'2.png','displayName':'范德','type':6})
            appModel.append({'name':'360','icon':'2.png','displayName':'范德','type':4})
            appModel.append({'name':'360','icon':'3.png','displayName':'大幅度','type':3})
            appModel.append({'name':'360','icon':'3.png','displayName':'大幅度','type':1})
            appModel.append({'name':'360','icon':'3.png','displayName':'大幅度','type':5})
            appModel.append({'name':'360','icon':'3.png','displayName':'大幅度','type':2})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':6})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':2})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':5})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':7})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':4})
            appModel.append({'name':'360','icon':'4.png','displayName':'2位地方','type':1})
        }
    }

    GridView{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: item1.right
        anchors.leftMargin: 10
        cellHeight: 150
        cellWidth: 150
        clip:true
        model:appModel
        delegate: AppDelegate{
            height: 140
            width: 140
        }
    }

    Item {
        id: item1
        width: 33
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Text {
            id: text1
            color: "#c2ff66"
            text: qsTr("App")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Tahoma"
            font.pixelSize: 12
        }
    }
}

