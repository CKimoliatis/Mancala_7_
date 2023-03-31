#include <iostream>
#include <vector>
using namespace std;

#ifndef PLAYER_H_
#define PLAYER_H_

class Player{
  private:
    string name;
    int score;
  public:
    Player() {};
  
    Player(string s){
      name = s;
    }

    void setScore(int s){
      score = s;
    }

    int getScore(){
      return score;
    }

    void setName(string s){
      name = s;
    }

    string getName(){
      return name;
    }
};

#endif /* PLAYER_H_ */
