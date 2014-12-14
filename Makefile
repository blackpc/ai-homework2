all:
	g++ -O3 -Wall -Iinclude src/Board.cpp src/BoardReader.cpp src/GoGame.cpp src/main.cpp src/MinMaxSearch.cpp src/MoreChipsHeuristic.cpp  -o minimax

clean:
	rm minimax
