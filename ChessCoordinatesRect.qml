import QtQuick 2.15

Rectangle {
    property string _cellCoordinatesText
//    id: _delegateAlphaCoord
//    height: _chessCellSize//_cellCoordinatesSize
//    width: _gameBoard._cellCoordinatesMargins//_chessCellSize
//    border.color: "red"
//    border.width: 1
    Text {
//        id: _flopaText
        anchors.centerIn: parent
        text: _cellCoordinatesText
//        font.family: "Helvetica [Cronyx]"
//        font.family: "Times"
        font.family: "Helvetica"

        font.pixelSize: 24
    }
}
