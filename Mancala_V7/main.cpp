#include "SignIn.h"

int main() {
    int playerTurn = 1;
    Leaderboard ldrbrd;
    SignIn interface;
    string player2 = "bot";
    
    interface.displayMenu();
    
    while (!interface.getExitSignIn()) {
        if (interface.getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else if (interface.getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            interface.validateAdminKey();
            interface.setUsername();
            interface.setPassword();
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
    
    Player *p1 = new Player(interface.getUsername());
    Player *p2 = new Player(player2);
    Board board(p1, p2);
    
    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
        
    } 
    else {
        cout << "Normal User" << endl;
        while(!board.gameOver()){   //Game ends when either side as 0 marbles in all pits           
            if(playerTurn == 1){
              int currCell;
              board.printBoard();

              board.playerOneMove(currCell);

              board.checkOneMove(currCell, playerTurn);
            }
            else{
              int currCell;
              board.printBoard();

              board.playerTwoMove(currCell);

              board.checkTwoMove(currCell, playerTurn);
            }
        }
    }
    
    
    
}

