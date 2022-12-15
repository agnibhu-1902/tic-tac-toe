#include "board.h"

bool Board:: horizontal_scan(int row, bool player) const
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[row][i] == (player ? this->player : computer))
            count++;
    return count == 3 ? true : false;
}
bool Board:: vertical_scan(int col, bool player) const
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][col] == (player ? this->player : computer))
            count++;
    return count == 3 ? true : false;
}
bool Board:: l_diagonal_scan(bool player) const
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if(board[i][i] == (player ? this->player : computer))
            count++;
    return count == 3 ? true : false;
}
bool Board:: r_diagonal_scan(bool player) const
{
    int count = 0;
    for (int i = 0, j = 2; i < 3; i++, j--)
        if (board[i][j] == (player ? this->player : computer))
            count++;
    return count == 3 ? true : false;
}
bool Board:: match(int row, int col, bool player) const
{
    if (horizontal_scan(row, player))
        return true;
    if (vertical_scan(col, player))
        return true;
    if (row == 1 && col == 1)
    {
        if (l_diagonal_scan(player))
            return true;
        if (r_diagonal_scan(player))
            return true;
    }
    else if (row == col)
    {
        if (l_diagonal_scan(player))
            return true;
    }
    else if (row == 2 - col)
    {
        if (r_diagonal_scan(player))
            return true;
    }
    return false;
}