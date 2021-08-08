#include "mover.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"
#include "piecestrategy.h"

#include <QCursor>

Mover::Mover(BasicBoard *board, QObject *parent)
    : QObject(parent)
    , m_board(board)
    , m_movingPiece(nullptr)
    , m_preMovingCell(nullptr)
    , m_hoveredCell(nullptr)
    , m_selectionList()
{

}

void Mover::startMove(BasicPiece *piece)
{
    if(piece == m_movingPiece || m_movingPiece != nullptr)
        return;

    BasicGridCell *pieceCell = m_board->cell(piece->rowIndex(), piece->columnIndex());
    piece->setParentItem(m_board);
    piece->setGeometry(pieceCell->geometry());
    pieceCell->setPiece(nullptr);

    updateSelection(piece);

    m_preMovingCell = pieceCell;
    m_movingPiece = piece;
    m_hoveredCell = pieceCell;

    if(m_hoveredCell)
        m_hoveredCell->setHovered(true);
}

void Mover::move(BasicPiece *piece, const QRect &geometry)
{
    if(m_movingPiece != piece || !geometry.isValid())
        return;

    piece->setGeometry(geometry);

    if(m_hoveredCell != nullptr)
        m_hoveredCell->setHovered(false);

    m_hoveredCell = m_board->cellUnderMouse(piece->geometry().center());

    if(m_hoveredCell != nullptr && m_selectionList.contains(m_hoveredCell))
        m_hoveredCell->setHovered(true);
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


    if(cell != m_preMovingCell)
        updateSelection(nullptr);

    if(m_hoveredCell != nullptr)
        m_hoveredCell->setHovered(false);

    m_hoveredCell = nullptr;
    m_movingPiece = nullptr;
    m_preMovingCell = nullptr;

    finishCastlingMove(piece);
}

void Mover::updateSelection(BasicPiece *piece)
{
    for(BasicGridCell *cell : qAsConst(m_selectionList))
        m_board->deselect(cell->rowIndex(), cell->columnIndex());

    m_selectionList.clear();

    if(!piece)
        return;

    QList<QPoint> moves = piece->availableMoves();
    if(moves.isEmpty())
        return;

    moves << QPoint(piece->rowIndex(), piece->columnIndex());
    for(QPoint p : qAsConst(moves)) {
        BasicGridCell *cell = m_board->cell(p.x(), p.y());

        Q_ASSERT_X(cell != nullptr,
                   "Mover::updateSelection()",
                   "cell in row: " + QString::number(p.x()).toLatin1() +
                   " column " + QString::number(p.y()).toLatin1() +
                   " is not available for piece type: " + QString::number(piece->type()).toLatin1());

        m_selectionList.append(cell);
        m_board->select(cell->rowIndex(), cell->columnIndex(), piece);
    }
}

void Mover::finishCastlingMove(BasicPiece *piece)
{
    if(piece->type() != BasicPiece::King)
        return;

    PieceStrategy<BasicPiece::King> *kingStrategy = dynamic_cast<PieceStrategy<BasicPiece::King> *>(piece);
    if(!kingStrategy->needCastling())
        return;

    QPoint rookPoint = kingStrategy->castlingRookPoint();
    PieceStrategy<BasicPiece::Rook> *rookStrategy =
            dynamic_cast<PieceStrategy<BasicPiece::Rook> *>(m_board->cell(rookPoint.x(), rookPoint.y())->piece());

    rookStrategy->startMove();
    BasicGridCell *cell = m_board->cell(rookStrategy->castlingPoint().x(), rookStrategy->castlingPoint().y());
    rookStrategy->setGeometry(cell->geometry());
    m_selectionList.append(cell);
    rookStrategy->finishMove();
}
