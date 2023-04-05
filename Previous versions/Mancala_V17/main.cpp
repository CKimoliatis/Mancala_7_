#include "AdminUser.h"

void gameLoop(Board &, char[]);
bool isAdmin(char[], char[]);
void displayLeaderboard();

int main() {
    Board board;
    char username[SIZE], password[SIZE];
    srand(time(NULL));
/*

            char admin[SIZE] = "piadmin";
            char pass[SIZE] = "piadmin";
            Admin testadmin;
            for(int i = 0; i < SIZE; i++){
                testadmin.username[i] = admin[i];
            }
            for(int i = 0; i < SIZE; i++){
                testadmin.password[i] = pass[i];
            }
            fstream adminDB("AdminData.bin", ios::in | ios::app | ios::binary);
            adminDB.seekp(ios::app);
            adminDB.write(reinterpret_cast<char *> (&testadmin), sizeof (testadmin));
            adminDB.close();
*/

    char login = ' ';
    cout << "Welcome to Mancala V99" << endl;
    do {
        cout << "R) To Register For an Account \t L) To Log In to an Account" << endl;
        cin >> login;
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
        if (!user.getStatus()) {
            return 0;
        }
        displayLeaderboard();
        gameLoop(board, username);
        user.setUserScore(board.returnPlayer1Score(), board.returnPlayer2Score());
        board.printBoard();
    }
}

bool isAdmin(char username[], char password[]) {
    fstream adminDB("AdminData.bin", ios::in | ios::app | ios::binary);
    Admin temp;
    adminDB.seekg(ios::beg);

    int userNameLength = 0;
    char t = username[userNameLength];
    while (t != '\0') {
        userNameLength++;
        t = username[userNameLength];
    }
    int passwordLength = 0;
    t = password[passwordLength];
    while (t != '\0') {
        passwordLength++;
        t = username[passwordLength];
    }

    while (adminDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
        bool validUsername = 1, validPassword = 1;
        for (int i = 0; i < userNameLength; i++) {
            if (temp.username[i] != username[i]) {
                validUsername = 0;
            }
        }
        for (int i = 0; i < passwordLength; i++) {
            if (temp.password[i] != password[i]) {
                validPassword = 0;
            }
        }
        if (validUsername && validPassword) {
            adminDB.close();
            return 1;
        } else if (validUsername && !validPassword) {
            char tryAgain[SIZE];
            do {
                cout << "Incorrect Password, Try Again: ";
                cin>>tryAgain;
                
                validPassword = 1;
                passwordLength = 0;
                t = tryAgain[passwordLength];
                while (t != '\0') {
                    passwordLength++;
                    t = tryAgain[passwordLength];
                }
        
                for (int i = 0; i < passwordLength; i++) {
                    if (temp.password[i] != tryAgain[i]) {
                        validPassword = 0;
                    }
                }
            } while (!validPassword);
            
            adminDB.close();
            return 1;
        }
    }
    adminDB.close();
    return 0;
}

void displayLeaderboard() {
    fstream userDB("UserData.bin", ios::in | ios::app | ios::binary);
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

void gameLoop(Board &board, char username[]) {
    int playerTurn = 1;
    while (!board.gameOver()) { //Game ends when either side as 0 marbles in all pits

        if (playerTurn == 1) {
            int play, marbles;
            board.printBoard();
            cout << endl;
            cout << username << "'s Turn. Enter a number 1 - 6 (L to R)" << endl;
            //cin>>play;
            play = (rand() % 6) + 1;

            int currCell = play + 1;
            board.playerOneMove(currCell, play, marbles);
            currCell--; //Back off one to check if capture or go again

            board.checkOneMove(currCell, playerTurn);
        } else {
            int play, marbles;
            board.printBoard();
            cout << endl;
            cout << "Player 2's Turn. Enter a number 1 - 6 (L to R)" << endl;
            play = (rand() % 6) + 1;
            cout << "Player 2 Selected Cell " << play << endl << endl;

            play = 14 - play;
            int currCell = play + 1;
            board.playerTwoMove(currCell, play, marbles);
            currCell--;

            board.checkTwoMove(currCell, playerTurn);
        }
        cout << endl;

    }



}