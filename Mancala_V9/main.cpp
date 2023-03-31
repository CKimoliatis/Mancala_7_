#include "Mancala7.h"
#include "Player.h"
#include "SignIn.h"
#include "Board.h"
#include "PlayerRecord.h"

void readUserInfo(fstream&, vector<UserInfo>&);
void printUserInfo(const vector<UserInfo>&);
void readPlayerData(fstream&, vector<PlayerData>&);
void printPlayerData(const vector<PlayerData>&);

int main() {
    SignIn interface;
    vector<UserInfo> userData;
    vector<PlayerData> playerData;
    fstream userInfoBinaryFile;
    fstream playerDataBinaryFile;
    int playerTurn = 1;
    string player2 = "bot";

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


    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
        userInfoBinaryFile.open("UserInfo.bin", ios::in | ios::binary);
        playerDataBinaryFile.open("PlayerData.bin", ios::in | ios::binary);
        readUserInfo(userInfoBinaryFile, userData);
        printUserInfo(userData);
        cout << endl << endl;
        readPlayerData(playerDataBinaryFile, playerData);
        printPlayerData(playerData);
        userInfoBinaryFile.close();
        playerDataBinaryFile.close();

    } else {
        cout << "Normal User" << endl;
        Player *p1 = new Player(interface.getUsername());
        Player *p2 = new Player(player2);
        Board board(p1, p2);
        while (!board.getGameStatus()) { //Game ends when either side as 0 marbles in all pits           
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
        cout << endl;
        board.printBoard();

        PlayerRecord player1Record(p1);
        player1Record.writePlayerData();

        PlayerRecord player2Record(p2);
        player2Record.writePlayerData();

        delete p1;
        delete p2;
    }
    return 0;
}

void readUserInfo(fstream& userInfo, vector<UserInfo>& userData) {
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    UserInfo temp;
    userInfo.seekg(0, ios::beg);

    while (userInfo.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        userInfo.read(&temp.username[0], tempUsernameLength);

        userInfo.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        userInfo.read(&temp.password[0], tempPasswordLength);
        userInfo.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        userInfo.read(reinterpret_cast<char*>
                (&temp.status), sizeof (bool));
        userData.push_back(temp);
    }
}

void printUserInfo(const vector<UserInfo>& userData) {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    for (int i = 0; i < userData.size(); i++) {
        cout << setw(25) << userData[i].username;
        cout << setw(25) << userData[i].password;
        cout << setw(25) << userData[i].adminFlag;
        cout << setw(25) << (userData[i].status == true ? 'T' : 'F') << endl;
    }
}

void readPlayerData(fstream& playerData, vector<PlayerData>& data) {
    char tempUsernameLength = 0; // User's username length 
    PlayerData temp;
    playerData.seekg(0, ios::beg);

    while (playerData.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        playerData.read(&temp.username[0], tempUsernameLength);
        playerData.read(reinterpret_cast<char*> (&temp.win),
                sizeof (int));
        playerData.read(reinterpret_cast<char*> (&temp.loss),
                sizeof (int));
        playerData.read(reinterpret_cast<char*> (&temp.points),
                sizeof (int));
        data.push_back(temp);
    }
}

void printPlayerData(const vector<PlayerData>& data) {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "WIN";
    cout << setw(25) << "LOSS";
    cout << setw(25) << "POINTS" << endl;
    for (int i = 0; i < data.size(); i++) {
        cout << setw(25) << data[i].username;
        cout << setw(25) << data[i].win;
        cout << setw(25) << data[i].loss;
        cout << setw(25) << data[i].points << endl;
    }
}