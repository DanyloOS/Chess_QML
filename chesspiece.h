#ifndef CHESSPIECE_H
#define CHESSPIECE_H


enum class PieceType_e {
    None = -1,
    King,
    Queen,
    Bishop,
    Knight,
    Rock,
    Pawn
};

enum class PieceColor_e {
    None = -1,
    White,
    Black
};


class ChessPiece
{
public:
    ChessPiece(PieceType_e pieceType = PieceType_e::None,
               PieceColor_e pieceColor = PieceColor_e::None);

    PieceType_e type() const;
    PieceColor_e color() const;

private:
    PieceType_e m_type;
    PieceColor_e m_color;
};

#endif // CHESSPIECE_H
