tic-tac-toe:
	g++ -std=c++11 -c board.cpp
	g++ -std=c++11 -c checker.cpp
	g++ -std=c++11 -c brain.cpp
	g++ -std=c++11 -c randomize.cpp
	g++ -std=c++11 -c tic-tac-toe.cpp
	g++ -std=c++11 -o tic-tac-toe tic-tac-toe.o board.o brain.o checker.o randomize.o