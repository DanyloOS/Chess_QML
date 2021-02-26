#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H


#include <QAbstractListModel>

#include "chessboard.h"


#define CHESSBOARD_ROLE_OFFSET 100


class ChessBoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChessBoardRoles {
        CellColorRole = Qt::UserRole + CHESSBOARD_ROLE_OFFSET,
        PieceTypeRole,
        PieceColorRole,
        PieceCoordXRole,
        PieceCoordYRole
    };

    ChessBoardModel(ChessBoard board, QObject *parent = 0);
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void movePiece(int oldY, int oldX, int newY, int newX);

protected:
    QHash <int, QByteArray> roleNames() const override;

private:
    ChessBoard m_board;

    const Cell &cell(int index) const;
};

#endif // CHESSBOARDMODEL_H
