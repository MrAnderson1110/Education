#ifndef MOVER_H
#define MOVER_H

#include <QObject>

#include "chesscore_global.h"

class IPiece;

class CHESSCORE_EXPORT Mover: QObject
{
    Q_OBJECT
public:
    explicit Mover(QObject *parent = nullptr);

    void onMoveStarted(IPiece *piece);
    void onMove(IPiece *piece);
    void onMoveFinished(IPiece *piece);

private:
    IPiece *m_movingPiece;
};

#endif // MOVER_H
