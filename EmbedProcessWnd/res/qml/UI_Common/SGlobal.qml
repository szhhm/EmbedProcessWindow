pragma Singleton
import QtQuick 2.9

QtObject{
    readonly property double vRatio: 1.0//mainView.verticalRatio;
    readonly property double hRatio: 1.0//mainView.horizontalRatio;
    readonly property double fontRatio: hRatio;

    property string styleName: "gray"
}
