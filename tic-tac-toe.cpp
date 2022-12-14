#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "board.h"
#include <ctime>
#include <cstdio>
#include <cctype>
#include <chrono>
#include <thread>

void intro();
void quit();

int main(void)
{
    intro();
    string name;
    cout << "\n\nHello, what is your name?\n";
    cin >> name;
    cout << "\nHi " << name << "! I am Vanessa, your computer opponent. I hope you will enjoy playing with me. :D\n";
    cout << "\n***** PRESS ANY KEY *****";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    srand(time(0));
    const int MAX_TIME = 10, MIN_TIME = 3; char choice; bool flag;
    do
    {
        flag = false;
        cout << "\nOK, let's begin!\n";
        cout << "\nFirst, you need to choose your piece.\n";
        cout << "Do you want the 'X' or the 'O'? [X/O]: ";
        char piece;
        do
        {
            cin >> piece;
            piece = toupper(piece);
            if (piece != 'X' && piece != 'O')
                cout << "\nPlease type 'X' or 'O': ";
        }
        while (piece != 'X' && piece != 'O');
        cout << "\nGood! You now have the '" << piece << "'.\n";
        cout << "\n***** PRESS ANY KEY *****";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        Board board(piece);
        cout << "\nNow you need to place your piece.\n";
        board.draw();
        cout << "\nThe board has markings from 1 to 9. You can place your piece anywhere.\n";
        cout << "\nLet's play!\n";
        cin.get();
        while (!board.tied())
        {
            cout << "\n\n" << name << "'s turn:\n";
            cout << "\nWhere do you want to place your piece? [1-9]: ";
            int pos, row, col;
            do
            {
                cin >> pos;
                if (pos < 1 || pos > 9)
                    cout << "Invalid position. Try again!";
                row = (pos - 1) / 3; col = (pos - 1) % 3;
                if (board.filled(row, col))
                    cout << pos << " is already taken. Try again!";
            }
            while ((pos < 1 || pos > 9) || board.filled(row, col));
            board.place(row, col, true);
            board.draw();
            if (board.match(row, col, true))
            {
                flag = true;
                cout << "\n\n" << name << " wins!\n";
                break;
            }
            if (board.tied())
                break;
            cout << "\n\nVanessa is thinking";
            int time = rand() % (MAX_TIME - MIN_TIME + 1) + MIN_TIME;
            for (int i = 0; i < time; i++)
            {
                cout.flush();
                sleep(1);
                cout << ".";
            }
            cout << "\n";
            bool brain = rand() % 2, computer_status;
            if (brain)
                computer_status = board.brain();
            else
                computer_status = board.randomize();
            board.draw();
            if (computer_status)
            {
                flag = true;
                cout << "\n\nVanessa wins!\n";
                break;
            }
        }
        if (board.tied() && !flag)
        {
            cout << "\n\nMatch tied!\n";
            cout << "Nobody wins.\n";
        }
        cout << "\nDo you want to play again? [Y/N]: ";
        do
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N')
                cout << "\nPlease type 'Y' (yes) or 'N' (no): ";
        }
        while (choice != 'Y' && choice != 'N');
    }
    while (choice == 'Y');
    quit();
    return 0;
}
void intro()
{
    cout << "\n*******************************************************";
    cout << "\n*                     TIC-TAC-TOE                     *";
    cout << "\n*               The beloved classic game              *";
    cout << "\n*          Play tic-tac-toe with the computer         *";
    cout << "\n*******************************************************";

}
void quit()
{
    cout << "\nGoodbye!";
    cout << "\n\n***** PRESS ANY KEY TO EXIT *****";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}