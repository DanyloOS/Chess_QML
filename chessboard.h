#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include <vector>

#include "chesspiece.h"


enum class CellColor_e {
    Black = 0,
    White
};

class Cell
{
public:
    Cell() = default;
    Cell(CellColor_e color);

    ChessPiece piece() const;
    void setPiece(const ChessPiece &piece);
    CellColor_e color() const;

private:
    ChessPiece m_piece;
    CellColor_e m_color;
};

class ChessBoard
{
public:
    using Board = std::vector <std::vector <Cell>>;

public:
    ChessBoard();
    ChessBoard(Board board);

    const Cell& cell(std::size_t col, std::size_t row) const;
    int rowCount() const;
    int columnCount() const;

    std::vector <Cell>& operator[](std::size_t index);
    const Cell &operator [](std::size_t index) const;
    Cell& at(std::size_t y, std::size_t x);
    const Cell& at(std::size_t y, std::size_t x) const;

private:
    Board m_board;
};

#endif // CHESSBOARD_H
