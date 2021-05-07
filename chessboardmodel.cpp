#include "chessboardmodel.h"

#include <QDebug>

ChessBoardModel::ChessBoardModel(ChessBoard board, QObject *parent)
    : QAbstractListModel(parent), m_board(std::move(board))
    , m_currentPlayer(PieceColor_e::White)
{
    m_engine.startEngine(ENGINE_PATH);//, QStringList({"uci", "ucinewgame", "isready"}));
    connect(this, &ChessBoardModel::readyToMove, this, &ChessBoardModel::applyMove);
    connect(this, &ChessBoardModel::moveApplied, this, &ChessBoardModel::toggleCurrentPlayer);
    connect(this, &ChessBoardModel::blackToMove, this, &ChessBoardModel::askForMove);
    connect(&m_engine, &UciEngine::bestMoveFound, this, &ChessBoardModel::applyMove);
}

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

void ChessBoardModel::playerMakesMove(int oldY, int oldX, int newY, int newX)
{
    const static QMap <int, QChar> itoc {
        {0, 'a'},
        {1, 'b'},
        {2, 'c'},
        {3, 'd'},
        {4, 'e'},
        {5, 'f'},
        {6, 'g'},
        {7, 'h'}
    };

    if (std::make_pair(oldY, oldX) != std::make_pair(newY, newX))
    {
//        m_board.at(newY, newX).setPiece(m_board.at(oldY, oldX).piece());
//        m_board.at(oldY, oldX).setPiece(ChessPiece());
//        endResetModel();
        QString move;
        move.append(itoc[oldX]);
        move.append(QString::number(8 - oldY));
        move.append(itoc[newX]);
        move.append(QString::number(8 - newY));
        qDebug() << "playerMakesMove() move = " << move << "   "
                << oldX << ' ' << oldY << ' ' << newX << ' ' << newY;
        emit readyToMove(move);
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

void ChessBoardModel::applyMove(QString move)
{
    const static QMap <QChar, int> ctoi {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7},
        {'1', 7},
        {'2', 6},
        {'3', 5},
        {'4', 4},
        {'5', 3},
        {'6', 2},
        {'7', 1},
        {'8', 0}
    };

    int newY, newX, oldY, oldX;
    oldX = ctoi[move.at(0)];
    oldY = ctoi[move.at(1)];
    newX = ctoi[move.at(2)];
    newY = ctoi[move.at(3)];

    qDebug() << "applyMove() move = " << move << "   "
            << oldX << ' ' << oldY << ' ' << newX << ' ' << newY;

    m_board.at(newY, newX).setPiece(m_board.at(oldY, oldX).piece());
    m_board.at(oldY, oldX).setPiece(ChessPiece());
    endResetModel();
    m_movesHistory += move + " ";
    emit moveApplied();
}

void ChessBoardModel::toggleCurrentPlayer()
{
    m_currentPlayer = (m_currentPlayer == PieceColor_e::White) ? PieceColor_e::Black : PieceColor_e::White;
    switch (m_currentPlayer) {
    case PieceColor_e::White: emit whiteToMove(); break;
    case PieceColor_e::Black: emit blackToMove(); break;
    default: exit(EXIT_FAILURE);
    }
}

void ChessBoardModel::askForMove()
{
    m_engine.findMove(m_movesHistory);
}

//void whiteToMove()
//{
//    qDebug() << "White to move!";
//}

//void blackToMove()
//{
//    qDebug() << "Black to move!";
//}
