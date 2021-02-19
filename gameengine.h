#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include "chessboardmodel.h"
#include "chesspiecemodel.h"
#include "fen.h"

#include <string>


class GameEngine
{
public:
    GameEngine();
    void setUpStartPos(const std::string& FEN_pos);
    ChessBoardModel& getChessBoardModel();
    ChessPieceModel& getChessPieceModel();

private:
    ChessBoardModel chessBoardModel;
    ChessPieceModel chessPieceModel;
};

#endif // GAMEENGINE_H
