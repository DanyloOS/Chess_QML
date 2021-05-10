#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QMap>
#include <QMetaEnum>
#include <QtGlobal>
#include <QQmlEngine>

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

//class PieceColor_e : public QObject {
//public:
//    PieceColor_e() : QObject() {}

//    enum Color {
//        None = -1,
//        White,
//        Black
//    };
//    Q_ENUM(Color);
//    static void declareQML() {
//        qmlRegisterType<PieceColor_e>("PieceColor_e", 1, 0, "PieceColor");
//    }
//};

class ChessPiece
{
public:
    ChessPiece(PieceType_e pieceType = PieceType_e::None,
               PieceColor_e pieceColor = PieceColor_e::None);

    PieceType_e type() const;
    PieceColor_e color() const;

    static QString typeToStr(PieceType_e type);
private:
    PieceType_e m_type;
    PieceColor_e m_color;
};

#endif // CHESSPIECE_H
