/**
 * Filename: Board.h
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

#ifndef INCLUDE_AI_HOMEWORK2_BOARD_H_
#define INCLUDE_AI_HOMEWORK2_BOARD_H_


#include <iostream>
#include <vector>
#include <inttypes.h>


using namespace std;


/**
 * Represents a game board of arbitrary size
 */
class Board {

public:

    /**
     * The value of a cell
     */
    enum Cell {
        CellBlack,//!< CellBlack
        CellWhite,//!< CellWhite
        CellFree  //!< CellFree
    };

    /**
     * Represents x-y integer coordinates
     */
    struct Point {
        uint8_t x;
        uint8_t y;

        Point() : x(0), y(0) { }

        Point(uint8_t x, uint8_t y) {
            this->x = x;
            this->y = y;
        }
    };

    /**
     * Cell with coordinates
     */
    struct CellPoint {
        Cell cellValue;
        Point point;

        CellPoint(Cell cell, Point point) {
            this->cellValue = cell;
            this->point = point;
        }
    };

public:

    /**
     * Initializes the board with size width*height, with free cells
     * @param width Board width
     * @param height Board height
     */
	Board(uint8_t width, uint8_t height);


public:

//	void setCell(Board::Cell )

private:

	vector<Cell> boardArray_;

};

#endif /* INCLUDE_AI_HOMEWORK2_BOARD_H_ */
