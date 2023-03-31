#include <string>
using namespace std;

#ifndef USERINFOSTRUCT_H
#define USERINFOSTRUCT_H

const int USERNAME_LENGTH = 12;
const int PASSWORD_LENGTH = 12;

struct UserInfo {
    string username;
    string password;
    bool adminFlag;
    bool status;
};

#endif /* USERINFOSTRUCT_H */

