#include "movechecker.h"
#include "basicpiece.h"

// Функции вынесены из класса, чтобы была возможность специализации шаблонов
namespace PieceStrategy
{
typedef QPoint Move;
typedef QList<Move> Moves;

// Не определяется, чтобы получить ошибку компиляции при использовании неверных типов фигур
template<BasicPiece::Type>
Moves CHESSCORE_EXPORT availableMoves(int row, int column);

template<>
Moves CHESSCORE_EXPORT availableMoves<BasicPiece::King>(int row, int column)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    Moves moves;
    for(int r = row - 1, rCheck = 0; r < row + 1; ++r, ++rCheck) {
        for(int c = column - 1, cCheck = 0; c < column + 1; ++c, ++cCheck) {
            if(rCheck == cCheck)
                continue;

            if(r >= 8 || r < 0)
                continue;

            if(c >= 8 || c < 0)
                continue;

            moves << Move(r, c);
        }
    }

    return moves;
}

template<>
Moves CHESSCORE_EXPORT availableMoves<BasicPiece::Knight>(int row, int column)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    Moves moves;

    // Левый верхний угол
    int tempRow = row - 1;
    int tempCol = column - 2;
    if(tempRow >= 0 && tempCol >= 0)
        moves << Move(tempRow, tempCol);

    tempRow = row - 2;
    tempCol = column - 1;
    if(tempRow >= 0 && tempCol >= 0)
        moves << Move(tempRow, tempCol);

    // Правый верхний угол
    tempRow = row - 1;
    tempCol = column + 2;
    if(tempRow >= 0 && tempCol < 8)
        moves << Move(tempRow, tempCol);

    tempRow = row - 2;
    tempCol = column + 1;
    if(tempRow >= 0 && tempCol < 8)
        moves << Move(tempRow, tempCol);

    // Правый нижний угол
    tempRow = row + 1;
    tempCol = column + 2;
    if(tempRow < 8 && tempCol < 8)
        moves << Move(tempRow, tempCol);

    tempRow = row + 2;
    tempCol = column + 1;
    if(tempRow < 8 && tempCol < 8)
        moves << Move(tempRow, tempCol);

    // Левый нижний угол
    tempRow = row + 1;
    tempCol = column - 2;
    if(tempRow < 8 && tempCol >= 0)
        moves << Move(tempRow, tempCol);

    tempRow = row + 2;
    tempCol = column - 1;
    if(tempRow < 8 && tempCol >= 0)
        moves << Move(tempRow, tempCol);

    return moves;
}

template<>
Moves CHESSCORE_EXPORT availableMoves<BasicPiece::Bishop>(int row, int column)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    Moves moves;
    // По диагонали в правый верхний угол
    for(int r = row - 1, c = column + 1; r >= 0 && c < 8; --r, ++c)
        moves << Move(r, c);

    // По диагонали в правый нижний угол
    for(int r = row + 1, c = column + 1; r < 8 && c < 8; ++r, ++c)
        moves << Move(r, c);

    // По диагонали в левый нижний угол
    for(int r = row + 1, c = column - 1; r < 8 && c >= 0; ++r, --c)
        moves << Move(r, c);

    // По диагонали в левый верхний угол
    for(int r = row - 1, c = column - 1; r >= 0 && c >= 0; --r, --c)
        moves << Move(r, c);

    return moves;
}

template<>
Moves CHESSCORE_EXPORT availableMoves<BasicPiece::Rook>(int row, int column)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    Moves moves;
    {
        // Вниз
        int tempRow = row + 1;
        while(tempRow < 8)
            moves << Move(tempRow, column);

        // Вверх
        tempRow = row - 1;
        while(tempRow >= 0)
            moves << Move(tempRow, column);
    }
    {
        // Вправо
        int tempCol = column + 1;
        while(tempCol < 8)
            moves << Move(row, tempCol);

        // Влево
        tempCol = column - 1;
        while(tempCol >= 0)
            moves << Move(row, tempCol);
    }

    return moves;
}

template<>
Moves CHESSCORE_EXPORT availableMoves<BasicPiece::Queen>(int row, int column)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    Moves rookMoves = availableMoves<BasicPiece::Rook>(row, column);
    Moves bishopMoves = availableMoves<BasicPiece::Bishop>(row, column);
    return Moves() << rookMoves << bishopMoves;
}

// У пешки логика движения зависит от команды,
// поэтому не специализируем ее, а делаем отдельную функцию
Moves CHESSCORE_EXPORT pawnMoves(int row, int column, BasicPiece::Command command, bool boardInverted)
{
    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
    int direction = command;
    if(boardInverted)
        direction *= -1;

    Moves moves;
    int tempRow = row + direction;
    auto atEndFunc = [&](int row) { return direction < 0 ? row < 0 : row >= 8; };
    while(!atEndFunc(tempRow)) {
        moves << Move(tempRow, column);
        tempRow += direction;
    }

    return moves;
}

};

#include "basicboard.h"
#include "basicgridcell.h"

MoveChecker::MoveChecker(BasicBoard *board)
    : m_board(board)
{

}

QList<QPoint> MoveChecker::rawMoves(BasicPiece *piece)
{
    QList<QPoint> rawMoves;
    switch (piece->type()) {
    case BasicPiece::King:
        rawMoves = PieceStrategy::availableMoves<BasicPiece::King>(piece->rowIndex(), piece->columnIndex());
        break;
    case BasicPiece::Queen:
        rawMoves = PieceStrategy::availableMoves<BasicPiece::Queen>(piece->rowIndex(), piece->columnIndex());
        break;
    case BasicPiece::Bishop:
        rawMoves = PieceStrategy::availableMoves<BasicPiece::Bishop>(piece->rowIndex(), piece->columnIndex());
        break;
    case BasicPiece::Knight:
        rawMoves = PieceStrategy::availableMoves<BasicPiece::Knight>(piece->rowIndex(), piece->columnIndex());
        break;
    case BasicPiece::Rook:
        rawMoves = PieceStrategy::availableMoves<BasicPiece::Rook>(piece->rowIndex(), piece->columnIndex());
        break;
    case BasicPiece::Pawn:
        rawMoves = PieceStrategy::pawnMoves(piece->rowIndex(), piece->columnIndex(), piece->command(), m_board->inverted());
        break;
    default:
        return QList<QPoint>();
    }

    return rawMoves;
}

QList<QPoint> MoveChecker::filterMoves(const QList<QPoint> &rawMoves, BasicPiece *piece)
{
    switch (piece->type()) {
    case BasicPiece::King:
        return kingFilter(piece, rawMoves);
    case BasicPiece::Queen:
        return queenFilter(piece, rawMoves);
    case BasicPiece::Bishop:
        return bishopFilter(piece, rawMoves);
    case BasicPiece::Knight:
        return knightFilter(piece, rawMoves);
    case BasicPiece::Rook:
        return rookFilter(piece, rawMoves);
    case BasicPiece::Pawn:
        return pawnFilter(piece, rawMoves);
    default:
        return QList<QPoint>();
    }

    return QList<QPoint>();
}

QList<QPoint> MoveChecker::kingFilter(BasicPiece *king, const QList<QPoint> &rawMoves)
{
    return rawMoves;
}

QList<QPoint> MoveChecker::queenFilter(BasicPiece *queen, const QList<QPoint> &rawMoves)
{
    return rawMoves;
}

QList<QPoint> MoveChecker::bishopFilter(BasicPiece *bishop, const QList<QPoint> &rawMoves)
{
    return rawMoves;
}

QList<QPoint> MoveChecker::knightFilter(BasicPiece *knight, const QList<QPoint> &rawMoves)
{
    return rawMoves;
}

QList<QPoint> MoveChecker::rookFilter(BasicPiece *rook, const QList<QPoint> &rawMoves)
{
    return rawMoves;
}

QList<QPoint> MoveChecker::pawnFilter(BasicPiece *pawn, const QList<QPoint> &rawMoves)
{
    QList<QPoint> filteredMoves;
    int direction = pawn->command();
    for(const QPoint &move : rawMoves) {
        int row = move.x();
        int column = move.y();

        if(row == pawn->rowIndex() + direction) {
            // Правый противник
            column += 1;
            if(column < 8 && m_board->cell(row, column)->piece() != nullptr)
                filteredMoves << QPoint(row, column);

            // Левый противник
            column -= 2;
            if(column >= 0 && m_board->cell(row, column)->piece() != nullptr)
                filteredMoves << QPoint(row, column);

            column = move.y();
        }

        // Противник на против
        if(m_board->cell(row, column)->piece() != nullptr)
            break;

        filteredMoves << move;
    }

    return filteredMoves;
}
