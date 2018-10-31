import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import "UI_Common"

Rectangle {
    id:root
    property var colors: ["#815bff", "#ff77ff","#4dffff","#66b3ff","#ff8040","#e1e100","#9999cc","#b766ad"]
    color:ma.containsMouse ? Qt.darker(colors[type]) : colors[type]
    radius: 8
    border.width: 1
    border.color: /*ma.containsMouse ? Qt.lighter(colors[type]) :*/ colors[type]

    ColumnLayout {
        id: columnLayout
        anchors.fill:parent

        Label {
            id: label1
            height: 12
            text: displayName
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
        Image{
            Layout.preferredHeight: 40
            Layout.preferredWidth: 40
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            fillMode: Image.Stretch
            source: "../images/"+icon
        }
        Label {
            id: label
            height: 12
            text: name
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }
    MouseArea{
        id:ma
        hoverEnabled: true
        anchors.fill: parent
    }

}

