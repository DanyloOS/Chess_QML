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

