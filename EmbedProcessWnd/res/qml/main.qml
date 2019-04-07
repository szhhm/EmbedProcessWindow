import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
//import QtQuick.Dialogs 1.2

import "UI_Common" as UiCommon
import "UI_Common"

Rectangle {
    id: root
    implicitWidth: 1024 * Settings.hRatio
    implicitHeight: 768 * Settings.vRatio
    visible: true

    property var messageBox: MessageBox{}
    Component{
        id:centerComponent
        Image {
            id: embedWndContainer
            anchors.fill: parent
            objectName: "WndContainerRect"
            fillMode: Image.Stretch
            source: "../images/2.jpg"
            //        ComboBox {
            //              currentIndex: 2
            //              model: ListModel {
            //                  id: cbItems
            //                  ListElement { text: "Banana"; color: "Yellow" }
            //                  ListElement { text: "Apple"; color: "Green" }
            //                  ListElement { text: "Coconut"; color: "Brown" }
            //              }
            //              width: 200
            //              onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).text + ", " + cbItems.get(currentIndex).color)
            //          }
        }
    }

    Dialog {
        id: dialog
        x: 100
        y: 100
        width: 200
        height: 300
        modal: true
        focus: true
        standardButtons: Dialog.Ok
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
    Image {
        id: bottomBtnImg
        y: 353 * Settings.vRatio
        //        width: root.width
        height: 50 * Settings.vRatio
        anchors.right: anoucement.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -3
        source: "../images/windowContainerBg.png"

        RowLayout {
            id: bottomRow
            width:parent.width
            height: parent.height

            ToolButton {
                id: embedBtn
                text: "吸附进程窗口"
                //: "吸附进程窗口"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    loader.sourceComponent = centerComponent
                    wndContainer.EmbedProcessWindow("WpfApplication2.exe",
                                                    loader.x,
                                                    loader.y,
                                                    loader.width,
                                                    loader.height)
                    //                    frontWorker.embededWindow();
                }
            }
        }
    }

    Image {
        id: topBtnImg
        width: root.width
        height: 30 * Settings.vRatio
        source: "../images/windowContainerBg.png"

        RowLayout {
            id: flowBtn
            width:400
            height: parent.height
            anchors.right: parent.right
            spacing: 1 * Settings.hRatio
            layoutDirection: Qt.LeftToRight
            //            UiCommon.SLabel{
            //                height: 30 * mainView.verticalRatio
            //                width:200 * mainView.horizontalRatio
            ////                text: "类型"
            ////                tooltip: "我的标签"
            //                anchors.verticalCenter: parent.verticalCenter
            //                anchors.left: parent.left
            //                anchors.leftMargin: 0
            //                onWidthChanged: console.log("width: " + width)
            //                onHeightChanged: console.log("height: " + height)
            //            }

            //            UiCommon.SComboBox {
            //                width: 200
            //                height: 26
            //                anchors.verticalCenter: parent.verticalCenter
            //                model: 100
            //                onAccepted: {
            //                    //                  if (find(editText) === -1)
            //                    //                      model.append({text: editText})
            //                }
            //                onCurrentIndexChanged: console.debug("currentIndex: " + currentIndex)
            //            }

            //            UiCommon.SToolButton{
            //                id:openBtn
            //                text:"打开"
            //                height: 26
            //            }

            //            UiCommon.STextArea{
            //                id:descript
            //                text:"这是一个描述"
            //            }
            //            UiCommon.SCycleScrollText{
            //                id:cycleScrollText
            //                property int index: 0
            //                property var myTexts: ["你好这记录卡士大夫经理刷卡了的房间里是大家分开了","撒旦法撒的发链接快乐撒娇了圣诞节了开发的时间里开发及","dflsadfsdfsldflkjfld解放路的世界疯了沙发点开链接阿萨德飞机了撒娇地方了沙拉酱豆腐"]

            //                width: 453
            //                height: 30
            //                curText:"尽快咯大姐夫上了对方监考老师地方"
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                onTextScrollFinished: {
            //                    ++index;
            //                    if(index < myTexts.length)
            //                        curText = myTexts[index];
            //                    else
            //                        curText = "";
            //                }
            //            }

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ToolButton {
                id: gridViewBtn
                //                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "GridView"
                anchors.verticalCenter: parent.verticalCenter
                onClicked:
                {
                    loader.source = "UI_Common/SGridView.qml"
                }
            }

            SToolButton2 {
                id: mainBtn
                width: 16
                Layout.fillHeight: true
                text: "主页"
                anchors.verticalCenter: parent.verticalCenter
                ToolTip.text: "主页"
                onClicked:loader.source = "AppManager.qml"
            }
            SToolButton2 {
                id: minBtn
                //                Layout.fillWidth: true
                width: 16
                Layout.fillHeight: true
                text: "最小化"
                anchors.verticalCenter: parent.verticalCenter
                ToolTip.text: "最小化"
                onClicked:mainView.showMinimized()
            }
            SToolButton2 {
                id: maxBtn
                width: 16
                Layout.fillHeight: true
                text: "最大化"
                anchors.verticalCenter: parent.verticalCenter
                ToolTip.text: "最大化"
//                onClicked:mainView.showMaximized()
                onClicked: messageBox.show()
            }
            SToolButton2 {
                id: normalBtn
                width: 16
                Layout.fillHeight: true
                text: "常规"
                anchors.verticalCenter: parent.verticalCenter
                ToolTip.text: "常规"
                //                onClicked:mainView.showNormal()
                onClicked: {
                    console.log("styleName,", Settings.styleName)
                    Settings.styleName = "gray" === Settings.styleName ? "blue" : "gray"
                    console.log("styleName,", Settings.styleName)
                }
            }
            SToolButton2 {
                id: closeBtn
                width: 16
                Layout.fillHeight: true
                text: "关闭"
                anchors.verticalCenter: parent.verticalCenter
                ToolTip.text: "关闭"
                onClicked:
                {
                    //                    dialog.open()
                    mainView.close()
                    wndContainer.close()
                }
            }
        }
    }
    AnoucementList{
        id:anoucement
        anchors.right: parent.right
        anchors.top: topBtnImg.bottom
        width: 200
        height: root.height
    }

    Loader{
        id:loader
        anchors.right: anoucement.left
        anchors.rightMargin: 1 * Settings.hRatio
        anchors.left: parent.left
        anchors.leftMargin: 1 * Settings.hRatio
        anchors.bottom: bottomBtnImg.top
        anchors.bottomMargin: 1 * Settings.vRatio
        anchors.top: topBtnImg.bottom
        anchors.topMargin: 1 * Settings.vRatio
        sourceComponent: centerComponent
    }
    Component.onCompleted: loader.source = "AppManager.qml"
}

