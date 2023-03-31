#ifndef MANCALA7_H
#define MANCALA7_H

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



const int USERNAME_LENGTH = 12;
const int PASSWORD_LENGTH = 12;

struct UserInfo {
    string username;
    string password;
    bool adminFlag;
    bool status;
};

struct PlayerData {
    string username;
    int win;
    int loss;
    int points;
};

#endif /* MANCALA7_H */

