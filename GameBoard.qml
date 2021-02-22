import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
    id: _board

    property int boardSize: width > height ? height : width
    property int cellSize: boardSize / 8
    property bool isRotated: false

    ListView {
        id: _cells
        model: chessBoardModel //parent.columns * parent.rows
        anchors.fill: parent
        delegate: Rectangle {
//            x: cellSize * 1
//            y: cellSize * 1
            width: cellSize
            height: cellSize
            color: cellColor ? "#8b4513" : "#ffdead" //parseInt(index + index / 8) % 2  ? "#8b4513" : "#ffdead"
            border.width: 1
            border.color: "black"
        }
    }

    Repeater {
        anchors.fill: parent
        id: _pieces
        model: chessBoardModel
        delegate:  ChessPiece {
            required property int pieceType
            required property int pieceColor
//            required property int pieceCoordX
//            required property int pieceCoordY

            width: pieceType !== -1 ? cellSize : 0
            height: pieceType !== -1 ? cellSize : 0
//            x: cellSize * pieceCoordX
//            y: cellSize * (isRotated ? 7 - pieceCoordY : pieceCoordY)

            source: "chess_pieces.png"
            sourceClipRect: Qt.rect(200 * pieceType, pieceColor * 200, 200, 200)
        }
    }
}
