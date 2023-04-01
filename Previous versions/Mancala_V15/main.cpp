#include "AdminUser.h"

void gameLoop(Board &, string);
bool isAdmin(string, string);
void displayLeaderboard();

int main() {
    Board board;
    string username, password;
    srand(time(NULL));
    //    Admin testadmin;
    //    testadmin.username = "piadmin";
    //    testadmin.password = "piadmin";
    //    fstream adminDB("AdminData.dat", ios::out | ios::binary);
    //    adminDB.seekp(ios::beg);
    //    adminDB.write(reinterpret_cast<char *> (&testadmin), sizeof (testadmin));
    //    adminDB.close();

    char login = ' ';
    cout << "Welcome to Mancala V99" << endl;
    do {
        char input;
        cout << "R) To Register For an Account \t L) To Log In to an Account" << endl;
        cin >> input;
        login = input;
    } while (login != 'R' && login != 'L');

    if (login == 'R') {
        cout << "Set Username : ";
        cin >> username;
        cout << "Set Password : ";
        cin >> password;
    } else if (login == 'L') {
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;
    }

    if (isAdmin(username, password)) {
        cout << "Admin" << endl;
        AdminUser test;
    } else {
        User user;
        user.setUser(username, password);
        displayLeaderboard();
        gameLoop(board, username);
        user.setUserScore(board.returnPlayer1Score(), board.returnPlayer2Score());
        board.printBoard();
    }
    return 0;
}

bool isAdmin(string username, string password) {
    fstream adminDB("AdminData.dat", ios::in | ios::app | ios::binary);
    Admin temp;

    adminDB.seekg(ios::beg);
    while (adminDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
        if (temp.username == username && temp.password != password) {
            string password;
            do {
                cout << "Incorrect Password Try Again : ";
                cin>>password;
            } while (password != temp.password);
            return 1;
        } else if (temp.username == username && temp.password == password) {
            return 1;
        }
    }
    adminDB.close();
    return 0;
}

void displayLeaderboard() {
    fstream userDB("UserData.dat", ios::in | ios::app | ios::binary);
    UserInfo temp;
    vector<UserInfo> leaderboard;

    userDB.seekg(ios::beg);
    while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
        leaderboard.push_back(temp);
    }

    int userSize = leaderboard.size();
    for (int i = 0; i < userSize; i++) {
        for (int j = i + 1; j < userSize; j++) {
            if (leaderboard[j].highScore > leaderboard[i].highScore) {
                swap(leaderboard[i], leaderboard[j]);
            }
        }
    }

    cout << endl << "Username \t Highscore" << endl << endl;
    for (UserInfo user : leaderboard) {
        cout << left << setw(20);
        cout << user.username << setw(20) << user.highScore << endl;
    }

    userDB.close();
    cout << endl;
}

void gameLoop(Board &board, string username) {
    int playerTurn = 1;
    while (!board.gameOver()) { //Game ends when either side as 0 marbles in all pits

        if (playerTurn == 1) {
            int play, marbles;

            cout << endl;
            cout << username << "'s Turn. Enter a number 1 - 6 (L to R)" << endl;
            board.printBoard();
            cout << endl;
            //cin>>play;
            play = (rand() % 6) + 1;

            int currCell = play + 1;
            board.playerOneMove(currCell, play, marbles);
            currCell--; //Back off one to check if capture or go again

            board.checkOneMove(currCell, playerTurn);
        } else {
            int play, marbles;

            cout << endl;
            cout << "Player 2's Turn. Enter a number 1 - 6 (L to R)" << endl;
            board.printBoard();
            cout << endl;
            play = (rand() % 6) + 1;
            cout << "Player 2 Selected Cell " << play << endl << endl;

            play = 14 - play;
            int currCell = play + 1;
            board.playerTwoMove(currCell, play, marbles);
            currCell--;

            board.checkTwoMove(currCell, playerTurn);
        }
    }
}