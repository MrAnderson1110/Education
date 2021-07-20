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
    Q_PROPERTY(bool selected READ selected NOTIFY selectedChanged)

public:
    explicit BasicGridCell(QQuickItem *parent = nullptr);

    virtual void polishContent() override;

    BasicPiece *piece() const;
    bool selected() const;

public slots:
    void setPiece(BasicPiece *newPiece);
    void setSelected(bool newSelected);

signals:
    void pieceChanged(BasicPiece *);
    void selectedChanged(bool);

private:
    BasicPiece *m_piece;
    bool m_selected;
};

#endif // BASICGRIDCELL_H
