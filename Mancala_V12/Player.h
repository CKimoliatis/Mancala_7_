#include "Mancala7.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
    PlayerData data;

public:

    Player(string n);

    void setName(string n);

    void setWin(int w);

    void addWin();

    void setLoss(int l);
    void addLoss();
    void setPoints(int p);

    string getName();

    int getWin();

    int getLoss();

    int getPoints();

    void print();
};

#endif /* PLAYER_H_ */
