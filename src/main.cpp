/**
 * Filename: main.cpp
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


#include <ai-homework2/MinMaxSearch.h>
#include <ai-homework2/MoreChipsHeuristic.h>


using namespace std;


void printBoard(const Board& board, const string& title) {
    cout << title << ":" << endl;
    cout << board.toString() << endl << endl;
}

void testBoard() {
    Board board(7, 7);
    printBoard(board, "Empty board");

    board.setCell(0, 0, Board::CellWhite);
    board.setCell(0, 1, Board::CellBlack);

    printBoard(board, "Black and white chips");
}

void testCapturing() {
    Board board(5, 5);
    board.setCell(3, 1, Board::CellWhite);
    board.setCell(1, 3, Board::CellWhite);

    board.setCell(2, 2, Board::CellBlack);
    board.setCell(1, 2, Board::CellBlack);
    board.setCell(2, 1, Board::CellBlack);

    GoGame game(board, GoGame::TurnWhite);

    printBoard(game.getBoard(), "Before capturing (white's turn)");

    GoGame clonedGame = game.simulateMove(1, 1);

    printBoard(clonedGame.getBoard(), "After capturing");

    printBoard(game.getBoard(), "Original game");
}

void test() {
    Board board(5, 5);

    board.setCell(0, 0, Board::CellBlack);
    board.setCell(0, 1, Board::CellBlack);
    board.setCell(1, 0, Board::CellWhite);
    board.setCell(2, 0, Board::CellWhite);

    GoGame game(board, GoGame::TurnBlack);

    vector<GoGame> v;

    for (int i = 0; i < 100; ++i) {
        v.push_back(GoGame(board));
    }
}

void testMinimax() {
    Board board(3, 5);

    board.setCell(1, 1, Board::CellBlack);
    board.setCell(0, 0, Board::CellWhite);
    board.setCell(2, 2, Board::CellWhite);
    board.setCell(0, 1, Board::CellWhite);
    board.setCell(2, 4, Board::CellWhite);

    GoGame game(board, GoGame::TurnBlack);

    MinMaxSearch minimaxSearch(new MoreChipsHeuristic());
    cout << minimaxSearch.search(game);
}

int main(int argc, char **argv) {

    testMinimax();

	return 1;
}


