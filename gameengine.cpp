#include "gameengine.h"

GameEngine::GameEngine(const QString &start_pos)
    : chessBoardModel(FEN::fromFENToBoard(start_pos))
{}

ChessBoardModel& GameEngine::getChessBoardModel()
{
    return chessBoardModel;
}
