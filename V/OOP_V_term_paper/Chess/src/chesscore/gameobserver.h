#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QRectF>
#include <memory>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class Selector;
class Mover;
class MoveChecker;

class CHESSCORE_EXPORT GameObserver
{
public:
    explicit GameObserver(BasicBoard *board);
    ~GameObserver();

    void startMove(BasicPiece *piece);
    void move(BasicPiece *piece, const QRectF &geometry);
    void finishMove(BasicPiece *piece);

    void clearSelection();

private:
    BasicBoard *m_board;
    Mover *m_mover;
    Selector *m_selector;
    MoveChecker *m_moveChecker;
};

#endif // GAMEOBSERVER_H
