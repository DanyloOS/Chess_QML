#include "chessboardmodel.h"

#include <QDebug>
#include <algorithm>

#include "fen.h"

ChessBoardModel::ChessBoardModel(ChessBoard board, QObject *parent)
    : QAbstractListModel(parent), m_board(std::move(board))
    , m_currentPlayer(PieceColor_e::White)
{
    m_engine.startEngine(ENGINE_PATH);//, QStringList({"uci", "ucinewgame", "isready"}));
//    connect(this, &ChessBoardModel::initiateGame, this, &ChessBoardModel::findLegalMoves);
    connect(this, &ChessBoardModel::readyToMove, this, &ChessBoardModel::applyMove, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::piecesChanged, this, &ChessBoardModel::updatePiecesOnBoard, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::moveApplied, this, &ChessBoardModel::toggleCurrentPlayer, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::moveApplied, this, &ChessBoardModel::updatePiecesOnBoard, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::blackToMove, this, &ChessBoardModel::askForMove, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::whiteToMove, this, &ChessBoardModel::askForMove, Qt::UniqueConnection);
    connect(&m_engine, &UciEngine::bestMoveFound, this, &ChessBoardModel::applyMove, Qt::UniqueConnection);
    connect(&m_engine, &UciEngine::legalMovesFound, this, &ChessBoardModel::saveLegalMoves, Qt::UniqueConnection);
    connect(this, &ChessBoardModel::gameOver, this, &ChessBoardModel::processGameOver, Qt::UniqueConnection);
    QThread::msleep(100);
    findLegalMoves();
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
        return static_cast <int>(cell.color());
        break;
    case PieceTypeRole:
        return static_cast <int>(cell.piece().type());
        break;
    case PieceColorRole:
        return static_cast <int>(cell.piece().color());
        break;
    case PieceCoordXRole:
        return index.row() % 8;
        break;
    case PieceCoordYRole:
        return index.row() / 8;
        break;
    default:
        qDebug("[WARNING] ChessBoardModel() - bad role");
        return QVariant();
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
        {'a', 0}, {'1', 7},
        {'b', 1}, {'2', 6},
        {'c', 2}, {'3', 5},
        {'d', 3}, {'4', 4},
        {'e', 4}, {'5', 3},
        {'f', 5}, {'6', 2},
        {'g', 6}, {'7', 1},
        {'h', 7}, {'8', 0},
    };

    if (!isMoveLegal(move))
    {
        endResetModel();
        return;
    }

    int newY, newX, oldY, oldX;
    oldX = ctoi[move.at(0)];
    oldY = ctoi[move.at(1)];
    newX = ctoi[move.at(2)];
    newY = ctoi[move.at(3)];

    const ChessPiece &oldPiece =  m_board.at(oldY, oldX).piece();

    switch (typeOfMove(move))
    {
    case TypeOfMove::DefaultMove:
        qDebug() << "DefaultMove";
        m_board.at(newY, newX).setPiece(oldPiece);
        break;
    case TypeOfMove::Castling:
        qDebug() << "Castling";
        if (move.at(2) == "g")
        {
            Cell &oldRockCell = m_board.at(newY, ctoi['h']);
            const ChessPiece &rock = oldRockCell.piece();
            m_board.at(newY, ctoi['f']).setPiece(rock);
            oldRockCell.setPiece(ChessPiece());
        }
        else
        {
            Cell &oldRockCell = m_board.at(newY, ctoi['a']);
            const ChessPiece &rock = oldRockCell.piece();
            m_board.at(newY, ctoi['d']).setPiece(rock);
            oldRockCell.setPiece(ChessPiece());
        }
        m_board.at(newY, newX).setPiece(oldPiece);
        break;
    case TypeOfMove::EnPassant:
        qDebug() << "EnPassant";
        break;
    case TypeOfMove::Promotion:
        qDebug() << "Promotion";
        m_board.at(newY, newX)
                .setPiece(ChessPiece(PieceType_e::Queen, oldPiece.color()));
        break;
    default: exit(EXIT_FAILURE);
    }

    m_board.at(oldY, oldX).setPiece(ChessPiece());
    qDebug() << "applyMove() move = " << move << "   "
        << oldX << ' ' << oldY << ' ' << newX << ' ' << newY;
    endResetModel();
    m_movesHistory += move + " ";
    emit moveApplied();
}

void ChessBoardModel::toggleCurrentPlayer()
{
    m_engine.findLegalMoves(m_movesHistory);
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
    QThread::msleep(300);
}

bool ChessBoardModel::isMoveLegal(QString move)
{
    return m_legalMoves.count(move);
}

void ChessBoardModel::findLegalMoves()
{
    m_engine.findLegalMoves(m_movesHistory);
}

void ChessBoardModel::saveLegalMoves(const QString& legalMoves)
{
    m_legalMoves = legalMoves.split(" ");
    qDebug() << "legal moves: " << legalMoves;
    if (m_legalMoves.first() == "")
        emit gameOver(m_currentPlayer);
}

void ChessBoardModel::processGameOver(PieceColor_e p)
{
    QString result;
    if (p == PieceColor_e::None)
        result = "DRAW";
    else
        result = QString("PLAYER ") + (p != PieceColor_e::Black ? "Black" : "White") + " WINS";
    qDebug("%s %s %s", "______________________________________\n"
                "\t\tGAME OVER\n"
                "\t", result.toStdString().c_str(),
                "\n"
                "______________________________________");

    disconnect(&m_engine, &UciEngine::legalMovesFound, this, &ChessBoardModel::saveLegalMoves);
    m_legalMoves.clear();
    m_winner = PieceColor_to_int(p);
    emit winnerChanged(m_winner);
}

ChessBoardModel::TypeOfMove ChessBoardModel::typeOfMove(QString move)
{
    if (move.length() == 5)
        return TypeOfMove::Promotion;
    if (QStringList{"e1g1", "e1c1", "e8g8", "e8c8"}.count(move))
        return TypeOfMove::Castling;
    return TypeOfMove::DefaultMove;
}

void ChessBoardModel::updatePiecesOnBoard()
{
    m_piecesOnBoard.clear();

    for (const auto& row : m_board)
        for (const auto& cell : row)
            if (cell.piece().type() != PieceType_e::None)
                m_piecesOnBoard.append(cell.piece());

    std::sort(m_piecesOnBoard.begin(), m_piecesOnBoard.end(),
              [](const ChessPiece& lhs, const ChessPiece& rhs)
    {
        return std::pair{lhs.color(), lhs.type()} < std::pair{rhs.color(), rhs.type()
    };});

    auto itBegin = m_piecesOnBoard.begin();
    auto itEnd = m_piecesOnBoard.end();
    auto itMid = std::find_if(itBegin, itEnd, [](const ChessPiece& p)
        { return p.color() == PieceColor_e::Black; });

    if (std::find_if(itBegin, itEnd, [](const ChessPiece& p)
                     { return p.type() == PieceType_e::Pawn; }) != itEnd)
    {
        qDebug() << "info: pawns are still in game";
        return;
    }

    QString whitePieces;
    QString blackPieces;

    std::for_each(itBegin, itMid, [&whitePieces](const ChessPiece& p)
    { whitePieces.append(ChessPiece::typeToStr(p.type())); });
    std::for_each(itMid, itEnd, [&blackPieces](const ChessPiece& p)
    { blackPieces.append(ChessPiece::typeToStr(p.type())); });

    qDebug() << "updatePiecesOnBoard : " << whitePieces << " vs " << blackPieces;

    if (whitePieces > blackPieces)
        std::swap(whitePieces, blackPieces);

    if (whitePieces == "k" &&
        (blackPieces == "k" || blackPieces == "kb" || blackPieces == "kn"))
        emit gameOver(PieceColor_e::None);
    if (whitePieces == "kb" && blackPieces == "kb")
        emit gameOver(PieceColor_e::None);

    /*
     * k,b : k,b
     * k : k,n
     * k : k,b
     * k : k
     */
}

void ChessBoardModel::resetModel()
{
//    connect(this, &ChessBoardModel::readyToMove, this, &ChessBoardModel::applyMove);
//    connect(this, &ChessBoardModel::piecesChanged, this, &ChessBoardModel::updatePiecesOnBoard);
//    connect(this, &ChessBoardModel::moveApplied, this, &ChessBoardModel::toggleCurrentPlayer);
//    connect(this, &ChessBoardModel::moveApplied, this, &ChessBoardModel::updatePiecesOnBoard);
//    connect(this, &ChessBoardModel::blackToMove, this, &ChessBoardModel::askForMove);
////    connect(this, &ChessBoardModel::whiteToMove, this, &ChessBoardModel::askForMove);
//    connect(&m_engine, &UciEngine::bestMoveFound, this, &ChessBoardModel::applyMove);
//    connect(&m_engine, &UciEngine::legalMovesFound, this, &ChessBoardModel::saveLegalMoves);
//    connect(this, &ChessBoardModel::gameOver, this, &ChessBoardModel::processGameOver);
//    QThread::msleep(100);
    connect(&m_engine, &UciEngine::legalMovesFound, this, &ChessBoardModel::saveLegalMoves);
    m_board = FEN::fromFENToBoard(CHESS_DEFAULT_FEN);
    m_currentPlayer = PieceColor_e::White;
//    m_engine = UciEngine();
    m_movesHistory.clear();
    m_legalMoves.clear();
    m_piecesOnBoard.clear();
    m_winner = PieceColor_to_int(PieceColor_e::None);
    findLegalMoves();
    endResetModel();
}

//void whiteToMove()
//{
//    qDebug() << "White to move!";
//}

//void blackToMove()
//{
//    qDebug() << "Black to move!";
//}
