#include "chesspiece.h"

ChessPiece::ChessPiece(PieceType_e pieceType, PieceColor_e pieceColor, Coordinates pieceCoordinates)
    : type(pieceType), color(pieceColor), coordinates(pieceCoordinates)
{}

PieceType_e ChessPiece::getType() const
{
    return type;
}

PieceColor_e ChessPiece::getColor() const
{
    return color;
}

unsigned ChessPiece::getCoordX() const
{
    return coordinates.x;
}

unsigned ChessPiece::getCoordY() const
{
    return coordinates.y;
}
