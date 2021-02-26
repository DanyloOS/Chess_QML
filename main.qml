import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 640
    title: qsTr("GNU Chess")

    GameBoard {
        anchors.centerIn: parent
        property int boardSize: Math.min(parent.width, parent.height)
        width: boardSize
        height: boardSize
        anchors.margins: 20
    }
}
