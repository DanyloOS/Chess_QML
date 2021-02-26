import QtQuick 2.15

Repeater {
    id: _repeaterNumCoord
    height: _chessBoardSize
    width: _cellCoordinatesSize

    property int _cellCoordinatesMargins
    property int _chessCellSize
    property int xoffset
    property int yoffset

    model: ListModel {
        ListElement {
            display: "1"
        }
        ListElement {
            display: "2"
        }
        ListElement {
            display: "3"
        }
        ListElement {
            display: "4"
        }
        ListElement {
            display: "5"
        }
        ListElement {
            display: "6"
        }
        ListElement {
            display: "7"
        }
        ListElement {
            display: "8"
        }
    }
    delegate: ChessCoordinatesRect {
        _cellCoordinatesText: display
        height: _chessCellSize//_cellCoordinatesSize
        width: _cellCoordinatesSize//_chessCellSize
        x: width + xoffset
        y: height * (_gameBoard.isBoardInverted ? index : 7 - index) + yoffset
    }
}
