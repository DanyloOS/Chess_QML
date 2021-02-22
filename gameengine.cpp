#include "gameengine.h"

GameEngine::GameEngine(const std::string &start_pos)
    : chessBoardModel(FEN::fromFENToBoard(start_pos))
{
}

ChessBoardModel& GameEngine::getChessBoardModel()
{
    return chessBoardModel;
}
