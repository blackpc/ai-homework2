/**
 * Filename: GoGame.h
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

#ifndef INCLUDE_AI_HOMEWORK2_GOGAME_H_
#define INCLUDE_AI_HOMEWORK2_GOGAME_H_


#include <set>

#include <ai-homework2/Board.h>


using namespace std;


/*
 * Go game
 */
class GoGame {

public:

    /**
     * Represents whose turn
     */
    enum Turn {
        TurnBlack,
        TurnWhite
    };

public:

    /**
     * Initializes the game with specified board and turn ownership
     * @param board
     * @param turn
     */
	GoGame(const Board& board, Turn turn = GoGame::TurnBlack);

public:

	/**
	 * Gets the game board
	 * @return
	 */
	inline const Board& getBoard() const {
	    return board_;
	}

	/**
	 * Returns whose the turn
	 * @return
	 */
	inline Turn getTurn() const {
	    return turn_;
	}

	/**
	 * Converts turn enum to @see Board::Cell enum
	 * @param turn
	 * @return
	 */
	inline Board::Cell turnToCell(Turn turn) const;

	/**
	 * Returns all available moves for current player
	 * @return
	 */
	set<Board::CellPoint> getAvailableMoves() const;

private:

	Turn turn_;
	Board board_;

};

#endif /* INCLUDE_AI_HOMEWORK2_GOGAME_H_ */
