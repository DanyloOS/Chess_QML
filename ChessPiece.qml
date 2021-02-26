import QtQuick 2.15

Image {
    property bool isCoordinatesInverted: false
    property int coordX: 0
    property int coordY: 0
    readonly property int _coordX: isCoordinatesInverted ? 7 - coordX: coordX
    readonly property int _coordY: isCoordinatesInverted ? 7 - coordY: coordY
    property int pieceType: 0
    property bool pieceColor: ChessPiece.PieceColor_e.Black

    enum PieceType_e {
        King = 0,
        Queen,
        Bishop,
        Knight,
        Rock,
        Pawn
    }

    enum PieceColor_e {
        White = 0,
        Black
    }

//    source: "chess_pieces.png"
//    sourceClipRect: Qt.rect(200 * pieceType, pieceColor * 200, 200, 200)
}
