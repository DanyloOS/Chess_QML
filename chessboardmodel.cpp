#include "chessboardmodel.h"


ChessBoardModel::ChessBoardModel(ChessBoard board, QObject *parent)
    : QAbstractTableModel(parent), m_board(std::move(board))
{}

int ChessBoardModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_board.rowCount();
}

int ChessBoardModel::columnCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_board.columnCount();
}

QVariant ChessBoardModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_board.rowCount())
        return QVariant();
    if (index.column() < 0 || index.column() >= m_board.columnCount())
        return QVariant();

    const Cell &cell = m_board[index.column()][index.row()];

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
    return roles;
}

