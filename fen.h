#ifndef FEN_H
#define FEN_H


#include "chesspiece.h"

#include <QList>
#include <string.h>
#include <map>


class FEN
{
public:
    virtual ~FEN() = 0;
    static void fromFENtoQList (const std::string &FENpos, QList<ChessPiece> &curPiecesList);
    static void fromQListToFEN (const QList<ChessPiece> &curPiecesList, std::string FENpos);

private:
    static const std::map <char, PieceType_e> charToPieceType;
};

#endif // FEN_H
