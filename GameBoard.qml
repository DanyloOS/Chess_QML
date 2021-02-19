import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
    id: _board

    property int boardSize: width > height ? height : width
    property int cellSize: boardSize / 8
    property bool isRotated: false

    Repeater {
        id: _cells
        model: chessBoardModel //parent.columns * parent.rows
        delegate: Rectangle {
            x: cellSize * (index % 8)
            y: cellSize * parseInt(index / 8)
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
        model: chessPieceModel
        delegate:  ChessPiece {
            required property int pieceType
            required property int pieceColor
            required property int pieceCoordX
            required property int pieceCoordY

            width: cellSize
            height: cellSize
            x: cellSize * pieceCoordX
            y: cellSize * (isRotated ? 7 - pieceCoordY : pieceCoordY)

            source: "chess_pieces.png"
            sourceClipRect: Qt.rect(200 * pieceType, pieceColor * 200, 200, 200)
        }
    }
}
