#include "chesspiece.h"

ChessPiece::ChessPiece(PieceType_e pieceType, PieceColor_e pieceColor)
    : m_type(pieceType), m_color(pieceColor)
{}

PieceType_e ChessPiece::type() const
{
    return m_type;
}

PieceColor_e ChessPiece::color() const
{
    return m_color;
}
