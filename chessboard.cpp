#include "chessboard.h"


Cell::Cell(CellColor_e color)
    : m_color(color)
{
}

ChessPiece Cell::piece() const
{
    return m_piece;
}

void Cell::setPiece(const ChessPiece &piece)
{
    m_piece = piece;
}

CellColor_e Cell::color() const
{
    return m_color;
}

ChessBoard::ChessBoard()
    : m_board(8, std::vector <Cell> (8))
{
    int index = 0;
    for (auto &col : m_board)
    {
        for (auto &row : col)
        {
            row = Cell((index + index / 8) % 2
                       ? CellColor_e::White : CellColor_e::Black);
            ++index;
        }
    }
}

ChessBoard::ChessBoard(Board board)
    : m_board(std::move(board))
{
}

int ChessBoard::rowCount() const
{
    return m_board.at(0).size();
}

int ChessBoard::columnCount() const
{
    return m_board.size();
}

std::vector <Cell>& ChessBoard::operator[](std::size_t index)
{
    return m_board[index];
}

const Cell &ChessBoard::at(std::size_t y, std::size_t x) const
{
    return m_board[y][x];
}

const Cell& ChessBoard::operator[](std::size_t index) const
{
    return m_board[index / rowCount()][index % columnCount()];
}

