#ifndef PIECESTRATEGY_H
#define PIECESTRATEGY_H

#include "basicpiece.h"
#include "basicboard.h"
#include "basicgridcell.h"
#include "chesscore_global.h"

template<typename BasicPiece::Type, typename BasicPiece::Command>
struct CHESSCORE_EXPORT PieceStrategy
{    
    PieceStrategy(BasicBoard *) {}
    QList<QPoint> availableMoves(int, int) { return QList<QPoint>(); }
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::King, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        int nextRow = row + 1;
        if(nextRow < 8 && !sameCommandPiece(nextRow, column))
            points << QPoint(nextRow, column);

        nextRow = row - 1;
        if(nextRow >= 0 && !sameCommandPiece(nextRow, column))
            points << QPoint(nextRow, column);

        int nextCol = column + 1;
        if(nextCol < 8 && !sameCommandPiece(row, nextCol))
            points << QPoint(row, nextCol);

        nextCol = column - 1;
        if(nextCol >= 0 && !sameCommandPiece(row, nextCol))
            points << QPoint(row, nextCol);

        nextRow = row - 1;
        nextCol = column - 1;
        if(nextCol >= 0 && nextRow >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column - 1;
        if(nextCol >= 0 && nextRow < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 1;
        if(nextCol < 8 && nextRow >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 1;
        if(nextCol < 8 && nextRow < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::White
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        for(int i = row, j = column; i < 7 && j < 7 && !sameCommandPiece(i + 1, j + 1); ++i, ++j) {
            points << QPoint(i + 1, j + 1);
            if(m_board->cell(i + 1, j + 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i < 7 && j > 0 && !sameCommandPiece(i + 1, j - 1); ++i, --j) {
            points << QPoint(i + 1, j - 1);
            if(m_board->cell(i + 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i > 0 && j > 0 && !sameCommandPiece(i - 1, j - 1); --i, --j) {
            points << QPoint(i - 1, j - 1);
            if(m_board->cell(i - 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i > 0 && j < 7 && !sameCommandPiece(i - 1, j + 1); --i, ++j) {
            points << QPoint(i - 1, j + 1);
            if(m_board->cell(i - 1, j + 1)->piece() != nullptr)
                break;
        }
        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::White
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Knight, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board){}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        int nextRow = row + 2;
        int nextCol = column + 1;
        if(nextRow < 8 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 2;
        if(nextRow < 8 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 2;
        if(nextRow >= 0 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column + 1;
        if(nextRow >= 0 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column - 1;
        if(nextRow >= 0 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column - 2;
        if(nextRow >= 0 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column +-2;
        if(nextRow < 8 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 2;
        nextCol = column - 1;
        if(nextRow < 8 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::White
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        for(int i = row; i < 7 && !sameCommandPiece(i + 1, column); ++i) {
            points << QPoint(i + 1, column);
            if(m_board->cell(i + 1, column)->piece() != nullptr)
                break;
        }

        for(int i = row; i > 0 && !sameCommandPiece(i - 1, column); --i) {
            points << QPoint(i - 1, column);
            if(m_board->cell(i - 1, column)->piece() != nullptr)
                break;
        }

        for(int i = column; i > 0 && !sameCommandPiece(row, i - 1); --i) {
            points << QPoint(row, i - 1);
            if(m_board->cell(row, i - 1)->piece() != nullptr)
                break;
        }

        for(int i = column; i < 7 && !sameCommandPiece(row, i + 1); ++i) {
            points << QPoint(row, i + 1);
            if(m_board->cell(row, i + 1)->piece() != nullptr)
                break;
        }

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::White
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Queen, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::White> rookStrategy(m_board);
        PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::White> bishopStrategy(m_board);
        return QList<QPoint>() << rookStrategy.availableMoves(row, column)
                               << bishopStrategy.availableMoves(row, column);
    }
private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Pawn, BasicPiece::Command::White>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        int rowSign = m_board->inverted() ? 1 : -1;
        QList<QPoint> points;
        BasicGridCell *frontCell = m_board->cell(row - rowSign, column);
        if(frontCell != nullptr && frontCell->piece() == nullptr)
            points << QPoint(row - rowSign, column);

        BasicGridCell *leftCell = m_board->cell(row - rowSign, column - 1);
        if(leftCell != nullptr && leftCell->piece() != nullptr
                && leftCell->piece()->command() == BasicPiece::Command::Black && !isKing(leftCell))
            points << QPoint(row - rowSign, column - 1);

        BasicGridCell *rightCell = m_board->cell(row - rowSign, column + 1);
        if(rightCell != nullptr &&rightCell->piece() != nullptr
                && rightCell->piece()->command() == BasicPiece::Command::Black && !isKing(rightCell))
            points << QPoint(row - rowSign, column + 1);

        return points;
    }

private:
    bool isKing(BasicGridCell *cell)
    {
        return cell != nullptr && cell->piece() != nullptr && cell->piece()->type() == BasicPiece::Type::King;
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::King, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        int nextRow = row + 1;
        if(nextRow < 8 && !sameCommandPiece(nextRow, column))
            points << QPoint(nextRow, column);

        nextRow = row - 1;
        if(nextRow >= 0 && !sameCommandPiece(nextRow, column))
            points << QPoint(nextRow, column);

        int nextCol = column + 1;
        if(nextCol < 8 && !sameCommandPiece(row, nextCol))
            points << QPoint(row, nextCol);

        nextCol = column - 1;
        if(nextCol >= 0 && !sameCommandPiece(row, nextCol))
            points << QPoint(row, nextCol);

        nextRow = row - 1;
        nextCol = column - 1;
        if(nextCol >= 0 && nextRow >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column - 1;
        if(nextCol >= 0 && nextRow < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 1;
        if(nextCol < 8 && nextRow >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 1;
        if(nextCol < 8 && nextRow < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::Black
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        for(int i = row, j = column; i < 7 && j < 7 && !sameCommandPiece(i + 1, j + 1); ++i, ++j) {
            points << QPoint(i + 1, j + 1);
            if(m_board->cell(i + 1, j + 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i < 7 && j > 0 && !sameCommandPiece(i + 1, j - 1); ++i, --j) {
            points << QPoint(i + 1, j - 1);
            if(m_board->cell(i + 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i > 0 && j > 0 && !sameCommandPiece(i - 1, j - 1); --i, --j) {
            points << QPoint(i - 1, j - 1);
            if(m_board->cell(i - 1, j - 1)->piece() != nullptr)
                break;
        }

        for(int i = row, j = column; i > 0 && j < 7 && !sameCommandPiece(i - 1, j + 1); --i, ++j) {
            points << QPoint(i - 1, j + 1);
            if(m_board->cell(i - 1, j + 1)->piece() != nullptr)
                break;
        }

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::Black
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Knight, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board){}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        int nextRow = row + 2;
        int nextCol = column + 1;
        if(nextRow < 8 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column + 2;
        if(nextRow < 8 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column + 2;
        if(nextRow >= 0 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column + 1;
        if(nextRow >= 0 && nextCol < 8 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 2;
        nextCol = column - 1;
        if(nextRow >= 0 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row - 1;
        nextCol = column - 2;
        if(nextRow >= 0 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 1;
        nextCol = column +-2;
        if(nextRow < 8 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        nextRow = row + 2;
        nextCol = column - 1;
        if(nextRow < 8 && nextCol >= 0 && !sameCommandPiece(nextRow, nextCol))
            points << QPoint(nextRow, nextCol);

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::Black
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        QList<QPoint> points;
        for(int i = row; i < 7 && !sameCommandPiece(i + 1, column); ++i) {
            points << QPoint(i + 1, column);
            if(m_board->cell(i + 1, column)->piece() != nullptr)
                break;
        }

        for(int i = row; i > 0 && !sameCommandPiece(i - 1, column); --i) {
            points << QPoint(i - 1, column);
            if(m_board->cell(i - 1, column)->piece() != nullptr)
                break;
        }

        for(int i = column; i > 0 && !sameCommandPiece(row, i - 1); --i) {
            points << QPoint(row, i - 1);
            if(m_board->cell(row, i - 1)->piece() != nullptr)
                break;
        }

        for(int i = column; i < 7 && !sameCommandPiece(row, i + 1); ++i) {
            points << QPoint(row, i + 1);
            if(m_board->cell(row, i + 1)->piece() != nullptr)
                break;
        }

        return points;
    }

private:
    bool sameCommandPiece(int row, int column)
    {
        BasicGridCell *cell = m_board->cell(row, column);
        return cell->piece() != nullptr && (cell->piece()->command() == BasicPiece::Command::Black
                || cell->piece()->type() == BasicPiece::Type::King);
    }

private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Queen, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        PieceStrategy<BasicPiece::Type::Rook, BasicPiece::Command::Black> rookStrategy(m_board);
        PieceStrategy<BasicPiece::Type::Bishop, BasicPiece::Command::Black> bishopStrategy(m_board);
        return QList<QPoint>() << rookStrategy.availableMoves(row, column)
                               << bishopStrategy.availableMoves(row, column);
    }
private:
    BasicBoard *m_board;
};

template<>
struct CHESSCORE_EXPORT PieceStrategy<BasicPiece::Type::Pawn, BasicPiece::Command::Black>
{
    PieceStrategy(BasicBoard *board)
        : m_board(board) {}
    QList<QPoint> availableMoves(int row, int column)
    {
        int rowSign = m_board->inverted() ? -1 : 1;
        QList<QPoint> points;
        BasicGridCell *frontCell = m_board->cell(row - rowSign, column);
        if(frontCell != nullptr && frontCell->piece() == nullptr)
            points << QPoint(row - rowSign, column);

        BasicGridCell *leftCell = m_board->cell(row - rowSign, column - 1);
        if(leftCell != nullptr && leftCell->piece() != nullptr
                && leftCell->piece()->command() == BasicPiece::Command::White && !isKing(leftCell))
            points << QPoint(row - rowSign, column - 1);

        BasicGridCell *rightCell = m_board->cell(row - rowSign, column + 1);
        if(rightCell != nullptr && rightCell->piece() != nullptr
                && rightCell->piece()->command() == BasicPiece::Command::White && !isKing(rightCell))
            points << QPoint(row - rowSign, column + 1);

        return points;
    }

private:
    bool isKing(BasicGridCell *cell)
    {
        return cell != nullptr && cell->piece() != nullptr && cell->piece()->type() == BasicPiece::Type::King;
    }

private:
    BasicBoard *m_board;
};


#endif // PIECESTRATEGY_H
