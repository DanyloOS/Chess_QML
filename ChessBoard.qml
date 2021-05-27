import QtQuick 2.15

Rectangle {

    property int boardSize
    property int cellSize: boardSize / 8
    property bool isBoardInverted: false

    width: boardSize
    height: boardSize

    GridView {
        id: _cells
//        z:30
        interactive: false
        width: boardSize
        height: boardSize
        cellWidth: cellSize
        cellHeight: cellSize
        model: chessBoardModel // parent.columns * parent.rows
        delegate: Rectangle {
//            x: cellSize * (index % 8)
//            y: cellSize * parseInt(index / 8)
//            z:100
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
            id: _piece
            isCoordinatesInverted: parent.isBoardInverted
            required property int pieceType
            required property int pieceColor
            required property int pieceCoordX
            required property int pieceCoordY
            coordX: pieceCoordX
            coordY: pieceCoordY

            width: cellSize
            height: cellSize
            x: cellSize * _coordX
            y: cellSize * _coordY
            z: pieceType === -1 ? -1 : 1

//            Component.onCompleted: {
////                        console.warn("warn completed")
////                        console.log("log completed")
////                        console.error("error completed")
////                        console.debug("debug completed")
////                        console.exception("exception completed")
////                        console.info("info completed")
//                    }

            source: "chess_pieces.png"
            sourceClipRect: Qt.rect(200 * pieceType, pieceColor * 200, 200, 200)

            Drag.active: _mouseArea.drag.active

            MouseArea {
                id: _mouseArea
                anchors.fill: parent
                anchors.margins: parent.width * 0.2
                drag.target: parent
//                visible: false

                onPressed: {
                    _piece.z++
                    _mouseAreaRect.visible = (pieceType === -1) ? false : true
                    _mouseAreaRect.opacityCoef = 0.3
                    console.log("cellSize:", cellSize,
                                "x:", _piece.x,
                                "xc:", _piece.x + _piece.width / 2,
                                "y:", _piece.y,
                                "yc:", _piece.y + _piece.width / 2,
                                "pieceType:", pieceType);
                    _piece.width = _piece.width * 1.3
                    _piece.height = _piece.height * 1.3
                }

                onReleased: {
                    _piece.z--
                    _mouseAreaRect.opacityCoef = 0
                    var xCenter = _piece.x + cellSize / 2
                    var yCenter = _piece.y + cellSize / 2
                    _piece.coordX = parseInt(xCenter / cellSize)
                    _piece.coordX = _piece._coordX
                    _piece.coordY = parseInt(yCenter / cellSize)
                    _piece.coordY = _piece._coordY
                    _piece.width = _piece.width / 1.3
                    _piece.height = _piece.height / 1.3

                    console.log("cellSize:", cellSize,
                                "x:", _piece.x,
                                "xc:", xCenter,
                                "y:", _piece.y,
                                "yc:", yCenter,
                                "pieceType:", pieceType)

                    console.log("lalala: pieceCoordY", pieceCoordY,
                                "pieceCoordX", pieceCoordX,
                                "_piece._coordY", _piece._coordY,
                                "_piece._coordX", _piece._coordX)
                    chessBoardModel.playerMakesMove(pieceCoordY, pieceCoordX,
                                              _piece.coordY, _piece.coordX)

                }
                Rectangle {
                    id: _mouseAreaRect
                    property real opacityCoef: 0.5
                    color: "darkblue"
                    anchors.fill: parent
                    width: cellSize
                    height: cellSize
                    opacity: opacityCoef
                    radius: width / 2
                    visible: false
                }
            }
        }
    }
}
