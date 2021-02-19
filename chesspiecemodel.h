#ifndef CHESSPIECEMODEL_H
#define CHESSPIECEMODEL_H


#include "chesspiece.h"

#include <QAbstractListModel>
#include <QStringList>


class ChessPieceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChessPieceRoles {
        PieceTypeRole = Qt::UserRole + 10,
        PieceColorRole,
        PieceCoordX,
        PieceCoordY
    };

    ChessPieceModel(QObject *parent = 0);
    void addPiece(const ChessPiece &piece);
    void setPieceList(QList <ChessPiece> &piecesList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash <int, QByteArray> roleNames() const;

private:
    QList <ChessPiece> m_pieces;
};

#endif // CHESSPIECEMODEL_H
