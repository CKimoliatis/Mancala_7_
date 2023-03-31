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

    void changeStatus(string user, bool status) {
        for (UserInfo &p : userInfo) {
            if (user == p.username) {
                p.status = status;
            }
        }
    }

    void writeChanges() {
        fstream binarySignInFile;
        binarySignInFile.open("UserInfo.bin", ios::out | ios::binary);
        char tempUsernameLength = 0; // User's username length 
        char tempPasswordLength = 0; // User's password length

        for (UserInfo &information : userInfo) {
            tempUsernameLength = information.username.size();
            tempPasswordLength = information.password.size();
            binarySignInFile.write(&tempUsernameLength, sizeof (char));
            binarySignInFile.write(&information.username[0], tempUsernameLength);
            binarySignInFile.write(&tempPasswordLength, sizeof (char));
            binarySignInFile.write(&information.password[0], tempPasswordLength);
            binarySignInFile.write(reinterpret_cast<char*> (&information.adminFlag),
                    sizeof (bool));
            binarySignInFile.write(reinterpret_cast<char*> (&information.status),
                    sizeof (bool));
        }
        binarySignInFile.close();
        // Write username, password, and admin status to the binary file

    }
};
#endif /* ADMIN_H */

