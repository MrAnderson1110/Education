#ifndef PIECESTRATEGY_H
#define PIECESTRATEGY_H

#include "basicpiece.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "chesscore_global.h"

template<typename BasicPiece::Type>
class CHESSCORE_EXPORT PieceStrategy : public BasicPiece
{    
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent) {}

protected:
    virtual QList<QPoint> availableMoves() override { return QList<QPoint>(); }
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::Bishop>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent) { setType(Bishop); }

    QList<QPoint> availableMoves() override
    {
        if(!board())
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();
        QList<QPoint> points;
        for(int i = row, j = column; canMove(i + 1, j + 1); ++i, ++j) {
            points << QPoint(i + 1, j + 1);
            if(board()->cell(i + 1, j + 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; canMove(i + 1, j - 1); ++i, --j) {
            points << QPoint(i + 1, j - 1);
            if(board()->cell(i + 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; canMove(i - 1, j - 1); --i, --j) {
            points << QPoint(i - 1, j - 1);
            if(board()->cell(i - 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; canMove(i - 1, j + 1); --i, ++j) {
            points << QPoint(i - 1, j + 1);
            if(board()->cell(i - 1, j + 1)->piece() != nullptr)
                break;
        }
        return points;
    }
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::Knight>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent) { setType(Knight); }

    QList<QPoint> availableMoves() override
    {
        if(!board())
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();
        QList<QPoint> points;

        int nextRow = row + 2;
        int nextCol = column + 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 2;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 2;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column + 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column - 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column - 2;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column - 2;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 2;
        nextCol = column - 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        return points;
    }
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::Rook>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent)
        , m_moved(false) { setType(Rook); }

    QList<QPoint> availableMoves() override
    {
        if(!board())
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();
        QList<QPoint> points;

        for(int i = row; canMove(i + 1, column); ++i) {
            points << QPoint(i + 1, column);
            if(board()->cell(i + 1, column)->piece() != nullptr)
                break;
        }

        for(int i = row; canMove(i - 1, column); --i) {
            points << QPoint(i - 1, column);
            if(board()->cell(i - 1, column)->piece() != nullptr)
                break;
        }

        for(int i = column; canMove(row, i - 1); --i) {
            points << QPoint(row, i - 1);
            if(board()->cell(row, i - 1)->piece() != nullptr)
                break;
        }

        for(int i = column; canMove(row, i + 1); ++i) {
            points << QPoint(row, i + 1);
            if(board()->cell(row, i + 1)->piece() != nullptr)
                break;
        }

        return points;
    }
    void finishMove() override
    {
        BasicPiece::finishMove();

        if(!m_moved)
            m_moved = true;
    }
    bool moved()
    {
        return m_moved;
    }
    QPoint castlingPoint()
    {
        if(m_moved)
            return QPoint(rowIndex(), columnIndex());

        return columnIndex() == 0 ? QPoint(rowIndex(), 3) : QPoint(rowIndex(), 5);
    }

private:
    bool m_moved;
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::Queen>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent) { setType(Queen); }

    QList<QPoint> availableMoves() override
    {
        PieceStrategy<Rook> rookStrategy;
        rookStrategy.setBoard(board());
        rookStrategy.setRowIndex(rowIndex());
        rookStrategy.setColumnIndex(columnIndex());
        rookStrategy.setCommand(command());
        PieceStrategy<Bishop> bishopStrategy;
        bishopStrategy.setBoard(board());
        bishopStrategy.setRowIndex(rowIndex());
        bishopStrategy.setColumnIndex(columnIndex());
        bishopStrategy.setCommand(command());
        return QList<QPoint>() << rookStrategy.availableMoves()
                               << bishopStrategy.availableMoves();
    }
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::King>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent)
        , m_moved(false)
        , m_castlingRookPoint(-1, -1) { setType(King); }

    QList<QPoint> availableMoves() override
    {
        if(!board())
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();
        QList<QPoint> points;

        int nextRow = row + 1;
        if(canMove(nextRow, column))
            points << QPoint(nextRow, column);

        nextRow = row - 1;
        if(canMove(nextRow, column))
            points << QPoint(nextRow, column);

        int nextCol = column + 1;
        if(canMove(row, nextCol))
            points << QPoint(row, nextCol);

        nextCol = column - 1;
        if(canMove(row, nextCol))
            points << QPoint(row, nextCol);

        nextRow = row - 1;
        nextCol = column - 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column - 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 1;
        if(canMove(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        points << checkCastlingPoints();

        for(QList<QPoint>::const_iterator it = points.cbegin(); points.cend() != it; ++it) {
            QPoint p = *it;
            Q_ASSERT(p.x() < 8 && p.x() >= 0 && p.x() < 8 && p.x() >= 0);
            Q_ASSERT(p.y() < 8 && p.y() >= 0 && p.y() < 8 && p.y() >= 0);
        }

        return points;
    }
    void finishMove() override
    {
        int row = rowIndex();
        int column = columnIndex();

        BasicPiece::finishMove();

        if(!m_moved && (row != rowIndex() || column != columnIndex()))
            m_moved = true;
    }
    bool moved() const
    {
        return m_moved;
    }
    bool needCastling()
    {
        if(columnIndex() == 2) {
            PieceStrategy<Rook> *leftRookCell = dynamic_cast<PieceStrategy<Rook> *>(board()->cell(rowIndex(), 0)->piece());
            if(leftRookCell != nullptr && !leftRookCell->moved()) {
                m_castlingRookPoint = QPoint(leftRookCell->rowIndex(), leftRookCell->columnIndex());
                return true;
            }
        }
        else if(columnIndex() == 6) {
            PieceStrategy<Rook> *rightRookCell = dynamic_cast<PieceStrategy<Rook> *>(board()->cell(rowIndex(), 7)->piece());
            if(rightRookCell != nullptr && !rightRookCell->moved()) {
                m_castlingRookPoint = QPoint(rightRookCell->rowIndex(), rightRookCell->columnIndex());
                return true;
            }
        }

        return false;
    }
    QPoint castlingRookPoint()
    {
        return m_castlingRookPoint;
    }

private:
    QList<QPoint> checkCastlingPoints()
    {
        if(m_moved)
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();

        bool hasRightCastling = false;
        bool hasLeftCastling = false;

        PieceStrategy<Rook> *rightRook = dynamic_cast<PieceStrategy<Rook> *>(board()->cell(row, 7)->piece());
        hasRightCastling = rightRook != nullptr && !rightRook->moved();

        PieceStrategy<Rook> *leftRook = dynamic_cast<PieceStrategy<Rook> *>(board()->cell(row, 0)->piece());
        hasLeftCastling = leftRook != nullptr && !leftRook->moved();

        QList<QPoint> points;

        if(hasRightCastling) {
            for(int i = column; i != column + 3; ++i) {
                if(board()->cell(row, i)->piece() != nullptr) {
                    hasRightCastling = false;
                    break;
                }
            }
        }

        if(hasLeftCastling) {
            for(int i = column; i != column - 4; --i) {
                if(board()->cell(row, i)->piece() != nullptr) {
                    hasLeftCastling = false;
                    break;
                }
            }
        }

        if(hasRightCastling)
            points << QPoint(row, column + 2);

        if(hasLeftCastling)
            points << QPoint(row, column - 2);

        return points;
    }

private:
    bool m_moved;
    QPoint m_castlingRookPoint;
};

template<>
class CHESSCORE_EXPORT PieceStrategy<BasicPiece::Pawn>
        : public BasicPiece
{
public:
    explicit PieceStrategy(QQuickItem *parent = nullptr)
        : BasicPiece(parent)
        , m_moved(false) { setType(Pawn); }

    QList<QPoint> availableMoves() override
    {
        if(!board())
            return QList<QPoint>();

        int row = rowIndex();
        int column = columnIndex();

        int moveSign = command() == BasicPiece::Black ? -1 : 1;
        if(board()->inverted())
            moveSign *= -1;

        QList<QPoint> points;

        int nextRow = row + moveSign;
        if(canMove(nextRow, column))
            points << QPoint(nextRow, column);

        int nextColumn = column + 1;
        if(canMove(nextRow, nextColumn))
            points << QPoint(nextRow, nextColumn);

        nextColumn = column - 1;
        if(canMove(nextRow, nextColumn))
            points << QPoint(nextRow, nextColumn);

        if(!m_moved) {
            nextRow = row + moveSign;
            int rowAfterNext = nextRow + moveSign;
            if(canMove(nextRow, column) && canMove(rowAfterNext, column))
                points << QPoint(rowAfterNext, column);
        }

        return points;
    }
    void finishMove() override
    {
        int row = rowIndex();
        int column = columnIndex();

        BasicPiece::finishMove();

        if(!m_moved && (row != rowIndex() || column != columnIndex()))
            m_moved = true;

        qDebug() << m_moved << row << rowIndex() << column << columnIndex();
    }

private:
    bool canMove(int row, int column) override
    {
        BasicGridCell *cell = board()->cell(row, column);
        if(!cell)
            return false;

        BasicPiece *piece = cell->piece();
        if(column == columnIndex() && !piece)
            return true;
        else if(column == columnIndex() + 1 && piece != nullptr && piece->command() != command())
            return true;
        else if(column == columnIndex() - 1 && piece != nullptr && piece->command() != command())
            return true;

        return false;
    }

private:
    bool m_moved;
};

#endif // PIECESTRATEGY_H
