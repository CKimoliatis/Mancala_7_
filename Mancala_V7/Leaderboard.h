#include "Board.h"

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

bool compare(Player *p1, Player *p2) { return (p2->getWin() < p1->getWin()); }

class Leaderboard { // Records
private:
  vector<Player *> p;
  int Pcount;

public:
  Leaderboard() { 
      Pcount = 0; 
  }
  
  void addPlayer(Player *n) {
    p.push_back(n);
    Pcount++;
  }
  
  void delPlayer(string name) {
    vector<Player *>::iterator it;
    it = p.begin();
    for (int i = 0; i < p.size(); i++) {
      if (name == p[i]->getName()) {
        p.erase(it);
        Pcount--;
        break;
      }
      it++;
    }
  }
  
  void print() {
    sort(p.begin(), p.end(), compare);
    int i = 1;
    for (auto x : p) {
      cout << i << ". " << endl;
      x->print();
      i++;
    }
  }

  void readBoard() {
    fstream file("board.bin", ios::in | ios::binary);
    if (!file) {
      cerr << "error opening file" << endl;
      return;
    }
    file.seekg(0, ios::end); // move the file pointer to the end
    int size = file.tellg(); // get the size of the file
    file.seekg(0, ios::beg); // move the file pointer back to the beginning

    // read the data for each Player object and create a new Player object for
    // each one
    while (file.tellg() < size) {
      string name;
      int win, loss;
      file.read(reinterpret_cast<char *>(&win), sizeof(int));
      file.read(reinterpret_cast<char *>(&loss), sizeof(int));
      getline(file, name);
      Player *player = new Player(name, win, loss);
      addPlayer(player);
    }
    file.close();
  }

  void writeBoard() {
    fstream file("board.bin", ios::out | ios::binary | ios::trunc);
    if (!file) {
      cerr << "error opening file" << endl;
      return;
    }
    // write the data for each Player object to the file
    for (const auto &player : p) {
      int win = player->getWin();
      int loss = player->getLoss();
      string name = player->getName();
      file.write(reinterpret_cast<char *>(&win), sizeof(int));
      file.write(reinterpret_cast<char *>(&loss), sizeof(int));
      file << name << endl;
    }
    file.close();
  }
};

#endif /* LEADERBOARD_H */

