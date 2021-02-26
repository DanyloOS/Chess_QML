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
            display: "a"
        }
        ListElement {
            display: "b"
        }
        ListElement {
            display: "c"
        }
        ListElement {
            display: "d"
        }
        ListElement {
            display: "e"
        }
        ListElement {
            display: "f"
        }
        ListElement {
            display: "g"
        }
        ListElement {
            display: "h"
        }
    }
    delegate: ChessCoordinatesRect {
        _cellCoordinatesText: display
        width: _chessCellSize//_cellCoordinatesSize
        height: _cellCoordinatesSize//_chessCellSize
        y: height + yoffset
        x: width * (!_gameBoard.isBoardInverted ? index : 7 - index) + xoffset
    }
}
