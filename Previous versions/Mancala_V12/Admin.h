#ifndef ADMIN_H
#define ADMIN_H

#include "Mancala7.h"

class Admin {
private:
    string username;
    vector<UserInfo> userInfo;
    int userInfoIndex;
    vector<PlayerData> playerData;
    int playerDataIndex;
public:
    Admin(string u);
    void readUserInfo();
    void printAllUserInfo();
    void changeUserStatus(string username, bool status);
    void changeUserPassword(string username, string password);
    void writeUserInfoChanges();
    void readPlayerData();
    void printAllPlayerData();
    void displayMenu();
    void findUsername(string usernameSearch, bool flag);
    void displayUsersInfo(string usernameSearch);
    void displayPlayersData(string usernameSearch);
    void changePlayerWin(string username, int win);
    void changePlayerLoss(string username, int loss);
    void changePlayerPoints(string username, int points);
    void writePlayerDataChanges();
};


#endif /* ADMIN_H */

