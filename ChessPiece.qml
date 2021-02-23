import QtQuick 2.15

Image {
    property int coordX: 0
    property int coordY: 0
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
