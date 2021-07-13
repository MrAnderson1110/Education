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
    Q_PROPERTY(int rowIndex READ rowIndex WRITE setRowIndex NOTIFY rowIndexChanged)
    Q_PROPERTY(int columnIndex READ columnIndex WRITE setColumnIndex NOTIFY columnIndexChanged)

public:
    explicit BasicGridCell(QQuickItem *parent = nullptr);

    int rowIndex() const;
    int columnIndex() const;

public slots:
    void setColumnIndex(int newColumnIndex);
    void setRowIndex(int newRowIndex);

signals:
    void rowIndexChanged(int);
    void columnIndexChanged(int);

private:
    int m_rowIndex;
    int m_columnIndex;
};

#endif // BASICGRIDCELL_H
