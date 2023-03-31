#include "Mancala7.h"
#include "Player.h"
#include "SignIn.h"
#include "Board.h"
#include "PlayerRecord.h"
#include "Admin.h"

void signInInterface(SignIn& interface);
void recordPlayerData(Player* player1, Player* player2);
void destroyPlayers(Player* player1, Player* player2);
void gameLoop(Board& board, int playerTurn);
void pointsLeaderboard();
void winsLeaderboard();
void printLeaderboard(const vector<PlayerData>& playerData);
bool compareWins(const PlayerData& a, const PlayerData& b);
bool comparePoints(const PlayerData& a, const PlayerData& b);

int main() {
    srand(static_cast<unsigned int> (time(0)));
    SignIn interface;
    int adminInput;
    int playerTurn = 1;
    string player2 = "bot";

    signInInterface(interface);

    if (interface.getAdminStatus()) {
        char exit;
        //        cout << "Admin User" << endl;
        Admin admin(interface.getUsername());
        admin.readUserInfo();
        admin.readPlayerData();
        while (exit != 'x' && exit != 'X' && exit != 'w' && exit != 'W') {
            admin.displayMenu();
            do {
                string tempUsername;
                string tempPassword;
                int tempWin;
                int tempLoss;
                int tempPoints;

                cin >> adminInput;
                if (adminInput == 1) {
                    admin.printAllUserInfo();
                    cout << "Enter next instruction: ";
                } else if (adminInput == 2) {
                    cout << "Enter the username of the user you'd like to see: ";
                    cin >> tempUsername;
                    admin.displayUsersInfo(tempUsername);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 3) {
                    cout << "Enter the username of the user's password you'd like";
                    cout << " to change: ";
                    cin >> tempUsername;
                    cout << "Enter the new password: ";
                    cin >> tempPassword;
                    admin.changeUserPassword(tempUsername, tempPassword);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 4) {
                    bool tempStatus;
                    cout << "Enter the username of the user's status you'd like to change: ";
                    cin >> tempUsername;
                    cout << "Press (1) to activate or (0) to deactivate: ";
                    cin >> tempStatus;
                    admin.changeUserStatus(tempUsername, tempStatus);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 5) {
                    admin.printAllPlayerData();
                    cout << "Enter next instruction: ";
                } else if (adminInput == 6) {
                    cout << "Enter the username of the player you'd like to see ";
                    cin >> tempUsername;
                    admin.displayPlayersData(tempUsername);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 7) {
                    cout << "Enter the username of the player who's wins you want to change: ";
                    cin >> tempUsername;
                    cout << "Enter how many wins you want the player to have now: ";
                    cin >> tempWin;
                    admin.changePlayerWin(tempUsername, tempWin);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 8) {
                    cout << "Enter the username of the player who's wins you want to change: ";
                    cin >> tempUsername;
                    cout << "Enter how many losses you want the player to have now: ";
                    cin >> tempLoss;
                    admin.changePlayerLoss(tempUsername, tempLoss);
                    cout << "Enter next instruction: ";
                } else if (adminInput == 9) {
                    cout << "Enter the username of the player who's wins you want to change: ";
                    cin >> tempUsername;
                    cout << "Enter how many points you want the player to have now: ";
                    cin >> tempPoints;
                    admin.changePlayerPoints(tempUsername, tempPoints);
                    cout << "Enter next instruction: ";
                }
            } while (adminInput != -1);
            cin.ignore();
            cout << "If you would like to write your changes press (w) else press (x) to exit or enter to go back into the admin menu: ";
            cin.get(exit);
            if (exit == 'W' || exit == 'w') {
                admin.writeUserInfoChanges();
                admin.writePlayerDataChanges();
            }
        }
    } else {
        cout << "Normal User" << endl;
        Player *p1 = new Player(interface.getUsername());
        Player *p2 = new Player(player2);
        Board board(p1, p2);
        gameLoop(board, playerTurn);
        cout << endl;
        board.printBoard();
        recordPlayerData(p1, p2);
        destroyPlayers(p1, p2);
    }
    cout << endl << endl;
    pointsLeaderboard();
    return 0;
}

void destroyPlayers(Player* player1, Player* player2) {
    delete player1;
    delete player2;
}

void recordPlayerData(Player* player1, Player* player2) {
    PlayerRecord player1Record(player1);
    player1Record.writePlayerData();
    PlayerRecord player2Record(player2);
    player2Record.writePlayerData();
}

void signInInterface(SignIn& interface) {
    interface.displayMenu();
    while (!interface.getExitSignIn()) {
        if (interface.getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else if (interface.getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            interface.validateAdminKey();
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else {
            // Sign-in to an existing account
            cout << "Sign-In" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.validateUser();
            // If no account is found display an error and prompt user
            // to create an account or try again
            if (!interface.getExitSignIn()) {
                // The user only gets 5 attempts
                interface.displayError();
            }
        }
    }
}

void gameLoop(Board& board, int playerTurn) {
    //Game ends when either side as 0 marbles in all pits   
    while (!board.getGameStatus()) {
        if (playerTurn == 1) {
            int currCell;
            board.printBoard();
            board.playerOneMove(currCell);
            board.checkOneMove(currCell, playerTurn);
            board.gameOver();
        } else {
            int currCell;
            board.printBoard();
            board.playerTwoMove(currCell);
            board.checkTwoMove(currCell, playerTurn);
            board.gameOver();
        }
    }
}

void pointsLeaderboard() {
    fstream data;
    char tempUsernameLength = 0; // User's username length 
    PlayerData temp;
    vector<PlayerData> playerData;

    data.open("PlayerData.bin", ios::in | ios::binary);

    data.seekg(0, ios::beg);

    while (data.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        data.read(&temp.username[0], tempUsernameLength);
        data.read(reinterpret_cast<char*> (&temp.win),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.loss),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.points),
                sizeof (int));
        playerData.push_back(temp);
    }
    data.close();
    sort(playerData.begin(), playerData.end(), comparePoints);
    printLeaderboard(playerData);
}

void winsLeaderboard() {
    fstream data;
    char tempUsernameLength = 0; // User's username length 
    PlayerData temp;
    vector<PlayerData> playerData;

    data.open("PlayerData.bin", ios::in | ios::binary);

    data.seekg(0, ios::beg);

    while (data.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        data.read(&temp.username[0], tempUsernameLength);
        data.read(reinterpret_cast<char*> (&temp.win),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.loss),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.points),
                sizeof (int));
        playerData.push_back(temp);
    }
    data.close();
    sort(playerData.begin(), playerData.end(), compareWins);
    printLeaderboard(playerData);
}

void printLeaderboard(const vector<PlayerData>& playerData) {
    cout << endl << "LEADERBOARD" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "WIN";
    cout << setw(25) << "LOSS";
    cout << setw(25) << "POINTS" << endl;

    int count = 0;

    for (const auto& player : playerData) {
        cout << setw(25) << player.username;
        cout << setw(25) << player.win;
        cout << setw(25) << player.loss;
        cout << setw(25) << player.points << endl;

        count++;

        if (count == 5) {
            break; // Exit the loop after the first 5 elements are printed
        }
    }
}

bool compareWins(const PlayerData& a, const PlayerData& b) {
    return a.win > b.win;
}

bool comparePoints(const PlayerData& a, const PlayerData& b) {
    return a.points > b.points;
}