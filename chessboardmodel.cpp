#include "chessboardmodel.h"


Cell::Cell(int color) : _color(color) {};

int Cell::getColor() const
{
    return _color;
}

ChessBoardModel::ChessBoardModel(QObject *parent)
    : QAbstractListModel(parent)
{}

void ChessBoardModel::addCell(const Cell &cell)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_cells << cell;
    endInsertRows();
}

int ChessBoardModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_cells.count();
}

QVariant ChessBoardModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_cells.count())
        return QVariant();

    const Cell &cell = m_cells[index.row()];
    if (role == CellColorRole)
        return cell.getColor();
    return QVariant();
}

QHash<int, QByteArray> ChessBoardModel::roleNames() const {
    QHash <int, QByteArray> roles;
    roles[CellColorRole] = "cellColor";
    return roles;
}
