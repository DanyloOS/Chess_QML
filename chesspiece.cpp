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

QString ChessPiece::typeToStr(PieceType_e type)
{
    static const QMap <PieceType_e, QString> ptostr {
        {PieceType_e::King, "k"},
        {PieceType_e::Queen, "q"},
        {PieceType_e::Bishop, "b"},
        {PieceType_e::Knight, "n"},
        {PieceType_e::Rock, "r"},
        {PieceType_e::Pawn, "p"}
    };

    return ptostr[type];
}
