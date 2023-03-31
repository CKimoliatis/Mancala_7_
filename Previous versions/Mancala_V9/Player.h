#include "Mancala7.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
    PlayerData data;
//    fstream playerData;

public:

    Player(string n) {
        data.username = n;
        data.win = 0;
        data.loss = 0;
    }

//    ~Player();

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

    void setPoints(int p) {
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

#endif /* PLAYER_H_ */
