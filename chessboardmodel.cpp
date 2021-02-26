#include "chessboardmodel.h"

#include <QDebug>

ChessBoardModel::ChessBoardModel(ChessBoard board, QObject *parent)
    : QAbstractListModel(parent), m_board(std::move(board))
{}

int ChessBoardModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_board.rowCount() * m_board.columnCount();
}

QVariant ChessBoardModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

//    qDebug() << "index: " << index.row() << ',' << index.column() << " \t " << index.row() / 8 << " " << index.row() % 8;
    const Cell &cell = this->cell(index.row());

    switch (role) {
    case CellColorRole:
    {
        return static_cast <int>(cell.color());
    } break;
    case PieceTypeRole:
    {
        return static_cast <int>(cell.piece().type());
    } break;
    case PieceColorRole:
    {
        return static_cast <int>(cell.piece().color());
    } break;
    case PieceCoordXRole:
    {
        return index.row() % 8;
    } break;
    case PieceCoordYRole:
    {
        return index.row() / 8;
    }
    default:
    {
        qDebug("[WARNING] ChessBoardModel() - bad role");
        return QVariant();
    }
    }
}

void ChessBoardModel::movePiece(int oldY, int oldX, int newY, int newX)
{
    if (std::make_pair(oldY, oldX) != std::make_pair(newY, newX))// && (rand() % 2))
    {
        m_board.at(newY, newX).setPiece(m_board.at(oldY, oldX).piece());
        m_board.at(oldY, oldX).setPiece(ChessPiece());
        endResetModel();
    }
}

QHash<int, QByteArray> ChessBoardModel::roleNames() const {
    QHash <int, QByteArray> roles;
    roles[CellColorRole] = "cellColor";
    roles[PieceTypeRole] = "pieceType";
    roles[PieceColorRole] = "pieceColor";
    roles[PieceCoordXRole] = "pieceCoordX";
    roles[PieceCoordYRole] = "pieceCoordY";
    return roles;
}

const Cell &ChessBoardModel::cell(int index) const
{
    return m_board[index];
}

