#include "movechecker.h"

#include "../gui/basicpiece.h"
#include "../gui/basicboard.h"
#include "../gui/basicgridcell.h"

MoveChecker::MoveChecker(BasicBoard *board)
    : m_board(board)
{

}

MoveChecker::MoveDesctiption MoveChecker::rawDesctiption(BasicPiece *piece)
{
    MoveDesctiption description { piece, MovesDirectionHash() };
    switch (piece->type()) {
    case BasicPiece::King:
        kingRawMoves(description);
        break;
    case BasicPiece::Queen:
        queenRawMoves(description);
        break;
    case BasicPiece::Bishop:
        bishopRawMoves(description);
        break;
    case BasicPiece::Knight:
        knightRawMoves(description);
        break;
    case BasicPiece::Rook:
        rookRawMoves(description);
        break;
    case BasicPiece::Pawn:
        pawnRawMoves(description);
        break;
    default:
        return description;
    }

    return description;
}

Moves MoveChecker::filteredMoves(BasicPiece *piece)
{
    MoveDesctiption description = rawDesctiption(piece);
    switch (piece->type()) {
    case BasicPiece::King:
        kingFilter(description);
        break;
    case BasicPiece::Queen:
        queenFilter(description);
        break;
    case BasicPiece::Bishop:
        bishopFilter(description);
        break;
    case BasicPiece::Knight:
        knightFilter(description);
        break;
    case BasicPiece::Rook:
        rookFilter(description);
        break;
    case BasicPiece::Pawn:
        pawnFilter(description);
        break;
    default:
        return Moves();
    }

    Moves filteredMoves;
    for(auto moves : description.availableMoves)
        filteredMoves << moves;

    return filteredMoves;
}

void MoveChecker::kingFilter(MoveDesctiption &description)
{
//    MovesDirectionHash filteredMoves;
//    const MovesDirectionHash &availableMoves = description.availableMoves;
//    for(MovesDirectionHash::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
//        for(auto move : qAsConst(it.value())) {
//            int row = move.x();
//            int column = move.y();
//            if(m_board->cell(row, column)->piece() != nullptr)
//                continue;

//            filteredMoves[it.key()] << move;
//        }
//    }
//    description.availableMoves = filteredMoves;
}

void MoveChecker::queenFilter(MoveDesctiption &description)
{

}

void MoveChecker::bishopFilter(MoveDesctiption &description)
{    // Основной указатель на функцию сравнения
    bool(*compFunc)(const Move &next, const Move &prev) = nullptr;
    // функции сравнения в зависимости от направления обхода позиций
    // Подразумевается, что если функция вернет true, то next стоит после prev по направлению движения
    auto comp_top_left = [](const Move &prevY, const Move &nextY)->bool{ return false; };
    auto comp_top_right = [](const Move &prevX, const Move &nextX)->bool{ return false; };
    auto comp_bottom_left = [](const Move &prevY, const Move &nextY)->bool{ return false; };
    auto comp_bottom_right = [](const Move &prevX, const Move &nextX)->bool{ return false; };
    // функция получения следующей по возрастанию позиции
    auto get_next = [](const Move &prev,
                       const Move &max,
                       const Moves &moves,
                       bool(*compFunc)(const Move &next, const Move &prev))->Move
    {
        Move lastFoundVal = max;
        for(const Move &move : moves) {
            // ищем цепочку prev -> move -> lastFoundVal
            if(compFunc(prev, move) && compFunc(move, lastFoundVal))
                lastFoundVal = move;
        }
        return lastFoundVal;
    };

    MovesDirectionHash filteredMoves;
    const MovesDirectionHash &availableMoves = description.availableMoves;
    for(MovesDirectionHash::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
        // Заранее знаем, что направление только Top, Left, Right, Bottom. Выбираем функцию сравнения
        switch (it.key()) {
        case Direction::TopLeft:
            compFunc = comp_top_left;
            break;
        case Direction::TopRight:
            compFunc = comp_top_right;
            break;
        case Direction::BottomLeft:
            compFunc = comp_bottom_left;
            break;
        case Direction::BottomRight:
            compFunc = comp_bottom_right;
            break;
        default:
            // Нет доступных ходов для данного направления
            continue;
        }


        Move minValue = Move(description.initiator->rowIndex(), description.initiator->columnIndex());
        Move maxValue = *std::max_element(it->begin(), it->end(), compFunc);
        while(true) {
            // Следующее значение в порядке обхода по данному направлению
            Move nextValue = get_next(minValue, maxValue, it.value(), compFunc);
            if(m_board->cell(nextValue.x(), nextValue.y())->piece() != nullptr)
                break;
            else
                filteredMoves[it.key()] << nextValue;

            minValue = nextValue;
            if(nextValue == maxValue)
                break;
        }
    }
    description.availableMoves = filteredMoves;
}

void MoveChecker::knightFilter(MoveDesctiption &description)
{
//    MovesDirectionHash filteredMoves;
//    const MovesDirectionHash &availableMoves = description.availableMoves;
//    for(MovesDirectionHash::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
//        for(auto move : qAsConst(it.value())) {
//            int row = move.x();
//            int column = move.y();
//            if(m_board->cell(row, column)->piece() != nullptr)
//                continue;

//            filteredMoves[it.key()] << move;
//        }
//    }
//    description.availableMoves = filteredMoves;
}

void MoveChecker::rookFilter(MoveDesctiption &description)
{
    // Основной указатель на функцию сравнения
    bool(*compFunc)(const Move &next, const Move &prev) = nullptr;
    // функции сравнения в зависимости от направления обхода позиций
    // Подразумевается, что если функция вернет true, то next стоит после prev по направлению движения
    auto comp_top = [](const Move &prevY, const Move &nextY)->bool{ return prevY.y() > nextY.y(); };
    auto comp_left = [](const Move &prevX, const Move &nextX)->bool{ return prevX.x() > nextX.x(); };
    auto comp_bottom = [](const Move &prevY, const Move &nextY)->bool{ return prevY.y() < nextY.y(); };
    auto comp_right = [](const Move &prevX, const Move &nextX)->bool{ return prevX.x() < nextX.x(); };
    // функция получения следующей по возрастанию позиции
    auto get_next = [](const Move &prev,
                       const Move &max,
                       const Moves &moves,
                       bool(*compFunc)(const Move &next, const Move &prev))->Move
    {
        Move lastFoundVal = max;
        for(const Move &move : moves) {
            // ищем цепочку prev -> move -> lastFoundVal
            if(compFunc(prev, move) && compFunc(move, lastFoundVal))
                lastFoundVal = move;
        }
        return lastFoundVal;
    };

    MovesDirectionHash filteredMoves;
    const MovesDirectionHash &availableMoves = description.availableMoves;
    for(MovesDirectionHash::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
        // Заранее знаем, что направление только Top, Left, Right, Bottom. Выбираем функцию сравнения
        switch (it.key()) {
        case Direction::Top:
            compFunc = comp_top;
            break;
        case Direction::Bottom:
            compFunc = comp_bottom;
            break;
        case Direction::Left:
            compFunc = comp_left;
            break;
        case Direction::Right:
            compFunc = comp_right;
            break;
        default:
            // Нет доступных ходов для данного направления
            continue;
        }


        Move minValue = Move(description.initiator->rowIndex(), description.initiator->columnIndex());
        Move maxValue = *std::max_element(it->begin(), it->end(), compFunc);
        while(true) {
            // Следующее значение в порядке обхода по данному направлению
            Move nextValue = get_next(minValue, maxValue, it.value(), compFunc);
            if(m_board->cell(nextValue.x(), nextValue.y())->piece() != nullptr)
                break;
            else
                filteredMoves[it.key()] << nextValue;

            minValue = nextValue;
            if(nextValue == maxValue)
                break;
        }
    }
    description.availableMoves = filteredMoves;
}

void MoveChecker::pawnFilter(MoveDesctiption &description)
{
//    Moves filteredMoves;
//    int direction = description.initiator->command();
//    int centerRow = direction > 0 ? 4 : 3;
//    for(const QPoint &move : qAsConst(description.availableMoves)) {
//        int row = move.x();
//        int column = move.y();

//        if(row == description.initiator->rowIndex() + direction) {
//            // Правый противник
//            column += 1;
//            if(column < 8 && m_board->cell(row, column)->piece() != nullptr)
//                filteredMoves << QPoint(row, column);

//            // Левый противник
//            column -= 2;
//            if(column >= 0 && m_board->cell(row, column)->piece() != nullptr)
//                filteredMoves << QPoint(row, column);

//            column = move.y();
//        }

//        // Противник на против
//        if(m_board->cell(row, column)->piece() != nullptr)
//            break;

//        // Центр доски
//        if(row * direction < centerRow * direction)
//            filteredMoves << move << QPoint(row + direction, column);
//        else
//            filteredMoves << move;
//        break;
//    }

//    description.availableMoves = filteredMoves;
}

void MoveChecker::kingRawMoves(MoveDesctiption &description)
{
//    int row = description.initiator->xIndex();
//    int column = description.initiator->yIndex();
//    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));

//    // Top left
//    int tempRow = row - 1;
//    int tempCol = column - 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::TopLeft] << Move(tempRow, tempCol);

//    // Top
//    tempRow = row - 1;
//    tempCol = column;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::Top] << Move(tempRow, tempCol);

//    // Top right
//    tempRow = row - 1;
//    tempCol = column + 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::TopRight] << Move(tempRow, tempCol);

//    // Right
//    tempRow = row;
//    tempCol = column + 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::Right] << Move(tempRow, tempCol);

//    // Bottom right
//    tempRow = row + 1;
//    tempCol = column + 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::BottomRight] << Move(tempRow, tempCol);

//    // Bottom
//    tempRow = row + 1;
//    tempCol = column;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::Bottom] << Move(tempRow, tempCol);

//    // Bottom Left
//    tempRow = row + 1;
//    tempCol = column - 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::BottomLeft] << Move(tempRow, tempCol);

//    // Left
//    tempRow = row;
//    tempCol = column - 1;
//    if(tempRow < 8 && tempRow >= 0)
//        description.availableMoves[Direction::Left] << Move(tempRow, tempCol);
}

void MoveChecker::queenRawMoves(MoveDesctiption &description)
{
//    int row = description.initiator->xIndex();
//    int column = description.initiator->yIndex();
//    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));
//    rookRawMoves(description);
//    bishopRawMoves(description);
}

void MoveChecker::bishopRawMoves(MoveDesctiption &description)
{
    int row = description.initiator->rowIndex();
    int column = description.initiator->columnIndex();
    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);

    // По диагонали в нижний лувый угол
    for(int r = row - 1, c = column + 1; r >= 0 && c < 8; --r, ++c)
        description.availableMoves[Direction::BottomLeft] << Move(r, c);

    // По диагонали в нижний правый угол
    for(int r = row + 1, c = column + 1; r < 8 && c < 8; ++r, ++c)
        description.availableMoves[Direction::BottomRight] << Move(r, c);

    // По диагонали в верхний правый угол
    for(int r = row + 1, c = column - 1; r < 8 && c >= 0; ++r, --c)
        description.availableMoves[Direction::TopRight] << Move(r, c);

    // По диагонали в верхний левый угол
    for(int r = row - 1, c = column - 1; r >= 0 && c >= 0; --r, --c)
        description.availableMoves[Direction::TopLeft] << Move(r, c);
}

void MoveChecker::knightRawMoves(MoveDesctiption &description)
{
//    int row = description.initiator->xIndex();
//    int column = description.initiator->yIndex();
//    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));

//    // Левый верхний угол
//    int tempRow = row - 1;
//    int tempCol = column - 2;
//    if(tempRow >= 0 && tempCol >= 0)
//        description.availableMoves[Direction::TopLeft] << QPoint(tempRow, tempCol);

//    tempRow = row - 2;
//    tempCol = column - 1;
//    if(tempRow >= 0 && tempCol >= 0)
//        description.availableMoves[Direction::TopLeft] << QPoint(tempRow, tempCol);

//    // Правый верхний угол
//    tempRow = row - 1;
//    tempCol = column + 2;
//    if(tempRow >= 0 && tempCol < 8)
//        description.availableMoves[Direction::TopRight] << QPoint(tempRow, tempCol);

//    tempRow = row - 2;
//    tempCol = column + 1;
//    if(tempRow >= 0 && tempCol < 8)
//        description.availableMoves[Direction::TopRight] << QPoint(tempRow, tempCol);

//    // Правый нижний угол
//    tempRow = row + 1;
//    tempCol = column + 2;
//    if(tempRow < 8 && tempCol < 8)
//        description.availableMoves[Direction::BottomRight] << QPoint(tempRow, tempCol);

//    tempRow = row + 2;
//    tempCol = column + 1;
//    if(tempRow < 8 && tempCol < 8)
//        description.availableMoves[Direction::BottomRight] << QPoint(tempRow, tempCol);

//    // Левый нижний угол
//    tempRow = row + 1;
//    tempCol = column - 2;
//    if(tempRow < 8 && tempCol >= 0)
//        description.availableMoves[Direction::BottomLeft] << QPoint(tempRow, tempCol);

//    tempRow = row + 2;
//    tempCol = column - 1;
//    if(tempRow < 8 && tempCol >= 0)
//        description.availableMoves[Direction::BottomLeft] << QPoint(tempRow, tempCol);
}

void MoveChecker::rookRawMoves(MoveDesctiption &description)
{
    int row = description.initiator->rowIndex();
    int column = description.initiator->columnIndex();
    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);
    {
        // Вправо
        int tempRow = row + 1;
        while(tempRow < 8)
            description.availableMoves[Direction::Right] << Move(tempRow++, column);

        // Влево
        tempRow = row - 1;
        while(tempRow >= 0)
            description.availableMoves[Direction::Left] << Move(tempRow--, column);
    }
    {
        // Вверх
        int tempCol = column + 1;
        while(tempCol < 8)
            description.availableMoves[Direction::Bottom] << Move(row, tempCol++);

        // Вниз
        tempCol = column - 1;
        while(tempCol >= 0)
            description.availableMoves[Direction::Top] << Move(row, tempCol--);
    }
}

void MoveChecker::pawnRawMoves(MoveDesctiption &description)
{
    int row = description.initiator->rowIndex();
    int column = description.initiator->columnIndex();
    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);
    int direction = description.initiator->command();
    if(m_board->inverted())
        direction *= -1;

    Moves moves;
    int tempRow = row + direction;
    auto atEndFunc = [&](int row) { return direction < 0 ? row < 0 : row >= 8; };
    while(!atEndFunc(tempRow)) {
        moves << Move(tempRow, column);
        tempRow += direction;
    }

    Direction currentDirection = direction > 0 ? MoveDesctiption::Bottom : MoveDesctiption::Top;
    description.availableMoves[currentDirection] << moves;
}
