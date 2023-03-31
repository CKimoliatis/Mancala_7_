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

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    SignIn interface;
    int playerTurn = 1;
    string player2 = "bot";

    signInInterface(interface);

    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
        Admin admin;
        admin.readUserInfo();
        admin.printUserInfo();
        cout << endl << endl;
        admin.readPlayerData();
        admin.printPlayerData();
        
        admin.changeStatus("pingram1", false);
        admin.writeChanges();
        admin.readUserInfo();
        admin.printUserInfo();
        cout << endl << endl;
        admin.readPlayerData();
        admin.printPlayerData();
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