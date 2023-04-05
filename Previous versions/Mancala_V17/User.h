/* 
 * File:   User.h
 * Author: paulingram
 *
 * Created on March 30, 2023, 7:54 PM
 */
#include "Board.h"

#ifndef USER_H
#define USER_H

const int SIZE = 31;

struct UserInfo {
    char username[SIZE];
    char password[SIZE];
    int highScore;
    int wins;
    int usernameLength;
    int passwordLength;
    bool active;
};

class User {
private:
    UserInfo info;

public:

    User() {
        info.highScore = 0;
        info.wins = 0;
        info.active = true;
        info.usernameLength = 0;
        info.passwordLength = 0;
    }

    void setUserScore(int score1, int score2) {
        fstream userDB("UserData.bin", ios::in | ios::out | ios::binary);
        UserInfo temp;

        info.highScore = max(info.highScore, score1);
        if (score1 > score2) {
            info.wins++;
        }
                
        userDB.seekg(ios::beg);
        int index = 0;
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            bool validUsername = 1;
            for (int i = 0; i < info.usernameLength; i++) {
                if (temp.username[i] != info.username[i]) {
                    validUsername = 0;
                }
            }
            if (validUsername) {
                userDB.clear();
                userDB.seekp(sizeof (info) * index, ios::beg);
                userDB.write(reinterpret_cast<char *> (&info), sizeof (info));
                userDB.close();
            }
            index++;
        }
    }

    void setUser(char user[], char password[]) {
        for (int i = 0; i < SIZE; i++) {
            info.username[i] = user[i];
        }
        for (int i = 0; i < SIZE; i++) {
            info.password[i] = password[i];
        }
        
        int userNameLength = 0;
        char t = info.username[userNameLength];
        while (t != '\0') {
            userNameLength++;
            t = info.username[userNameLength];
        }
        int passwordLength = 0;
        t = info.password[passwordLength];
        while (t != '\0') {
            passwordLength++;
            t = info.username[passwordLength];
        }
        info.highScore = 0;
        info.wins = 0;
        info.usernameLength = userNameLength;
        info.passwordLength = passwordLength;
        
        validateUser();

        cout << "User : " << info.username << endl;
    }

    void validateUser() {
        fstream userDB("UserData.bin", ios::in | ios::app | ios::binary);
        UserInfo temp;
        bool write = 1;

        userDB.seekg(ios::beg);
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            bool validUsername = 1, validPassword = 1;
            for (int i = 0; i < info.usernameLength; i++) {
                if (temp.username[i] != info.username[i]) {
                    validUsername = 0;
                }
            }
            for (int i = 0; i < info.passwordLength; i++) {
                if (temp.password[i] != info.password[i]) {
                    validPassword = 0;
                }
            }
            if (validUsername && validPassword) {
                write = 0;
            } else if (validUsername && !validPassword) {
                char tryAgain[SIZE];
                do {
                    validPassword = 1;
                    cout << "Incorrect Password, Try Again: ";
                    cin>>tryAgain;

                    for (int i = 0; i < info.passwordLength; i++) {
                        if (temp.password[i] != tryAgain[i]) {
                            validPassword = 0;
                        }
                    }
                } while (!validPassword);

                write = 0;
            }
        }

        userDB.clear();

        if (write) {
            userDB.seekp(ios::app);
            userDB.write(reinterpret_cast<char *> (&info), sizeof (info));
        }
    }

    bool getStatus() {
        return info.active;
    }

};

#endif /* USER_H */

