#include "PlayerRecord.h"

PlayerRecord::PlayerRecord(Player* player) {
        temporaryData.username = player->getName();
        temporaryData.win = player->getWin();
        temporaryData.loss = player->getLoss();
        temporaryData.points = player->getPoints();
    }

void PlayerRecord::writePlayerData() {
    fstream playerData;
    // Check if the file exists
    playerData.open("PlayerData.bin", ios::in | ios::binary);
    bool fileExists = playerData.is_open();
    playerData.close();

    // If the file does not exist, create it with the ios::out flag
    if (!fileExists) {
        playerData.open("PlayerData.bin", ios::out | ios::binary);
        playerData.close();
    }

    // Open the file with both ios::in and ios::out flags
    playerData.open("PlayerData.bin", ios::in | ios::out | ios::binary);

    if (playerData.eof())
        playerData.clear();

    char tempUsernameLength = 0;
    playerData.seekp(0, ios::end);
    if (playerData.tellp() == 0) {
        playerData.seekp(0, ios::beg);
        tempUsernameLength = temporaryData.username.size();
        playerData.write(&tempUsernameLength, sizeof (char));
        playerData.write(&temporaryData.username[0], tempUsernameLength);
        playerData.write(reinterpret_cast<char*> (&temporaryData.win),
                sizeof (int));
        playerData.write(reinterpret_cast<char*> (&temporaryData.loss),
                sizeof (int));
        playerData.write(reinterpret_cast<char*> (&temporaryData.points),
                sizeof (int));
    } else {
        readPlayerData(data);
        int index = findUsername(data);
        if (index != -1) {
            data[index].win += temporaryData.win;
            data[index].loss += temporaryData.loss;
            data[index].points = max(data[index].points, temporaryData.points);
            writeVectorData(data, playerData);
        } else {
            data.push_back(temporaryData);
            writeVectorData(data, playerData);
        }
    }
    playerData.close();
}

void PlayerRecord::readPlayerData(vector<PlayerData>& tempVec) {
    fstream playerData;
    playerData.open("PlayerData.bin", ios::in | ios::binary);
    char tempUsernameLength = 0; // User's username length 
    PlayerData temp;
    playerData.seekg(0, ios::beg);
    if (playerData.eof())
        playerData.clear();

    while (playerData.read(&tempUsernameLength, sizeof (char))) {

        temp.username.resize(tempUsernameLength);
        playerData.read(&temp.username[0], tempUsernameLength);
        playerData.read(reinterpret_cast<char*> (&temp.win),
                sizeof (int));
        playerData.read(reinterpret_cast<char*> (&temp.loss),
                sizeof (int));
        playerData.read(reinterpret_cast<char*> (&temp.points),
                sizeof (int));
        tempVec.push_back(temp);
    }
    playerData.close();
}

int PlayerRecord::findUsername(vector<PlayerData>& tempVec) {
    int index = 0;
    while (index < tempVec.size()) {

        if (temporaryData.username == tempVec[index].username) {
            return index;
        }
        index++;
    }
    return -1;
}

void PlayerRecord::writeVectorData(vector<PlayerData>& tempVec,
        fstream& playerData) {
    if (playerData.eof())
        playerData.clear();
    char tempUsernameLength = 0;
    playerData.seekp(0, ios::beg);
    for (int i = 0; i < tempVec.size(); i++) {
        tempUsernameLength = tempVec[i].username.size();
        playerData.write(&tempUsernameLength, sizeof (char));
        playerData.write(&tempVec[i].username[0], tempUsernameLength);
        playerData.write(reinterpret_cast<char*> (&tempVec[i].win),
                sizeof (int));
        playerData.write(reinterpret_cast<char*> (&tempVec[i].loss),
                sizeof (int));
        playerData.write(reinterpret_cast<char*> (&tempVec[i].points),
                sizeof (int));
    }
}