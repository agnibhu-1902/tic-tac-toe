#include "board.h"
#include <limits>

int* player(string name, Board &board, bool player) {
    cout << "\n\n" << name << "'s turn:\n";
    int pos, row, col, *arr = new int[2];
    do
    {
        cout << "\nWhere do you want to place your piece? [1-9]: ";
        while (!(cin >> pos))
        {
            cout << "Please enter a proper numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (pos < 1 || pos > 9)
        {
            cout << "Invalid position. Please enter a number within 1 and 9.\n";
            continue;
        }
        row = (pos - 1) / 3; col = (pos - 1) % 3;
        if (board.filled(row, col))
            cout << pos << " is already taken. Try again!\n";
    }
    while ((pos < 1 || pos > 9) || board.filled(row, col));
    board.place(row, col, player);
    board.draw();
    arr[0] = row; arr[1] = col; return arr;
}
