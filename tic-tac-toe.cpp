#include "board.h"
#include <ctime>
#include <cctype>
#include <chrono>
#include <thread>
#include <limits>

void intro();
void quit();

int main(void)
{
    intro();
    string name, opponent = "Vanessa";
    cout << "\n\nHello, what is your name?\n";
    cin >> name;
    cout << "\nHi " << name << "! I am " << opponent << ", your computer opponent. I hope you will enjoy playing with me. :D\n";
    cout << "\n***** PRESS ENTER *****";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    srand(time(0));
    const int MAX_TIME = 10, MIN_TIME = 3; char choice; bool flag;
    do
    {
        auto start = chrono::steady_clock::now(); // Start the timer
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
        cout << "\n***** PRESS ENTER *****";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        Board board(piece);
        cout << "\nNow you need to place your piece.\n";
        board.draw();
        cout << "\nThe board has markings from 1 to 9. You can place your piece anywhere.\n";
        cout << "\nLet's play!\n";
        cout << "\n***** PRESS ENTER *****";
        cin.get();
        bool start_player = rand() % 2;
        if (start_player) // Choose who will start the game
            cout << "\n\n" << name << " will start the game.\n";
        else
            cout << "\n\n" << opponent << " will start the game.\n";
        while (!board.tied())
        {
            if (start_player)
            {
                cout << "\n\n" << name << "'s turn:\n";
                int pos, row, col;
                do
                {
                    cout << "\nWhere do you want to place your piece? [1-9]: ";
                    while (!(cin >> pos))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout << "\nPlease enter proper numeric value: ";
                    }
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
                board.place(row, col, true);
                board.draw();
                if (board.match(row, col, true))
                {
                    flag = true;
                    cout << "\n\n" << name << " wins!\n";
                    auto end = chrono::steady_clock::now(); // End the timer
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count(); // Get the elapsed time
                    cout << "Elapsed time: " << elapsed << " seconds\n";
                    int imax = std::numeric_limits<int>::max();
                    cout << "Your score: " << imax / elapsed << "\n"; // Display the score
                    break;
                }
                if (board.tied())
                    break;
            }
            start_player = true;
            cout << "\n\n" << opponent << "'s turn:";
            cout << "\n\n" << opponent << " is thinking";
            int time = rand() % (MAX_TIME - MIN_TIME + 1) + MIN_TIME;
            for (int i = 0; i < time; i++)
            {
                cout.flush();
                this_thread::sleep_for(chrono::seconds(1)); // Sleep momentarily
                cout << ".";
            }
            cout << "\n";
            bool brain = rand() % 5, computer_status;
            if (brain)
                computer_status = board.brain();
            else
                computer_status = board.randomize();
            board.draw();
            if (computer_status)
            {
                flag = true;
                cout << "\n\n" << opponent << " wins!\n";
                cout << "Better luck next time!\n";
                auto end = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
                cout << "Elapsed time: " << elapsed << " seconds\n";
                break;
            }
        }
        if (board.tied() && !flag)
        {
            cout << "\n\nMatch tied!\n";
            cout << "Nobody wins.\n";
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
            cout << "Elapsed time: " << elapsed << " seconds\n";
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
    cout << "\n\n***** PRESS ENTER TO EXIT *****";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
