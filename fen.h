#ifndef FEN_H
#define FEN_H


#include <QtCore>
#include <string>
#include <map>

#include "chessboard.h"


class FEN
{
public:
    virtual ~FEN() = 0;
    static ChessBoard fromFENToBoard(const std::string &FENpos);
    static void fromBoardToFEN (const ChessBoard &curPiecesBoard, std::string &FENpos);

private:
    static const std::map <char, PieceType_e> charToPieceType;
};

#endif // FEN_H
