#include "Mancala7.h"
#include "Player.h"

#ifndef PLAYERRECORD_H
#define PLAYERRECORD_H

class PlayerRecord {
private:
    vector<PlayerData> data;
    PlayerData temporaryData;
public:
    PlayerRecord(Player* player);
    void writePlayerData();
    void readPlayerData(vector<PlayerData>&);
    int findUsername(vector<PlayerData>&);
    void writeVectorData(vector<PlayerData>&, fstream&);
};


#endif /* PLAYERRECORD_H */

