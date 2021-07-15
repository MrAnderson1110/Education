#ifndef BASICGRIDCELL_H
#define BASICGRIDCELL_H

#include "chesscore_global.h"
#include "graphicitem.h"

/*!
 *  Базовый компонент клетки шахматной доски
 *
 *  Содержит описание клетки:
 *      координаты,
 *      фигура, находящяяся в данной клетке
 *  Содержит методы доступа к фигуре в данной клетке
 */

class BasicPiece;

class CHESSCORE_EXPORT BasicGridCell : public GraphicItem
{
    Q_OBJECT
    Q_PROPERTY(BasicPiece *piece READ piece WRITE setPiece NOTIFY pieceChanged)

public:
    explicit BasicGridCell(QQuickItem *parent = nullptr);

    BasicPiece *piece() const;

public slots:
    void setPiece(BasicPiece *newPiece);

protected:
    virtual void polishContent() override;

signals:
    void pieceChanged(BasicPiece *);

private:
    BasicPiece *m_piece;
};

#endif // BASICGRIDCELL_H
