#ifndef CHESSBOARDMODEL_H
#define CHESSBOARDMODEL_H

#include <QAbstractListModel>
#include "chessboard.h"
#include "uciengine.h"

#define CHESSBOARD_ROLE_OFFSET 100
//#define ENGINE_PATH "/home/danylos/Coding/Stockfish/src/stockfish"
#define ENGINE_PATH "chessEngine"


class ChessBoardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int winner MEMBER m_winner NOTIFY winnerChanged)
public:
    enum ChessBoardRoles {
        CellColorRole = Qt::UserRole + CHESSBOARD_ROLE_OFFSET,
        PieceTypeRole,
        PieceColorRole,
        PieceCoordXRole,
        PieceCoordYRole
    };

    enum class TypeOfMove
    {
        DefaultMove,
        Castling,
        EnPassant,
        Promotion,
    };


    ChessBoardModel(ChessBoard board, QObject *parent = 0);
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void playerMakesMove(int oldY, int oldX, int newY, int newX);
    Q_INVOKABLE void resetModel();

protected:
    QHash <int, QByteArray> roleNames() const override;

private:
    ChessBoard m_board;
    PieceColor_e m_currentPlayer;
    UciEngine m_engine;
    QString m_movesHistory;
    QList <QString> m_legalMoves;
    QList <ChessPiece> m_piecesOnBoard;
    int m_winner = PieceColor_to_int(PieceColor_e::None);

private slots:
    void applyMove(QString move);
    void toggleCurrentPlayer();
    void askForMove();
    const Cell &cell(int index) const;
    bool isMoveLegal(QString move);
    void findLegalMoves();
    void saveLegalMoves(const QString &legalMoves);
    void processGameOver(PieceColor_e);
    TypeOfMove typeOfMove(QString move);
    void updatePiecesOnBoard();

signals:
    void initiateGame();
    void readyToMove(QString);
    void moveApplied();
    void whiteToMove();
    void blackToMove();
    void gameOver(PieceColor_e);
    void piecesChanged();
    void winnerChanged(int);
};

#endif // CHESSBOARDMODEL_H
