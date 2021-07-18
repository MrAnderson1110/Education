#include "mover.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"
#include "piecestrategy.h"

Mover::Mover(BasicBoard *board, QObject *parent)
    : QObject(parent)
    , m_board(board)
    , m_movingPiece(nullptr)
    , m_preMovingCell(nullptr)
    , m_selectionList()
{

}

void Mover::startMove(BasicPiece *piece)
{
    if(piece == m_movingPiece || m_movingPiece != nullptr)
        return;

    BasicGridCell *pieceCell = m_board->cell(piece->rowIndex(), piece->columnIndex());
    pieceCell->setPiece(nullptr);
    piece->setParentItem(m_board);
    piece->setGeometry(pieceCell->geometry());

    updateSelection(piece);

    m_preMovingCell = pieceCell;
    m_movingPiece = piece;
}

void Mover::move(BasicPiece *piece, const QRect &geometry)
{
    if(m_movingPiece != piece || !geometry.isValid())
        return;

    piece->setGeometry(geometry);
}

void Mover::finishMove(BasicPiece *piece)
{
    if(m_movingPiece != piece)
        return;

    BasicGridCell *cell = m_board->cellUnderMouse(piece->geometry().center());

    if(cell == nullptr || !m_selectionList.contains(cell))
        cell = m_preMovingCell;

    piece->setRowIndex(cell->rowIndex());
    piece->setColumnIndex(cell->columnIndex());
    piece->setGeometry(cell->geometry());
    cell->setPiece(piece);

    updateSelection(piece);

    m_movingPiece = nullptr;
    m_preMovingCell = nullptr;
}

QList<QPoint> Mover::getWhiteMoves(BasicPiece *piece) const
{
    switch (piece->type()) {
    case BasicPiece::Type::King: {
        PieceStrategy<BasicPiece::Type::King, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Queen: {
        PieceStrategy<BasicPiece::Type::Queen, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Bishop: {
        PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Knight: {
        PieceStrategy<BasicPiece::Type::Knight, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Rook: {
        PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Pawn: {
        PieceStrategy<BasicPiece::Type::Pawn, BasicPiece::Command::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    default:
        return QList<QPoint>();
    }

    return QList<QPoint>();
}

QList<QPoint> Mover::getBlackMoves(BasicPiece *piece) const
{
    switch (piece->type()) {
    case BasicPiece::Type::King: {
        PieceStrategy<BasicPiece::Type::King, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Queen: {
        PieceStrategy<BasicPiece::Type::Queen, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Bishop: {
        PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Knight: {
        PieceStrategy<BasicPiece::Type::Knight, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Rook: {
        PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case BasicPiece::Type::Pawn: {
        PieceStrategy<BasicPiece::Type::Pawn, BasicPiece::Command::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    default:
        return QList<QPoint>();
    }

    return QList<QPoint>();
}

void Mover::updateSelection(BasicPiece *piece)
{
    for(BasicGridCell *cell : qAsConst(m_selectionList))
        m_board->deselect(cell->rowIndex(), cell->columnIndex());

    m_selectionList.clear();

    if(!piece)
        return;

    QList<QPoint> moves;
    if(piece->command() == BasicPiece::Command::White)
        moves = getWhiteMoves(piece);
    else
        moves = getBlackMoves(piece);

    if(moves.isEmpty())
        return;

    moves << QPoint(piece->rowIndex(), piece->columnIndex());
    for(QPoint p : qAsConst(moves)) {
        BasicGridCell *cell = m_board->cell(p.x(), p.y());
        Q_ASSERT(cell != nullptr);
        m_selectionList.append(cell);
        m_board->select(cell->rowIndex(), cell->columnIndex());
    }
}
