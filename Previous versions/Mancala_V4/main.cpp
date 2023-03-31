#include "Board.h"

int main() {
  int playerTurn = 1;        //Int value to alternate turns
  string playerOne;
  
  cout<<"Enter Player 1's name: ";
  cin>>playerOne;

  Board board(playerOne);
  
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

