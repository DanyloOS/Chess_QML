import QtQuick 2.15
import QtQuick.Window 2.12

Window {
    width: 640
    height: 640
    visible: true
    title: qsTr("Hello World")

    ChessBoard {
        anchors.fill: parent
    }
}
