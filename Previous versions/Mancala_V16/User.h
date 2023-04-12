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
    bool status;
};

class User {
private:
    UserInfo info;

public:

    User() {
        strcpy(info.username, " ");
        strcpy(info.password, " ");
        info.highScore = 0;
        info.wins = 0;
    }

    void setUserScore(int score1, int score2) {
        fstream userDB("UserData.bin", ios::in | ios::out | ios::binary);
        UserInfo temp;
        
        info.highScore = max(info.highScore, score1);
        if(score1 > score2){
            info.wins++;
        }
        
        userDB.seekg(ios::beg);
        int index = 0;
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (UserInfo))) {
            if(!strcmp(temp.username, info.username)){
                userDB.clear();
                userDB.seekp(sizeof (info) * index, ios::beg);
                userDB.write(reinterpret_cast<char *> (&info), sizeof (info));
                userDB.close();
            }
            index++;
        }
    }

    void setUser(string user, string password) {
        strcpy(info.username, user.c_str());
        strcpy(info.password, password.c_str());
        info.highScore = 0;
        info.wins = 0;

        validateUser();

        cout << "User : " << info.username << endl;
    }

    void validateUser() {
        fstream userDB("UserData.bin", ios::in | ios::app | ios::binary);
        UserInfo temp;
        bool write = 1;

        userDB.seekg(ios::beg);
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            if (!strcmp(temp.username, info.username) && strcmp(temp.password, info.password)) {
                string password;
                do {
                    cout << "Incorrect Password Try Again : ";
                    cin>>password;
                } while (strcmp(password.c_str(), temp.password));
                info = temp;
                write = 0;
            } else if (!strcmp(temp.username, info.username) && !strcmp(temp.password, info.password)) {
                info = temp;
                write = 0;
            }
        }

        userDB.clear();

        if (write) {
            userDB.seekp(ios::app);
            userDB.write(reinterpret_cast<char *> (&info), sizeof (info));
        }
    }

};

#endif /* USER_H */

