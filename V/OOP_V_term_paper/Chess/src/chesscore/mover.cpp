#include "mover.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"

#include <QCursor>

Mover::Mover(BasicBoard *board)
    : m_board(board)
    , m_movingPiece(nullptr)
    , m_preMovingCell(nullptr)
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

    m_preMovingCell = pieceCell;
    m_movingPiece = piece;
}

void Mover::move(BasicPiece *piece, const QRectF &geometry)
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

    piece->setRowIndex(cell->rowIndex());
    piece->setColumnIndex(cell->columnIndex());
    piece->setGeometry(cell->geometry());
    cell->setPiece(piece);

    m_movingPiece = nullptr;
    m_preMovingCell = nullptr;
}

void Mover::resetPosition(BasicPiece *piece)
{
    Q_ASSERT(m_movingPiece == piece);
    if(m_movingPiece != piece)
        return;

    piece->setRowIndex(m_preMovingCell->rowIndex());
    piece->setColumnIndex(m_preMovingCell->columnIndex());
    piece->setGeometry(m_preMovingCell->geometry());
    m_preMovingCell->setPiece(piece);

    m_movingPiece = nullptr;
    m_preMovingCell = nullptr;
}

//void Mover::finishCastlingMove(BasicPiece *piece)
//{
//    if(piece->type() != BasicPiece::King)
//        return;

//    PieceStrategy<BasicPiece::King> *kingStrategy = dynamic_cast<PieceStrategy<BasicPiece::King> *>(piece);
//    if(!kingStrategy->needCastling())
//        return;

//    QPoint rookPoint = kingStrategy->castlingRookPoint();
//    PieceStrategy<BasicPiece::Rook> *rookStrategy =
//            dynamic_cast<PieceStrategy<BasicPiece::Rook> *>(m_board->cell(rookPoint.x(), rookPoint.y())->piece());

//    rookStrategy->startMove();
//    BasicGridCell *cell = m_board->cell(rookStrategy->castlingPoint().x(), rookStrategy->castlingPoint().y());
//    rookStrategy->setGeometry(cell->geometry());
//    m_selectionList.append(cell);
//    rookStrategy->finishMove();
//}
