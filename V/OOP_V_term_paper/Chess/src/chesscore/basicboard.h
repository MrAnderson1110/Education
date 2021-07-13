#ifndef BASICBOARD_H
#define BASICBOARD_H

#include <QQuickItem>

#include "chesscore_global.h"

/*!
 * Базовый компонент шахматной доски
 *
 * Содержит компоненты клеток доски, а также логику распределения клеток по доске.
 * Предоставляет доступ к клеткам доски во внешний мир.
 */

class BasicGridCell;
class BasicPiece;

class CHESSCORE_EXPORT BasicBoard : public QQuickItem
{
    Q_OBJECT

public:
    explicit BasicBoard(QQuickItem *parent = nullptr);

    void componentComplete();

private:
    QHash<int, QHash<int, BasicGridCell *>> m_grid;
    QList<BasicPiece *> m_pieces;
};

#endif // BASICBOARD_H
