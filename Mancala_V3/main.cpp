#include "Board.h"

int main() {
  Board board;
  int playerTurn = 1;        //Int value to alternate turns

  while(!board.gameOver()){   //Game ends when either side as 0 marbles in all pits
    if(playerTurn == 1){
      int play, marbles;
      board.printBoard();
      cout<<"Player 1's Turn. Enter a number 1 - 6 (L to R)"<<endl;
      cin>>play;

      int currCell = play + 1;
      board.playerOneMove(currCell, play, marbles);
      currCell--; //Back off one to check if capture or go again
      
      board.checkOneMove(currCell, playerTurn);
    }
    else{
      int play, marbles;
      board.printBoard();
      cout<<"Player 2's Turn. Enter a number 1 - 6 (L to R)"<<endl;
      cin>>play;

      play = 14 - play;
      int currCell = play + 1;
      board.playerTwoMove(currCell, play, marbles);
      currCell--;
      
      board.checkTwoMove(currCell, playerTurn);
    }
  }
}