#include "fen.h"

const QMap <QChar, PieceType_e> FEN::charToPieceType {
    {'r', PieceType_e::Rock},
    {'n', PieceType_e::Knight},
    {'b', PieceType_e::Bishop},
    {'q', PieceType_e::Queen},
    {'k', PieceType_e::King},
    {'p', PieceType_e::Pawn}
};

const QMap <PieceType_e, QChar> FEN::pieceTypeToChar {
    {PieceType_e::Rock,   'r'},
    {PieceType_e::Knight, 'n'},
    {PieceType_e::Bishop, 'b'},
    {PieceType_e::Queen,  'q'},
    {PieceType_e::King,   'k'},
    {PieceType_e::Pawn,   'p'}
};

ChessBoard FEN::fromFENToBoard(const QString &FENpos)
{
    unsigned curCoordX = 0;
    unsigned curCoordY = 0;
    PieceColor_e curColor;
    PieceType_e curType;
    ChessBoard pieceBoard;

    for (QChar curChar : FENpos)
    {
        if (curCoordY == 7 && curChar == ' ')
            break;

        if (curChar.isDigit())//isdigit(curChar))
        {
            curCoordX = (curCoordX + (QString(curChar).toInt())) % 8;
        }
        else if (curChar.isLetter())//isalpha(curChar))
        {
            curColor = curChar.isUpper() ? PieceColor_e::White : PieceColor_e::Black;
            curType = charToPieceType[curChar.toLower()];
//            curPiecesList << ChessPiece({curType, curColor, {curCoordX, curCoordY}});
            pieceBoard[curCoordY][curCoordX].setPiece({curType, curColor});
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

    return pieceBoard;
}

QString FEN::fromBoardToFEN(const ChessBoard &curPieceBoard)
{
    Q_UNUSED(curPieceBoard);

    QString FEN;

    int emptyCounter = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (curPieceBoard.at(i, j).piece().type() == PieceType_e::None)
            {
                ++emptyCounter;
                continue;
            }
            if (emptyCounter)
            {
                FEN.append(QString::number(emptyCounter));
                emptyCounter = 0;
            }

            QChar curPiece = pieceTypeToChar[curPieceBoard.at(i, j).piece().type()];
            if (curPieceBoard.at(i, j).piece().color() == PieceColor_e::White)
                curPiece = curPiece.toUpper();

            FEN.append(curPiece);
        }
        if (emptyCounter)
            FEN.append(QString::number(emptyCounter));
        FEN.append('/');
        emptyCounter = 0;
    }
    FEN.remove(FEN.length() - 1, 1);
    return FEN;
}
