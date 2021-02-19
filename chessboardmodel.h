#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H


#include <QAbstractListModel>
#include <QStringList>


class Cell
{
public:
    Cell(int color);
    qint32 getColor() const;

private:
    qint32 _color;
};

class ChessBoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChessBoardRoles {
        CellColorRole = Qt::UserRole + 1
    };

    ChessBoardModel(QObject *parent = 0);
    void addCell(const Cell &cell);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash <int, QByteArray> roleNames() const;

private:
    QList <Cell> m_cells;
};

#endif // CHESSBOARDMODEL_H
