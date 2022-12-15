#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

class Board
{
private:
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char player, computer;
    bool horizontal_scan(int, bool) const;
    bool vertical_scan(int, bool) const;
    bool l_diagonal_scan(bool) const;
    bool r_diagonal_scan(bool) const;
    bool put_horizontal(int);
    bool put_vertical(int);
    bool put_l_diagonal();
    bool put_r_diagonal();
    bool infiltrate_horizontal(int, bool);
    bool infiltrate_vertical(int, bool);
    bool infiltrate_l_diagonal(bool);
    bool infiltrate_r_diagonal(bool);
public:
    Board(char);
    ~Board();
    void place(int, int, bool);
    void draw() const;
    bool filled(int, int) const;
    bool match(int, int, bool) const;
    bool tied() const;
    bool brain();
    bool randomize();
};

#endif