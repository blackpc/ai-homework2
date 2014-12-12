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

inline Board::Cell GoGame::turnToCell(Turn turn) const {
    if (turn == GoGame::TurnBlack)
        return Board::CellBlack;

    if (turn == GoGame::TurnWhite)
        return Board::CellWhite;

    throw new string("Illegal turn type");
}

set<Board::CellPoint> GoGame::getAvailableMoves() const {
    set<Board::CellPoint> moves;

    for (uint8_t y = 0; y < board_.getHeight(); ++y) {
        for (uint8_t x = 0; x < board_.getWidth(); ++x) {
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
