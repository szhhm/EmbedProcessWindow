import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ComboBox
{
    id:sComboBox
    style:ComboBoxStyle{
        id:sComboBoxStyle
        label:Label{
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:currentText
            font.pixelSize: 14
        }

        __popupStyle:MenuStyle{
            property int __maxPopupHeight: 400
            property int submenuOverlap: 0
            property int submenuPopupDelay: 100

            property Component frame: Rectangle{
                id:popupFrame
                border.color: "white"
                Text{
                    text:"未实现"
                    color:"red"
                    font{
                        pixelSize: 10
                        bold: true
                    }
                    anchors.centerIn: parent
                    rotation: -Math.atan2(popupFrame.height, popupFrame.width)*180/Math.PI
                }
            }

            itemDelegate.background: Rectangle{
                color:styleData.selected? "red":"white"
            }
            property  Component menuItemPanel: Text {
                text: styleData.text
            }
            property Component __scrollerStyle: null
        }

        __dropDownStyle:MenuStyle{
            __maxPopupHeight:600
            __menuItemType:"comboboxitem"
            frame:Rectangle{
                color: "transparent"
                border.width: 1
                border.color: "red"
            }
            itemDelegate.label: Label{
                x:(sComboBox.width - width-10)>>1
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 13
                color: styleData.selected?"red":"#333333"
                text:styleData.text
            }
            itemDelegate.background: Rectangle{
                color:styleData.selected?"blue":"white"
            }
            scrollIndicator:Image{
//                anchors.centerIn: parent
                source:styleData.scrollDirection === Qt.UpArrow?"../../images/up_Arror.png":"../../images/down_Arror.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}

