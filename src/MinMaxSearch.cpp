/**
 * Filename: MinMaxSearch.cpp
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


MinMaxSearch::MinMaxSearch(IGoGameHeuristic* heuristic)
    : heuristic_(heuristic) {
}

const string MinMaxSearch::search(const GoGame& game, int maxSteps, int maxDepth) const {
    string winner = "X";

    GoGame currentGame = game;

    cout << currentGame.getBoard().toString() << endl;

    bool maxPlayer = true;

    while (!currentGame.isFinished() && maxSteps-- != 0) {
        Board::CellPoint bestMove = minimax(currentGame, maxPlayer, maxDepth).first;
        currentGame.makeMove(bestMove.point);
        maxPlayer = !maxPlayer;
        cout << currentGame.getBoard().toString() << endl;
    }

    return currentGame.getWinner();
}

pair<Board::CellPoint, double> MinMaxSearch::minimax(
        const GoGame& game, bool maxPlayer, int depth) const {

    if (depth == 0) {
        double estimate = heuristic_->estimate(game);
        return make_pair(
                Board::CellPoint(0, 0, Board::CellEmpty),
                estimate);
    }

    if (game.isFinished()) {
        double estimation = heuristic_->estimate(game);
        return make_pair(
                Board::CellPoint(0, 0, Board::CellEmpty),
                estimation);
    }

    set<Board::CellPoint> allMoves = game.getAvailableMoves();

    double bestValue;
    Board::CellPoint bestMove(0, 0, Board::CellEmpty);

    if (maxPlayer)
        bestValue = -std::numeric_limits<double>::max();
    else
        bestValue = std::numeric_limits<double>::max();

    for(set<Board::CellPoint>::iterator move = allMoves.begin();
            move != allMoves.end(); ++move) {

        GoGame nextGame = game.simulateMove(move->point);
        cout << nextGame.getBoard().toString() << endl;
        double childValue = minimax(nextGame, !maxPlayer, depth - 1).second;

        if (maxPlayer) {
            if (childValue > bestValue) {
                bestValue = childValue;
                bestMove = *move;
            }
        }
        else
            if (childValue < bestValue) {
                bestValue = childValue;
                bestMove = *move;
            }
    }

    return make_pair(bestMove, bestValue);
}
