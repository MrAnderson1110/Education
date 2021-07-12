#ifndef MOVER_H
#define MOVER_H

#include <QObject>

#include "chesscore_global.h"

class BasicPiece;

class CHESSCORE_EXPORT Mover: QObject
{
    Q_OBJECT
public:
    explicit Mover(QObject *parent = nullptr);

    void onMoveStarted(BasicPiece *piece);
    void onMove(BasicPiece *piece);
    void onMoveFinished(BasicPiece *piece);

private:
    BasicPiece *m_movingPiece;
};

#endif // MOVER_H
