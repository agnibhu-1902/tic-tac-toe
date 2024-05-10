#include "board.h"

Board:: Board(char player)
    : player(player), computer((player == 'X') ? 'O' : 'X')
{
}
Board:: ~Board()
{
}
void Board:: place(int row, int col, bool player)
{
    if (!filled(row, col))
        board[row][col] = player ? this->player : computer;
}
void Board:: draw() const
{
    cout << "\n - - - - - - - - -";
    for (int i = 0; i < 3; i++)
    {
        cout << "\n|";
        for (int j = 0; j < 3; j++)
            cout << "  " << board[i][j] << "  |";
        if (i != 2)
            cout << "\n - - - - - - - - -";
    }
    cout << "\n - - - - - - - - -";
}
bool Board:: filled(int row, int col) const
{
    return board[row][col] == player || board[row][col] == computer;
}
bool Board:: tied() const
{
    bool flag = true;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!filled(i, j))
                flag = false;
    return flag;
}