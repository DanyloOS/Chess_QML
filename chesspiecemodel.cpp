#include "chesspiecemodel.h"


ChessPieceModel::ChessPieceModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ChessPieceModel::addPiece(const ChessPiece &piece)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_pieces << piece;
    endInsertRows();
}

// XXX: Does we need it?
int ChessPieceModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_pieces.count();
}

QVariant ChessPieceModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_pieces.count())
        return QVariant();

    const ChessPiece &piece = m_pieces[index.row()];
    if (role == PieceTypeRole)
        return static_cast <int>(piece.getType());
    if (role == PieceColorRole)
        return static_cast <int>(piece.getColor());
    if (role == PieceCoordX)
        return piece.getCoordX();
    if (role == PieceCoordY)
        return piece.getCoordY();

    return QVariant();
}

QHash <int, QByteArray> ChessPieceModel::roleNames() const {
    QHash <int, QByteArray> roles;
    roles[PieceTypeRole] = "pieceType";
    roles[PieceColorRole] = "pieceColor";
    roles[PieceCoordX] = "pieceCoordX";
    roles[PieceCoordY] = "pieceCoordY";
    return roles;
}

void ChessPieceModel::setPieceList(QList<ChessPiece> &piecesList)
{
    m_pieces = piecesList;
}


