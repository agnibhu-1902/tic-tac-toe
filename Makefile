tic-tac-toe:
	g++ -std=c++11 -c board.cpp
	g++ -std=c++11 -c checker.cpp
	g++ -std=c++11 -c brain.cpp
	g++ -std=c++11 -c randomize.cpp
	g++ -std=c++11 -c player.cpp
	g++ -std=c++11 -c tic-tac-toe.cpp
	g++ -Wall -std=c++11 -static -static-libgcc -static-libstdc++ -o tic-tac-toe tic-tac-toe.o board.o player.o brain.o checker.o randomize.o