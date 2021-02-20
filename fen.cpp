#include "fen.h"

const std::map <char, PieceType_e> FEN::charToPieceType {
    {'r', PieceType_e::Rock},
    {'n', PieceType_e::Knight},
    {'b', PieceType_e::Bishop},
    {'q', PieceType_e::Queen},
    {'k', PieceType_e::King},
    {'p', PieceType_e::Pawn}
};

void FEN::fromFENtoQList(const std::string &FENpos, QList <ChessPiece> &curPiecesList)
{
    unsigned curCoordX = 0;
    unsigned curCoordY = 0;
    PieceColor_e curColor;
    PieceType_e curType;

    curPiecesList.clear();

    for (char curChar : FENpos)
    {
        if (curCoordY == 7 && curChar == ' ')
            break;

        if (isdigit(curChar))
        {
            curCoordX = (curCoordX + (curChar - '0')) % 8;
        }
        else if (isalpha(curChar))
        {
            curColor = isupper(curChar) ? PieceColor_e::White : PieceColor_e::Black;
            curType = charToPieceType.at(tolower(curChar));
            curPiecesList << ChessPiece({curType, curColor, {curCoordX, curCoordY}});
            curCoordX = (curCoordX + 1) %  8;
        }
        else if (curChar == '/')
        {
            curCoordX = 0;
            ++curCoordY;
        }
        else
        {
            // TODO: throw BadFENpos exception
        }
    }
}

void FEN::fromQListToFEN(const QList <ChessPiece> &curPiecesList, std::string fenPos)
{
// TODO: implement converting QList <ChessPiece> to FEN
    Q_UNUSED(curPiecesList);
    Q_UNUSED(fenPos);
}
