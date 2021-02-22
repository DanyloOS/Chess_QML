#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H


#include <QAbstractTableModel>

#include "chessboard.h"


#define CHESSBOARD_ROLE_OFFSET 100


class ChessBoardModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ChessBoardRoles {
        CellColorRole = Qt::UserRole + CHESSBOARD_ROLE_OFFSET,
        PieceTypeRole,
        PieceColorRole
    };

    ChessBoardModel(ChessBoard board, QObject *parent = 0);
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    QHash <int, QByteArray> roleNames() const override;

private:
    ChessBoard m_board;
};

#endif // CHESSBOARDMODEL_H
