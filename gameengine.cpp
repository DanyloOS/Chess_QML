#include "gameengine.h"

GameEngine::GameEngine()
{
    for (int i = 0; i < 64; ++i)
        chessBoardModel.addCell( (i + i / 8) % 2 ? 1 : 0);
}

void GameEngine::setUpStartPos(const std::string& FEN_pos)
{
    QList <ChessPiece> piecesList;
    FEN::fromFENtoQList(FEN_pos, piecesList);
    chessPieceModel.setPieceList(piecesList);
}

ChessBoardModel& GameEngine::getChessBoardModel()
{
    return chessBoardModel;
}

ChessPieceModel& GameEngine::getChessPieceModel()
{
    return chessPieceModel;
}

