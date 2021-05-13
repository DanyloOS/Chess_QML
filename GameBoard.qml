import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
    id: _gameBoard

    property int _cellCoordinatesSize: 40
    property int _cellCoordinatesMargins: _cellCoordinatesSize * 2
    property int _chessBoardSize: _rectChessBoard.width
    property int _chessCellSize: _chessBoardSize / 8
    property bool isBoardInverted: true
    z: -1
    Rectangle {
        id: _rectChessBoard
        width: Math.min(parent.width, parent.height)
        height: Math.min(parent.width, parent.height)
        anchors.fill: parent
        anchors.margins: _cellCoordinatesMargins
        ChessBoard {
            id: _chessBoard
            boardSize: Math.min(parent.width, parent.height)
            isBoardInverted: _gameBoard.isBoardInverted
        }
    }


    ChessNumCoordinates {
        _cellCoordinatesMargins: _gameBoard._cellCoordinatesMargins
        _chessCellSize: _gameBoard._chessCellSize
        xoffset: 0
        yoffset: _cellCoordinatesMargins
    }

    ChessNumCoordinates {
        _cellCoordinatesMargins: _gameBoard._cellCoordinatesMargins
        _chessCellSize: _gameBoard._chessCellSize
        xoffset: _gameBoard.width - (_gameBoard.width - _gameBoard._chessBoardSize + _cellCoordinatesMargins) / 2
        yoffset: _cellCoordinatesMargins
    }

    ChessAlphaCoordinates {
        _cellCoordinatesMargins: _gameBoard._cellCoordinatesMargins
        _chessCellSize: _gameBoard._chessCellSize
        xoffset: _cellCoordinatesMargins
        yoffset: 0
    }

    ChessAlphaCoordinates {
        _cellCoordinatesMargins: _gameBoard._cellCoordinatesMargins
        _chessCellSize: _gameBoard._chessCellSize
        xoffset: _cellCoordinatesMargins
        yoffset: _gameBoard.width - (_gameBoard.width - _gameBoard._chessBoardSize + _cellCoordinatesMargins) / 2
    }

//    Connections {
//        target: chessBoardModel
//        function onWinnerChanged(pieceColor) {
//            console.log("Hello")
//            console.log(pieceColor)
//        }
//    }
}
