#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct PlayerData {
    string username;
    int win;
    int loss;
    int points;
};

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
    PlayerData data;
    fstream playerData;

public:

    Player() {
        data.username = "";
        data.win = 0;
        data.loss = 0;
    }

    Player(string n) {
        data.username = n;
        data.win = 0;
        data.loss = 0;
    }

    Player(string n, int w, int l) {
        data.username = n;
        data.win = w;
        data.loss = l;
    }

    ~Player();
    
    void setName(string n) {
        data.username = n;
    }

    void setWin(int w) {
        data.win = w;
    }

    void addWin() {
        data.win++;
    }

    void setLoss(int l) {
        data.loss = l;
    }

    void addLoss() {
        data.loss++;
    }
    
    void setPoints(int p){
        data.points = p;
    }

    string getName() {
        return data.username;
    }

    int getWin() {
        return data.win;
    }

    int getLoss() {
        return data.loss;
    }
    
    int getPoints() {
        return data.points;
    }
    void print() {
        cout << "Name: " << data.username << endl;
        cout << "Wins: " << data.win << endl;
        cout << "Losses: " << data.loss << endl;
        cout << "Points: " << data.points << endl;
    }
};

Player::~Player(){
    char tempUsernameLength = data.username.size();
    playerData.open("PlayerData.bin", ios::app | ios::binary);
    playerData.write(&tempUsernameLength, sizeof (char));
    playerData.write(&data.username[0], tempUsernameLength);
    playerData.write(reinterpret_cast<char*> (&data.win),
            sizeof (bool));
    playerData.write(reinterpret_cast<char*> (&data.loss),
            sizeof (bool));
    playerData.write(reinterpret_cast<char*> (&data.points),
            sizeof (bool));
    playerData.close();
}
#endif /* PLAYER_H_ */
