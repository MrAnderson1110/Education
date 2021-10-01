#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include "chesscore_global.h"

class BasicPiece;
class BasicGridCell;

class CHESSCORE_EXPORT BaseVisitor
{
public:
    virtual ~BaseVisitor() {}
};

template<class T, typename R = void>
class CHESSCORE_EXPORT Visitor
{
public:
    typedef R ReturnType;
    virtual ReturnType visit(T *) = 0;
};

template<typename R = void>
class CHESSCORE_EXPORT BaseVisitable
{
public:
    typedef R ReturnType;
    virtual ~BaseVisitable() {}
    virtual ReturnType accept(BaseVisitor *visitor) = 0;

protected:
    template<class T>
    static ReturnType acceptImpl(T *visited, BaseVisitor *visitor)
    {
        Visitor<T> *castedVisitor = dynamic_cast<Visitor<T> *>(visitor);
        if(!castedVisitor)
            return ReturnType();

        castedVisitor->visit(visited);
    }
};

#define MAKE_VISITABLE() \
    virtual ReturnType accept(BaseVisitor *visitor) override { \
        return acceptImpl(this, visitor); \
    }

#endif // BASEVISITOR_H
