#include "board.h"
#include <ctime>

bool Board:: randomize()
{
    if (tied())
        return false;
    srand(time(0));
    int pos, row, col;
    do
    {
        pos = rand() % 10;
        row = pos / 3; col = pos % 3;
    }
    while (filled(row, col));
    place(row, col, false);
    if (match(row, col, false))
        return true;
    else
        return false;
}