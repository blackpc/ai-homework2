/**
 * Filename: MinMaxSearch.h
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

#ifndef INCLUDE_AI_HOMEWORK2_MINMAXSEARCH_H_
#define INCLUDE_AI_HOMEWORK2_MINMAXSEARCH_H_


#include <iostream>
#include <math.h>
#include <limits>

#include <ai-homework2/IGoGameHeuristic.h>


using namespace std;


/**
 * Minimax search algorithm
 */
class MinMaxSearch {

public:

    MinMaxSearch(IGoGameHeuristic* heuristic);

public:

    const string search(const GoGame& game, int maxSteps = -1, int maxDepth = -1) const;

private:

    IGoGameHeuristic* heuristic_;

private:

    pair<Board::CellPoint, double> minimax(const GoGame& game, bool maxPlayer, int depth = -1) const;

private:

    struct CellPointScoreComparator {
        inline bool operator() (
                const pair<Board::CellPoint, double>& cell1,
                const pair<Board::CellPoint, double>& cell2) const {
            return cell1.second > cell2.second;
        }
    };

};

#endif /* INCLUDE_AI_HOMEWORK2_MINMAXSEARCH_H_ */
