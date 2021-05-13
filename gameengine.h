#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include "chessboardmodel.h"
#include "fen.h"
#include "uciengine.h"


class GameEngine
{
public:
    GameEngine(const QString &start_chess_fen_pos = CHESS_DEFAULT_FEN);
    void setUpStartPos(const QString& FEN_pos);
    ChessBoardModel& getChessBoardModel();

private:
    ChessBoardModel chessBoardModel;
//    UciEngine engine;
};

#endif // GAMEENGINE_H
