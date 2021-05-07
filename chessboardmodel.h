#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H

#include <QAbstractListModel>
#include "chessboard.h"
#include "uciengine.h"

#define CHESSBOARD_ROLE_OFFSET 100
#define ENGINE_PATH "/home/danylos/Coding/Stockfish/src/stockfish"


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
    Q_INVOKABLE void playerMakesMove(int oldY, int oldX, int newY, int newX);

protected:
    QHash <int, QByteArray> roleNames() const override;

private:
    ChessBoard m_board;
    PieceColor_e m_currentPlayer;
    UciEngine m_engine;
    QString m_movesHistory;

private slots:
    void applyMove(QString move);
    void toggleCurrentPlayer();
    void askForMove();
    const Cell &cell(int index) const;

signals:
    void readyToMove(QString);
    void moveApplied();
    void whiteToMove();
    void blackToMove();
};

#endif // CHESSBOARDMODEL_H
