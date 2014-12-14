/**
 * Filename: BoardReader.cpp
 *   Author: Igor Makhtes
 *     Date: Dec 13, 2014
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

#include <ai-homework2/BoardReader.h>


BoardReader::BoardReader(const string& filename)
    : board_(2, 2) {

    ifstream stream(filename.c_str());

    if (!stream) {
        stringstream s;
        s << "Failed to read input file: " << filename;
        throw new string(s.str());
    }

    vector<string> rows;

    while(!stream.eof()) {
        string line;
        stream >> line;

        if (line != "\0")
            rows.push_back(line);
    }

    int boardWidth = rows[0].length();
    int boardHeight = rows.size();

    board_ = Board(boardWidth, boardHeight);

    for (int y = 0; y < boardHeight; ++y) {
        for (int x = 0; x < boardWidth; ++x) {
            board_.setCell(x, y, charToCell(rows[y][x]));
        }
    }
}

Board BoardReader::getBoard() const {
    return board_;
}

Board::Cell BoardReader::charToCell(char c) const {
    if (c == 'E')
        return Board::CellEmpty;

    if (c == 'W')
        return Board::CellWhite;

    if (c == 'B')
        return Board::CellBlack;

    throw new string("Unknown cell type");
}
