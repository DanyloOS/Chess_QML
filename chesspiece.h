#ifndef CHESSPIECE_H
#define CHESSPIECE_H


enum class PieceType_e {
    King = 0,
    Queen,
    Bishop,
    Knight,
    Rock,
    Pawn
};

enum class PieceColor_e {
    White = 0,
    Black
};

struct Coordinates {
    unsigned x;
    unsigned y;
};

class ChessPiece
{
public:
    ChessPiece(PieceType_e pieceType, PieceColor_e pieceColor,
        Coordinates pieceCoordinates);
    PieceType_e getType() const;
    PieceColor_e getColor() const;
    unsigned getCoordX() const;
    unsigned getCoordY() const;

private:
    PieceType_e type;
    PieceColor_e color;
    Coordinates coordinates;
};

#endif // CHESSPIECE_H
