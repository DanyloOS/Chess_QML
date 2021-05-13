#ifndef FEN_H
#define FEN_H

#include <QtCore>
#include <string>
#include <map>

#include "chessboard.h"

#define CHESS_DEFAULT_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class FEN
{
public:
    virtual ~FEN() = 0;
    static ChessBoard fromFENToBoard(const QString &FENpos);
    static QString fromBoardToFEN(const ChessBoard &curPiecesBoard);

private:
    static const QMap <QChar, PieceType_e> charToPieceType;
    static const QMap <PieceType_e, QChar> pieceTypeToChar;
};

#endif // FEN_H
