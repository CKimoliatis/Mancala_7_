#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
    private:
      string name;
      int win;
      int loss;

    public:
      Player() {
        name = "";
        win = 0;
        loss = 0;
      }
      Player(string n) {
        name = n;
        win = 0;
        loss = 0;
      }
      Player(string n, int w, int l) {
        name = n;
        win = w;
        loss = l;
      }
      void setName(string n) {
          name = n; 
      }
      void setWin(int w) {
          win = w; 
      }
      void addWin() {
          win++; 
      }
      void setLoss(int l) {
          loss = l; 
      }
      void addLoss() {
          loss++; 
      }
      string getName() { 
          return name; 
      }
      int getWin() { 
          return win; 
      }
      int getLoss() { 
          return loss; 
      }
      void print() {
        cout << "Name: " << name << endl;
        cout << "Wins: " << win << endl;
        cout << "Losses: " << loss << endl;
      }
};

#endif /* PLAYER_H_ */
