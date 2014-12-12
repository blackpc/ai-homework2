/**
 * Filename: Board.cpp
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

#include <ai-homework2/Board.h>

Board::Board(uint8_t width, uint8_t height) {
    width_ = width;
    height_ = height;

    boardArray_.resize(width * height, Board::CellEmpty);
    assert(boardArray_.size() == width * height);
}

void Board::setCell(uint8_t x, uint8_t y, Cell cell) {
    boardArray_[width_ * y + x] = cell;
}

void Board::setCell(const Point& point, Cell cell) {
    setCell(point.x, point.y, cell);
}

void Board::setCell(const CellPoint& cellPoint) {
    setCell(cellPoint.point.x, cellPoint.point.y, cellPoint.cellValue);
}

bool Board::isEmpty(uint8_t x, uint8_t y) const {
    return getCell(x, y) == Board::CellEmpty;
}

bool Board::isInBounds(uint8_t x, uint8_t y) const {
    return x >= 0 && x < width_ &&
           y >= 0 && y < height_;
}

bool Board::isInBounds(const Point& point) const {
    return isInBounds(point.x, point.y);
}

const string Board::cellToString(Cell cell) const {
    if (cell == Board::CellBlack)
        return "B";

    if (cell == Board::CellWhite)
        return "W";

    if (cell == Board::CellEmpty)
        return "E";

    throw new string("Invalid cell value");
}

uint32_t Board::getBlackCellsCount() const {
    uint32_t counter = 0;

    for (size_t i = 0; i < boardArray_.size(); ++i)
        if (boardArray_[i] == Board::CellBlack)
            counter++;

    return counter;
}

uint32_t Board::getWhiteCellsCount() const {
    uint32_t counter = 0;

    for (size_t i = 0; i < boardArray_.size(); ++i)
        if (boardArray_[i] == Board::CellWhite)
            counter++;

    return counter;
}

uint32_t Board::getEmptyCellsCount() const {
    uint32_t counter = 0;

    for (size_t i = 0; i < boardArray_.size(); ++i)
        if (boardArray_[i] == Board::CellEmpty)
            counter++;

    return counter;
}

const string Board::toString() const {
    stringstream stream;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            const string& cellString = cellToString(getCell(x, y));
            stream << cellString;
        }
        stream << endl;
    }

    return stream.str();
}
