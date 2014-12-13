/**
 * Filename: GoGame.cpp
 *   Author: Igor Makhtes
 *     Date: Dec 12, 2014
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <ai-homework2/GoGame.h>


GoGame::GoGame(const Board& board, Turn turn)
    : board_(board) {
    turn_ = turn;
}


bool GoGame::isFinished() const {
    return board_.getEmptyCellsCount() == 0;
}

string GoGame::getWinner() const {
    if (isFinished()) {
        if (board_.getBlackCellsCount() > board_.getWhiteCellsCount())
            return "B";

        return "W";
    }

    return "";
}

GoGame::Turn GoGame::switchTurn(GoGame::Turn turn) const {
    if (turn == GoGame::TurnBlack) {
        return GoGame::TurnWhite;
    } else {
        return GoGame::TurnBlack;
    }
}

Board::Cell GoGame::turnToCell(Turn turn) const {
    if (turn == GoGame::TurnBlack)
        return Board::CellBlack;

    if (turn == GoGame::TurnWhite)
        return Board::CellWhite;

    throw new string("Illegal turn type");
}

set<Board::CellPoint> GoGame::getAvailableMoves() const {
    set<Board::CellPoint> moves;

    for (int32_t y = 0; y < board_.getHeight(); ++y) {
        for (int32_t x = 0; x < board_.getWidth(); ++x) {
            const Board::Cell& cell = board_.getCell(x, y);

            if (cell != Board::CellEmpty) {
                // Check all 4 neighbors
                // If empty, add to the list
                if (board_.isInBounds(x + 1, y) && board_.isEmpty(x + 1, y))
                    moves.insert(Board::CellPoint(x + 1, y, turnToCell(turn_)));

                if (board_.isInBounds(x - 1, y) && board_.isEmpty(x - 1, y))
                    moves.insert(Board::CellPoint(x - 1, y, turnToCell(turn_)));

                if (board_.isInBounds(x, y + 1) && board_.isEmpty(x, y + 1))
                    moves.insert(Board::CellPoint(x, y + 1, turnToCell(turn_)));

                if (board_.isInBounds(x, y - 1) && board_.isEmpty(x, y - 1))
                    moves.insert(Board::CellPoint(x, y - 1, turnToCell(turn_)));
            }
        }
    }

    return moves;
}

void GoGame::switchCapturedCells(const Board::Point& point, Turn turn) {
    // Search for captured cells in all 4 directions

    switchCapturedCellsRecursive(Board::Point(point.x + 1, point.y), turn, 1, 0);
    switchCapturedCellsRecursive(Board::Point(point.x - 1, point.y), turn, -1, 0);
    switchCapturedCellsRecursive(Board::Point(point.x, point.y + 1), turn, 0, 1);
    switchCapturedCellsRecursive(Board::Point(point.x, point.y - 1), turn, 0, -1);
}

bool GoGame::switchCapturedCellsRecursive(const Board::Point& point, Turn turn,
        int8_t xIncrement, int8_t yIncrement) {

    Board::Point nextPoint(point.x + xIncrement, point.y + yIncrement);

    // Iterates current direction until there is turn owner's cells
    // if current cell is empty, return false - capturing cell not found
    // if current cell is turn owner's cell, then return true

    if (board_.isEmpty(point) || !board_.isInBounds(point))
        return false;

    if (board_.getCell(point) == turnToCell(turn))
        return true;

    // If not empty cell and not turn owner's cell, then
    // it's opponent's cell, so we must continue the search
    bool capturingCellFound = switchCapturedCellsRecursive(nextPoint, turn, xIncrement, yIncrement);

    if (capturingCellFound) {
        if (board_.getCell(point) == turnToCell(switchTurn(turn)))
            board_.setCell(point, turnToCell(turn));
    }

    return capturingCellFound;
}

bool GoGame::isLegalMove(int32_t x, int32_t y) const {

    // The cell must be empty
    if (!board_.isEmpty(x, y))
        return false;

    return true;
}

bool GoGame::isLegalMove(const Board::Point& point) const {
    return isLegalMove(point.x, point.y);
}

void GoGame::makeMove(int32_t x, int32_t y) {
    makeMove(Board::Point(x, y));
}

void GoGame::makeMove(const Board::Point& point) {

    if (isFinished())
        throw new string("Can't make a move, ths game is finished");

    if (!isLegalMove(point))
        throw new string("Illegal move, target cell is not empty");

    board_.setCell(point, turnToCell(turn_));

    switchCapturedCells(point, turn_);

    turn_ = switchTurn(turn_);
}

GoGame GoGame::simulateMove(int32_t x, int32_t y) const {
    GoGame clonedGame = GoGame(*this);
    clonedGame.makeMove(x, y);
    return clonedGame;
}

GoGame GoGame::simulateMove(const Board::Point& point) const {
    return simulateMove(point.x, point.y);
}

