#ifndef SELECTOR_H
#define SELECTOR_H

#include <QList>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class BasicGridCell;

class CHESSCORE_EXPORT Selector
{
public:
    explicit Selector(BasicBoard *board);

    void updateHover(const QRectF &pieceGeometry);
    /// piece === nullptr - сбрасывает все выделение
    void updateSelection(BasicPiece *piece, const QList<QPoint> &availableMoves = QList<QPoint>());
    QPoint hoveredPoint() const;

private:
    BasicBoard *m_board;
    BasicPiece *m_selectionPiece;
    BasicGridCell *m_hoveredCell;
    QList<BasicGridCell *> m_selectionList;
};

#endif // SELECTOR_H
