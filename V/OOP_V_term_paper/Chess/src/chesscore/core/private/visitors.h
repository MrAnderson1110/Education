#ifndef VISITORS_H
#define VISITORS_H

#include "../basevisitor.h"

#define ChessVisitor \
    public Visitor<King>, \
    public Visitor<Queen>, \
    public Visitor<Bishop>, \
    public Visitor<Knight>, \
    public Visitor<Rook>, \
    public Visitor<Pawn>

class BasicGridCell;

class King;
class Queen;
class Bishop;
class Knight;
class Rook;
class Pawn;

class CHESSCORE_EXPORT PremoveVisitor : ChessVisitor
{
public:
    PremoveVisitor();

    void visit(King *king) override;
    void visit(Queen *queen) override;
    void visit(Bishop *bishop) override;
    void visit(Knight *knight) override;
    void visit(Rook *rook) override;
    void visit(Pawn *pawn) override;
};

class CHESSCORE_EXPORT MoveVisitor : ChessVisitor
{
public:
    MoveVisitor();

    void visit(King *king) override;
    void visit(Queen *queen) override;
    void visit(Bishop *bishop) override;
    void visit(Knight *knight) override;
    void visit(Rook *rook) override;
    void visit(Pawn *pawn) override;
};


class CHESSCORE_EXPORT PostmoveVisitor : ChessVisitor
{
public:
    PostmoveVisitor();

    void visit(King *king) override;
    void visit(Queen *queen) override;
    void visit(Bishop *bishop) override;
    void visit(Knight *knight) override;
    void visit(Rook *rook) override;
    void visit(Pawn *pawn) override;
};

class CHESSCORE_EXPORT BoardCellVisitor : public Visitor<BasicGridCell>
{
public:
    BoardCellVisitor();

    void visit(BasicGridCell *cell);
};

#endif // VISITORS_H
