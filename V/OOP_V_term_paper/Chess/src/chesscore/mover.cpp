#include "mover.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"
#include "piecestrategy.h"

typedef BasicPiece::Type PieceType;
typedef BasicPiece::Command PieceCommand;

Mover::Mover(BasicBoard *board, QObject *parent)
    : QObject(parent)
    , m_board(board)
    , m_movingPiece(nullptr)
    , m_preMovingCell(nullptr)
    , m_selectionList()
    , m_currentCommand(PieceCommand::White)
{

}

void Mover::startMove(BasicPiece *piece)
{
    if(piece == m_movingPiece || m_movingPiece != nullptr)
//            || piece->command() != m_currentCommand)
        return;

    BasicGridCell *pieceCell = m_board->cell(piece->rowIndex(), piece->columnIndex());
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

    m_board->cell(piece->rowIndex(), piece->columnIndex())->setPiece(nullptr);
    BasicGridCell *cell = m_board->cellUnderMouse(piece->geometry().center());

    if(cell == nullptr || !m_selectionList.contains(cell))
        cell = m_preMovingCell;

    moveRook(QPoint(cell->rowIndex(), cell->columnIndex()), piece);

    piece->setRowIndex(cell->rowIndex());
    piece->setColumnIndex(cell->columnIndex());
    piece->setGeometry(cell->geometry());
    cell->setPiece(piece);

    checkPawn(piece);

    if(cell != m_preMovingCell) {
        piece->setMoved(true);
        updateSelection(nullptr);
        m_currentCommand = piece->command() == PieceCommand::White ? PieceCommand::Black
                                                                   : PieceCommand::White;
    }

    m_movingPiece = nullptr;
    m_preMovingCell = nullptr;
}

QList<QPoint> Mover::getWhiteMoves(BasicPiece *piece) const
{
    switch (piece->type()) {
    case PieceType::King: {
        PieceStrategy<PieceType::King, PieceCommand::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Queen: {
        PieceStrategy<PieceType::Queen, PieceCommand::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Bishop: {
        PieceStrategy<PieceType::Bishop, PieceCommand::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Knight: {
        PieceStrategy<PieceType::Knight, PieceCommand::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Rook: {
        PieceStrategy<PieceType::Rook, PieceCommand::White> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Pawn: {
        PieceStrategy<PieceType::Pawn, PieceCommand::White> strategy(m_board);
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
    case PieceType::King: {
        PieceStrategy<PieceType::King, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Queen: {
        PieceStrategy<PieceType::Queen, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Bishop: {
        PieceStrategy<PieceType::Bishop, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Knight: {
        PieceStrategy<PieceType::Knight, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Rook: {
        PieceStrategy<PieceType::Rook, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    case PieceType::Pawn: {
        PieceStrategy<PieceType::Pawn, PieceCommand::Black> strategy(m_board);
        return strategy.availableMoves(piece->rowIndex(), piece->columnIndex());
    }
    default:
        return QList<QPoint>();
    }

    return QList<QPoint>();
}

void Mover::moveRook(const QPoint &newKingPos, BasicPiece *movingPiece)
{
    if(movingPiece->type() != PieceType::King)
        return;

    int availableRow = movingPiece->command() == PieceCommand::White ? 7 : 0;
    if(movingPiece->rowIndex() != availableRow
            || newKingPos.x() != availableRow
            || movingPiece->columnIndex() != 4 )
        return;

    int newRookCol = newKingPos.y() == 6 ? 5 : newKingPos.y() == 2 ? 3 : -1;
    int oldRookCol = newKingPos.y() == 6 ? 7 : newKingPos.y() == 2 ? 0 : -1;

    BasicPiece *rook = nullptr;
    BasicGridCell *rookCell = nullptr;

    if(newRookCol >= 0 && oldRookCol >= 0) {
        rook = m_board->cell(availableRow, oldRookCol)->piece();
        rookCell = m_board->cell(availableRow, newRookCol);
    }

    if(rook != nullptr && rookCell != nullptr
            && rook->type() == PieceType::Rook && !rook->moved()) {
        rook->setRowIndex(rookCell->rowIndex());
        rook->setColumnIndex(rookCell->columnIndex());
        rook->setGeometry(rookCell->geometry());
        rookCell->setPiece(rook);
    }
}

void Mover::checkPawn(BasicPiece *movedPiece)
{
    if(movedPiece->type() != PieceType::Pawn)
        return;

    int destanationRow = movedPiece->command() == PieceCommand::White ? 7 : 0;
    if(movedPiece->rowIndex() == destanationRow) {
        qDebug() << "emit changed pawn";
        emit pawnCanChange(movedPiece);
    }
}

void Mover::updateSelection(BasicPiece *piece)
{
    for(BasicGridCell *cell : qAsConst(m_selectionList))
        m_board->deselect(cell->rowIndex(), cell->columnIndex());

    m_selectionList.clear();

    if(!piece)
        return;

    QList<QPoint> moves;
    if(piece->command() == PieceCommand::White)
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
