#ifndef ADMIN_H
#define ADMIN_H

#include "Mancala7.h"

class Admin {
private:
    vector<UserInfo> userInfo;
    vector<PlayerData> playerData;
public:
    void readUserInfo();
    void printUserInfo();
    void readPlayerData();
    void printPlayerData();
};

void Admin::readUserInfo() {
    fstream information;
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    UserInfo temp;

    information.open("UserInfo.bin", ios::in | ios::binary);

    information.seekg(0, ios::beg);

    while (information.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        information.read(&temp.username[0], tempUsernameLength);

        information.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        information.read(&temp.password[0], tempPasswordLength);
        information.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        information.read(reinterpret_cast<char*>
                (&temp.status), sizeof (bool));
        userInfo.push_back(temp);
    }
    information.close();
}

void Admin::printUserInfo() {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    for (int i = 0; i < userInfo.size(); i++) {
        cout << setw(25) << userInfo[i].username;
        cout << setw(25) << userInfo[i].password;
        cout << setw(25) << (userInfo[i].adminFlag ? "True" : "False");
        cout << setw(25) << (userInfo[i].status ? "Active" : "Inactive");
        cout << endl;
    }
}

void Admin::readPlayerData() {
    fstream data;
    char tempUsernameLength = 0; // User's username length 
    PlayerData temp;

    data.open("PlayerData.bin", ios::in | ios::binary);

    data.seekg(0, ios::beg);

    while (data.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        data.read(&temp.username[0], tempUsernameLength);
        data.read(reinterpret_cast<char*> (&temp.win),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.loss),
                sizeof (int));
        data.read(reinterpret_cast<char*> (&temp.points),
                sizeof (int));
        playerData.push_back(temp);
    }
    data.close();
}

void Admin::printPlayerData() {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "WIN";
    cout << setw(25) << "LOSS";
    cout << setw(25) << "POINTS" << endl;
    for (int i = 0; i < playerData.size(); i++) {
        cout << setw(25) << playerData[i].username;
        cout << setw(25) << playerData[i].win;
        cout << setw(25) << playerData[i].loss;
        cout << setw(25) << playerData[i].points << endl;
    }
}


#endif /* ADMIN_H */

