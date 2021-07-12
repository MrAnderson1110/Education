#ifndef BASICGRIDCELL_H
#define BASICGRIDCELL_H

#include <QQuickItem>

#include "chesscore_global.h"

/*!
 *  Базовый компонент клетки шахматной доски
 *
 *  Содержит описание клетки:
 *      координаты,
 *      фигура, находящяяся в данной клетке
 *  Содержит методы доступа к фигуре в данной клетке
 */

class BasicPiece;

class CHESSCORE_EXPORT BasicGridCell : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int rowIndex READ rowIndex WRITE setRowIndex NOTIFY rowIndexChanged)
    Q_PROPERTY(int columnIndex READ columnIndex WRITE setColumnIndex NOTIFY columnIndexChanged)

public:
    explicit BasicGridCell(QQuickItem *parent = nullptr);

    QQuickItem *background() const;    
    int rowIndex() const;
    int columnIndex() const;

public slots:
    void setBackground(QQuickItem *newBackground);
    void setColumnIndex(int newColumnIndex);
    void setRowIndex(int newRowIndex);

signals:
    void backgroundChanged(QQuickItem *);    
    void rowIndexChanged(int);
    void columnIndexChanged(int);

private:
    QQuickItem *m_background;
    int m_rowIndex;
    int m_columnIndex;
};

#endif // BASICGRIDCELL_H
