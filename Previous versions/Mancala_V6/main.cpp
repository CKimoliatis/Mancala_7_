#include "SignIn.h"

int main() {
    int playerTurn = 1;
    Leaderboard ldrbrd;
    SignIn interface;
    string player1, player2;
    
    cout<<"Player 1 Name : ";
    cin>>player1;
    cout<<"Player 2 Name : ";
    cin>>player2;
   
    Player *p1 = new Player(player1);
    Player *p2 = new Player(player2);
    
    Board board(p1, p2);
 
    interface.displayMenu();
    
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

