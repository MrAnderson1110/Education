#ifndef MOVECHECKER_H
#define MOVECHECKER_H

#include <QList>

#include <tuple>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;

typedef QPoint Move;
typedef QList<Move> Moves;

class CHESSCORE_EXPORT MoveChecker
{
    typedef QHash<int, Moves> MovesDirectionHash;

    struct CHESSCORE_EXPORT MoveDesctiption
    {
        // Направление обхода позиций от startPoint
        enum Direction
        {
            StartPoint,     // { piece pos point }
            TopLeft,        // { startPoint - 1, startPoint - 1 } -> column - 1 && row - 1
            Top,            // { startPoint - 1, startPoint     } -> column - 1 && row
            TopRight,       // { startPoint - 1, startPoint + 1 } -> column - 1 && row + 1
            Right,          // { startPoint,     startPoint + 1 } -> column     && row + 1
            BottomRight,    // { startPoint + 1, startPoint + 1 } -> column + 1 && row + 1
            Bottom,         // { startPoint + 1, startPoint     } -> column + 1 && row
            BottomLeft,     // { startPoint + 1, startPoint - 1 } -> column + 1 && row - 1
            Left            // { startPoint ,    startPoint - 1 } -> column     && row - 1
        };

        BasicPiece *initiator;
        MovesDirectionHash availableMoves;
    };

    typedef MoveDesctiption::Direction Direction;

public:
    explicit MoveChecker(BasicBoard *board);

    Moves filteredMoves(BasicPiece *piece);

private:
    MoveDesctiption rawDesctiption(BasicPiece *piece);

    void kingFilter(MoveDesctiption &king);
    void queenFilter(MoveDesctiption &queen);
    void bishopFilter(MoveDesctiption &bishop);
    void knightFilter(MoveDesctiption &knight);
    void rookFilter(MoveDesctiption &rook);
    void pawnFilter(MoveDesctiption &pawn);

    void kingRawMoves(MoveDesctiption &piece);
    void queenRawMoves(MoveDesctiption &piece);
    void bishopRawMoves(MoveDesctiption &piece);
    void knightRawMoves(MoveDesctiption &piece);
    void rookRawMoves(MoveDesctiption &piece);
    void pawnRawMoves(MoveDesctiption &piece);

private:
    BasicBoard *m_board;
};

#endif // MOVECHECKER_H
