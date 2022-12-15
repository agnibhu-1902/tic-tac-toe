#include "board.h"
bool _MATCH = false;
bool Board:: brain()
{
    if (tied())
        return false;
    int count = 2; bool infiltrate_player = false; _MATCH = false;
    while (count--)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == (infiltrate_player ? this->player : computer))
                {
                    if (infiltrate_horizontal(i, infiltrate_player))
                        return _MATCH;
                    if (infiltrate_vertical(j, infiltrate_player))
                        return _MATCH;
                    if (i == 1 && j == 1)
                    {
                        if (infiltrate_l_diagonal(infiltrate_player))
                            return _MATCH;
                        if (infiltrate_r_diagonal(infiltrate_player))
                            return _MATCH;
                    }
                    else if (i == j)
                    {
                        if (infiltrate_l_diagonal(infiltrate_player))
                            return _MATCH;
                    }
                    else if (i == 2 - j)
                    {
                        if (infiltrate_r_diagonal(infiltrate_player))
                            return _MATCH;
                    }
                }
        infiltrate_player = true;
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == computer)
            {
                if (put_horizontal(i))
                    return _MATCH;
                if (put_vertical(j))
                    return _MATCH;
                if (i == 1 && j == 1)
                {
                    if (put_l_diagonal())
                        return _MATCH;
                    if (put_r_diagonal())
                        return _MATCH;
                }
                else if (i == j)
                {
                    if (put_l_diagonal())
                        return _MATCH;
                }
                else if (i == 2 - j)
                {
                    if (put_r_diagonal())
                        return _MATCH;
                }
            }
    return randomize();
}
bool Board:: put_horizontal(int row)
{
    for (int i = 0; i < 3; i++)
        if (board[row][i] == player)
            return false;
    for (int i = 0; i < 3; i++)
        if (!filled(row, i))
        {
            board[row][i] = computer;
            if (match(row, i, false))
                _MATCH = true;
            return true;
        }
    return false;
}
bool Board:: put_vertical(int col)
{
    for (int i = 0; i < 3; i++)
        if (board[i][col] == player)
            return false;
    for (int i = 0; i < 3; i++)
        if (!filled(i, col))
        {
            board[i][col] = computer;
            if (match(i, col, false))
                _MATCH = true;
            return true;
        }
    return false;
}
bool Board:: put_l_diagonal()
{
    for (int i = 0; i < 3; i++)
        if (board[i][i] == player)
            return false;
    for (int i = 0; i < 3; i++)
        if (!filled(i, i))
        {
            board[i][i] = computer;
            if (match(i, i, false))
                _MATCH = true;
            return true;
        }
    return false;
}
bool Board:: put_r_diagonal()
{
    for (int i = 0, j = 2; i < 3; i++, j--)
        if (board[i][j] == player)
            return false;
    for (int i = 0, j = 2; i < 3; i++, j--)
        if (!filled(i, j))
        {
            board[i][j] = computer;
            if (match(i, j, false))
                _MATCH = true;
            return true;
        }
    return false;
}
bool Board:: infiltrate_horizontal(int row, bool player)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[row][i] == (player ? this->player : computer))
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(row, i))
            {
                board[row][i] = computer;
                if (match(row, i, false))
                    _MATCH = true;
                return true;
            }
    return false;
}
bool Board:: infiltrate_vertical(int col, bool player)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][col] == (player ? this->player : computer))
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(i, col))
            {
                board[i][col] = computer;
                if (match(i, col, false))
                    _MATCH = true;
                return true;
            }
    return false;
}
bool Board:: infiltrate_l_diagonal(bool player)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][i] == (player ? this->player : computer))
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(i, i))
            {
                board[i][i] = computer;
                if (match(i, i, false))
                    _MATCH = true;
                return true;
            }
    return false;
}
bool Board:: infiltrate_r_diagonal(bool player)
{
    int count = 0;
    for (int i = 0, j = 2; i < 3; i++, j--)
        if (board[i][j] == (player ? this->player : computer))
            count++;
    if (count == 2)
        for (int i = 0, j = 2; i < 3; i++, j--)
            if (!filled(i, j))
            {
                board[i][j] = computer;
                if (match(i, j, false))
                    _MATCH = true;
                return true;
            }
    return false;
}