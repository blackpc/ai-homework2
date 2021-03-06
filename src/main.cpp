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


#include <ai-homework2/BoardReader.h>
#include <ai-homework2/MinMaxSearch.h>
#include <ai-homework2/MoreChipsHeuristic.h>


using namespace std;


int main(int argc, char **argv) {

    string boardFilename = "input.txt";

    if (argc > 1)
        boardFilename = argv[1];

    try {
        BoardReader reader(boardFilename);
        ofstream outputStream("output.txt");

        GoGame game(reader.getBoard(), GoGame::TurnBlack);
        MinMaxSearch searcher(new MoreChipsHeuristic());

        string winner = searcher.search(game);
        cout << "The winner is: " << winner << endl;
        outputStream << winner << endl;
    } catch (const string* e) {
        cerr << "Exception occurred:" << endl;
        cerr << *e << endl;
    } catch (...) {
        cerr << "Unexpected exception occurred, fuck it." << endl;
    }



	return 1;
}


