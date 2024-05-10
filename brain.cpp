#include "board.h"

bool Board:: brain()
{
    if (tied())
        return false;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == player)
            {
                if (infiltrate_horizontal(i))
                {
                    if (match(i, j, false))
                        return true;
                    else
                        return false;
                }
                if (infiltrate_vertical(j))
                {
                    if (match(i, j, false))
                        return true;
                    else
                        return false;
                }
                if (i == 1 && j == 1)
                {
                    if (infiltrate_l_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                    if (infiltrate_r_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                }
                else if (i == j)
                {
                    if (infiltrate_l_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                }
                else if (i == 2 - j)
                {
                    if (infiltrate_r_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                }
            }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == computer)
            {
                if (put_horizontal(i))
                {
                    if (match(i, j, false))
                        return true;
                    else
                        return false;
                }
                if (put_vertical(j))
                {
                    if (match(i, j, false))
                        return true;
                    else
                        return false;
                }
                if (i == 1 && j == 1)
                {
                    if (put_l_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                    if (put_r_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                }
                else if (i == j)
                {
                    if (put_l_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
                }
                else if (i == 2 - j)
                {
                    if (put_r_diagonal())
                    {
                        if (match(i, j, false))
                            return true;
                        else
                            return false;
                    }
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
            return true;
        }
    return false;
}
bool Board:: infiltrate_horizontal(int row)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[row][i] == player)
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(row, i))
            {
                board[row][i] = computer;
                return true;
            }
    return false;
}
bool Board:: infiltrate_vertical(int col)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][col] == player)
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(i, col))
            {
                board[i][col] = computer;
                return true;
            }
    return false;
}
bool Board:: infiltrate_l_diagonal()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][i] == player)
            count++;
    if (count == 2)
        for (int i = 0; i < 3; i++)
            if (!filled(i, i))
            {
                board[i][i] = computer;
                return true;
            }
    return false;
}
bool Board:: infiltrate_r_diagonal()
{
    int count = 0;
    for (int i = 0, j = 3; i < j; i++, j--)
        if (board[i][j] == player)
            count++;
    if (count == 2)
        for (int i = 0, j = 3; i < j; i++, j--)
            if (!filled(i, j))
            {
                board[i][j] = computer;
                return true;
            }
    return false;
}