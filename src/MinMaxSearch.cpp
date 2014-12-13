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

const string MinMaxSearch::search(const GoGame& game) const {
    string winner = "W";

    GoGame currentGame = game;
    cout << currentGame.getBoard().toString() << endl;

    while (!currentGame.isFinished()) {
        set<Board::CellPoint> allMoves = currentGame.getAvailableMoves();

        Board::Point bestMove;
        double bestValue = -std::numeric_limits<double>::max();

        for(set<Board::CellPoint>::iterator move = allMoves.begin();
                move != allMoves.end(); ++move) {

            const GoGame& nextGame = game.simulateMove(move->point);
            double moveEstimation = minimax(nextGame, false);

            if (moveEstimation > bestValue) {
                bestValue = moveEstimation;
                bestMove = move->point;
            }
        }



        currentGame.makeMove(bestMove);

        cout << currentGame.getBoard().toString() << endl;
    }

    return currentGame.getWinner();
}

double MinMaxSearch::minimax(GoGame game, bool maxPlayer, int depth) const {

    static long counter = 0;

    if (game.isFinished()) {
        double estimation = heuristic_->estimate(game);
        return estimation;
    }

    set<Board::CellPoint> allMoves = game.getAvailableMoves();

    double bestValue;

    if (maxPlayer)
        bestValue = -std::numeric_limits<double>::max();
    else
        bestValue = std::numeric_limits<double>::max();

    for(set<Board::CellPoint>::iterator move = allMoves.begin();
            move != allMoves.end(); ++move) {

        GoGame nextGame = game.simulateMove(move->point);
        double childValue = minimax(nextGame, !maxPlayer, depth + 1);

//        cout << nextGame.getBoard().toString() << endl;

        if (counter++ % 1000000 == 0)
            cout << counter << " depth = " << depth << endl;

        if (maxPlayer)
            bestValue = std::max(childValue, bestValue);
        else
            bestValue = std::min(childValue, bestValue);
    }

    return bestValue;
}
