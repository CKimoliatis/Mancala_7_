#include <iostream>
#include <vector>
using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

class Board{
  private:
    vector<int> cells;

  public:
    Board(){
      vector<int> temp(15, 4);
      cells = temp;
      cells[14] = 0;
      cells[7] = 0;
    }

    void playerTwoMove(int &currCell, int play, int marbles){
      marbles = cells[play]; //Gets the marbles in the played cell
      cells[play] = 0;       //Set the played cell to 0
      
      for(currCell; marbles; currCell++){ //Loop through all             subsequent cells and ++    
        if(currCell % 7){
          cells[(currCell%14)]++;
          marbles--;
        }
        else if(currCell % 14 == 0){
          cells[14]++;
          marbles--;
        }
      }
    }

    void checkTwoMove(int &currCell, int &playerTurn){
      if(8 <= currCell && currCell <= 13 && cells[currCell] == 1){
        cout<<endl;
        cout<<"Capture!"<<endl;
        cells[14] += (1 +  cells[14 - currCell]);
        cells[14 - currCell] = 0;
        cells[currCell] = 0;
        playerTurn = 1;
      }
      else if(currCell == 14){
        cout<<endl;
        cout<<"You have earned another turn, go again."<<endl;
      }
      else{
        playerTurn = 1;
      }
    }

    void checkOneMove(int &currCell, int &playerTurn){
      if(1 <= currCell && currCell <= 6 && cells[currCell] == 1){ //Check if in range 
        cout<<endl;
        cout<<"Capture!"<<endl;
        cells[7] += (1 +  cells[14 - currCell]); //Add to score bank the capture cell + 1
        cells[14 - currCell] = 0;                //Set captured pit to 0
        cells[currCell] = 0;                     //Set captee pit to 0
        playerTurn = 2;
      }
      else if(currCell == 7){ //Check if landed on score bank, don't change playerTurn
        cout<<endl;
        cout<<"You have earned another turn, go again."<<endl;
      }
      else{ //Else change turns
        playerTurn = 2;
      }
    }

    void playerOneMove(int &currCell, int play, int marbles){
      marbles = cells[play]; //Gets the marbles in the played cell
      cells[play] = 0;       //Set the played cell to 0
      
      for(currCell; marbles; currCell++){ //Loop through all subsequent cells and ++
        currCell = currCell % 14;         //Mod in case play has enough marbs to loop thru
        if(currCell != 0){                //If currCell != 0 means we are not on enemy score bank
          cells[(currCell%14)]++;
          marbles--;
        }
      }
    }

    void printBoard(){
      cout<<" "<<cells[13]<<"|"<<cells[12]<<"|"<<cells[11]<<"|"                    <<cells[10]<<"|"<<cells[9]           <<"|"<<cells[8]<<endl;
      cout<<cells[14]<<"==========="<<cells[7]<<endl;
      cout<<" "<<cells[1]<<"|"<<cells[2]<<"|"<<cells[3]<<"|"                <<cells[4]<<"|"<<cells[5]               <<"|"<<cells[6]<<endl;
    }

    bool gameOver(){
      return (cells[13]+cells[12]+cells[11]+cells[10]+cells[9]+cells[8] == 0) ||
        (cells[1]+cells[2]+cells[3]+cells[4]+cells[5]+cells[6] == 0);
    }
};


#endif /* BOARD_H_ */
