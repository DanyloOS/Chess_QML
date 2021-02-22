#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include "chessboardmodel.h"
#include "fen.h"

#include <string>


#define CHESS_DEFAULT_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class GameEngine
{
public:
    GameEngine(const std::string &start_chess_fen_pos = CHESS_DEFAULT_FEN);
    void setUpStartPos(const std::string& FEN_pos);
    ChessBoardModel& getChessBoardModel();

private:
    ChessBoardModel chessBoardModel;
};

#endif // GAMEENGINE_H
