#include "board.h"
#include <ctime>
#include <cctype>
#include <chrono>
#include <thread>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

void intro();
void quit();
void leaderboard();
int* player(string, Board&, bool);

int main(void)
{
    intro();
    fstream fout;
    fout.open("highscores.csv", ios::out | ios::app);
    string name, opponent; char player_mode;
    srand(time(0));
    const int MAX_TIME = 10, MIN_TIME = 3, MAX_SCORE = numeric_limits<int>::max() / 10000; char choice; bool flag;
    do
    {
        do
        {
            cout << "\n\nDo you want a single player or a multiplayer game? [s/m]: ";
            cin >> player_mode;
            if (player_mode != 's' && player_mode != 'm')
            {
                cout << "Oops! I didn't understand that. Try again.";
                continue;
            }
        } while (player_mode != 's' && player_mode != 'm');
        player_mode = tolower(player_mode);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\nHello, what is your name?\n";
        getline(cin, name);
        if (player_mode == 'm')
        {
            cout << "\nWhat is your opponent's name?\n";
            getline(cin, opponent);
            cout << "\nHi " << name << " and " << opponent << "! Have fun playing! :D\n";
        }
        else
        {
            opponent = "Vanessa";
            cout << "\nHi " << name << "! I am " << opponent << ", your computer opponent. I hope you will enjoy playing with me. :D\n";
        }
        cout << "\n***** PRESS ENTER *****";
        cin.get();
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
                cout << "Please type 'X' or 'O': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (piece != 'X' && piece != 'O');
        cout << "\nGood! You now have the '" << piece << "'.\n";
        cout << "\n***** PRESS ENTER *****";
        cin.clear();
        cin.get();
        Board board(piece);
        cout << "\nNow you need to place your piece.\n";
        board.draw();
        cout << "\nThe board has markings from 1 to 9. You can place your piece anywhere.\n";
        cout << "\nLet's play!\n";
        bool start_player = rand() % 2;
        if (start_player) // Choose who will start the game
            cout << "\n\n" << name << " will start the game.\n";
        else
            cout << "\n\n" << opponent << " will start the game.\n";
        while (!board.tied())
        {
            if (start_player)
            {
                int *arr = player(name, board, true);
                int row = arr[0], col = arr[1];
                delete[] arr;
                if (board.match(row, col, true))
                {
                    flag = true;
                    cout << "\n\n" << name << " wins!\n";
                    auto end = chrono::steady_clock::now(); // End the timer
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count(); // Get the elapsed time
                    cout << "Elapsed time: " << elapsed << " seconds\n";
                    int score = MAX_SCORE / (elapsed + 1);
                    cout << "Your score: " << score << "\n"; // Display the score
                    fout << name << ", " << score << "\n" << flush;
                    break;
                }
                if (board.tied())
                    break; 
            }
            start_player = true;
            if (player_mode == 'm')
            {
                int *arr = player(opponent, board, false);
                int row = arr[0], col = arr[1];
                delete[] arr;
                if (board.match(row, col, false))
                {
                    flag = true;
                    cout << "\n\n" << opponent << " wins!\n";
                    auto end = chrono::steady_clock::now(); // End the timer
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count(); // Get the elapsed time
                    cout << "Elapsed time: " << elapsed << " seconds\n";
                    int score = MAX_SCORE / (elapsed + 1);
                    cout << "Your score: " << score << "\n"; // Display the score
                    fout << opponent << ", " << score << "\n" << flush;
                    break;
                }
                if (board.tied())
                    break;
            }
            else
            {
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
                bool brain = rand() % 7, computer_status;
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
        }
        if (board.tied() && !flag)
        {
            cout << "\n\nMatch tied!\n";
            cout << "Nobody wins.\n";
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
            cout << "Elapsed time: " << elapsed << " seconds\n";
        }
        leaderboard();
        cout << "\nDo you want to play again? [Y/N]: ";
        do
        {
            cin >> choice;
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N')
                cout << "Please type 'Y' (yes) or 'N' (no): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (choice != 'Y' && choice != 'N');
    }
    while (choice == 'Y');
    quit();
    fout.close();
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
void leaderboard()
{
    ifstream fin("highscores.csv");
    string line;
    cout << endl << "====================== LEADERBOARD ======================" << endl;
    cout << "NAME" << "\t\t\t\t\t" << "HIGH SCORE" << endl;
    while (getline(fin, line))
    {
        istringstream iss(line); string word;
        while (getline(iss, word, ','))
        {
            cout << word;
            int spaces = count_if(word.begin(), word.end(), [](unsigned char c){ return isspace(c); }); //Count spaces
            for (int i = 0; i < 5 - spaces; i++)
                cout << "\t";
        }
        cout << endl;
    }
    fin.close();
}
void quit()
{
    cout << "\nGoodbye!";
    cout << "\n\n***** PRESS ENTER TO EXIT *****";
    cin.get();
}
