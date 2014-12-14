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
#include <assert.h>
#include <sstream>


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
        CellBlack,
        CellWhite,
        CellEmpty
    };

    /**
     * Represents x-y integer coordinates
     */
    struct Point {
        int32_t x;
        int32_t y;

        Point() : x(0), y(0) { }

        Point(int32_t x, int32_t y) {
            this->x = x;
            this->y = y;
        }

        bool operator <(const Point& other) const {
            if (x < other.x)
                return true;

            return y < other.y;
        }
    };

    /**
     * Cell with coordinates
     */
    struct CellPoint {
        Cell cellValue;
        Point point;

        CellPoint(Point point, Cell cell) {
            this->cellValue = cell;
            this->point = point;
        }

        CellPoint(int32_t x, int32_t y, Cell cell) {
            this->point = Point(x, y);
            this->cellValue = cell;
        }

        bool operator <(const CellPoint& other) const {
            return this->point < other.point;
        }

        string toString() const {
            stringstream stream;
            stream << "Point [ x = " << (int)point.x << ", y = " << (int)point.y << "]";
            return stream.str();
        }
    };

public:

    /**
     * Initializes the board with size width*height, with free cells
     * @param width Board width
     * @param height Board height
     */
	Board(int32_t width, int32_t height);

	/**
	 * Copy constructor
	 * @param board
	 */
	Board(const Board& board);

	/**
	 * Assignment operator
	 * @param board
	 * @return
	 */
	void operator =(const Board& board);

	/**
	 * Deletes board array
	 */
	~Board();

public:

	/**
	 * Gets the value of specified cell
	 * @param x
	 * @param y
	 * @return
	 */
	inline Cell getCell(int32_t x, int32_t y) const {
	    return boardArray_[width_ * y + x];
	}

	/**
	 * Gets the value of specified cell
	 * @param point
	 * @return
	 */
	inline Cell getCell(const Point& point) const {
	    return getCell(point.x, point.y);
	}

	/**
	 * Sets specified cell value in specified point
	 * @param x
	 * @param y
	 * @param cell
	 */
	void setCell(int32_t x, int32_t y, Cell cell);

	/**
	 * Sets specified cell value in specified point
	 * @param point
	 * @param cell
	 */
	void setCell(const Point& point, Cell cell);

	/**
	 * Sets specified cell value in specified point
	 * @param cellPoint CellPoint
	 */
	void setCell(const CellPoint& cellPoint);

	/**
	 * Returns true if specified cell is empty
	 * @param x
	 * @param y
	 * @return
	 */
	bool isEmpty(int32_t x, int32_t y) const;

	/**
	 * Returns true if specified cell is empty
	 * @param point
	 * @return
	 */
	bool isEmpty(const Point& point) const;

	/**
	 * Verifies that a specified point is within the board bounds
	 * @param x
	 * @param y
	 * @return
	 */
	bool isInBounds(int32_t x, int32_t y) const;

	/**
	 * Verifies that a specified point is within the board bounds
	 * @param point
	 * @return
	 */
	bool isInBounds(const Point& point) const;

	/**
	 * Gets the number of black cells
	 * @return
	 */
	uint32_t getBlackCellsCount() const;

	/**
	 * Gets the number of white cells
	 * @return
	 */
	uint32_t getWhiteCellsCount() const;

	/**
	 * Gets the number of empty cells
	 * @return
	 */
	uint32_t getEmptyCellsCount() const;

	/**
	 * Gets board width
	 * @return
	 */
	inline int32_t getWidth() const {
	    return width_;
	}

	/**
	 * Gets board height
	 * @return
	 */
	inline int32_t getHeight() const {
        return height_;
    }

	/**
	 * Switches cell color from black to white and vice versa
	 * @param cell
	 * @return
	 */
	inline Cell switchCellColor(Cell cell) const {
	    if (cell == Board::CellBlack)
	        return Board::CellWhite;

	    if (cell == Board::CellWhite)
            return Board::CellBlack;

	    return Board::CellEmpty;
	}

	/**
	 * Returns string representation of cell
	 * @param cell
	 * @return
	 */
	const string cellToString(Cell cell) const;

	/**
	 * Returns string representation of the board
	 * @return
	 */
	const string toString() const;

private:

	int32_t width_;
	int32_t height_;

	Cell* boardArray_;

};

#endif /* INCLUDE_AI_HOMEWORK2_BOARD_H_ */
