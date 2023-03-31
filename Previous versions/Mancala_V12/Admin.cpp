#include "Admin.h"

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

void Admin::printAllUserInfo() {
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

void Admin::printAllPlayerData() {
    cout << endl << "PLAYER DATA" << endl << endl;
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

void Admin::changeUserStatus(string username, bool status) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.status = status;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::changeUserPassword(string username, string password) {
    bool found = false;
    for (auto& user : userInfo) {
        if (user.username == username) {
            // User found
            found = true;
            user.password = password;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::writeUserInfoChanges() {
    char tempUsernameLength = 0;
    char tempPasswordLength = 0;
    fstream binarySignInFile;

    binarySignInFile.open("UserInfo.bin", ios::out | ios::binary);
    if (!binarySignInFile.is_open()) {
        // Handle the error here
        cout << "Failed to open UserInfo.bin in \"writeUserInfoChanges\" ";
        cout << endl;
        exit(1);
    }

    binarySignInFile.seekp(0, ios::beg);

    for (int i = 0; i < userInfo.size(); i++) {
        tempUsernameLength = userInfo[i].username.size();
        tempPasswordLength = userInfo[i].password.size();

        binarySignInFile.write(&tempUsernameLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].username[0], tempUsernameLength);
        binarySignInFile.write(&tempPasswordLength, sizeof (char));
        binarySignInFile.write(&userInfo[i].password[0], tempPasswordLength);
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].adminFlag),
                sizeof (bool));
        binarySignInFile.write(reinterpret_cast<char*> (&userInfo[i].status),
                sizeof (bool));
    }
    userInfo.clear();
    binarySignInFile.close();
}

Admin::Admin(string u) {
    username = u;
}

void Admin::displayMenu() {
    cout << "Welcome to the Admin Menu " << username << endl << endl;
    cout << "USER SIGN-IN INFORMATION OPTIONS:" << endl;
    cout << "To display all User Sign-in Information press (1)" << endl;
    cout << "To search for a user's Sign-In information press (2)" << endl;
    cout << "To change a user's password press (3) " << endl;
    cout << "To change a user's account status press (4)" << endl << endl;

    cout << "PLAYER DATA OPTIONS:" << endl;
    cout << "To display all Player Data press (5)" << endl;
    cout << "To search for a user's Player Data press (6)" << endl;
    cout << "To change a user's win count press (7)" << endl;
    cout << "To change a user's loss count press (8)" << endl;
    cout << "To change a user's point count press (9)" << endl << endl;
    cout << "Finally, to exit press (-1)" << endl;
    cout << "Enter input: ";
}

void Admin::findUsername(string usernameSearch, bool flag) {
    bool found = false;
    int index = 0;
    if (flag) {
        for (const auto& user : userInfo) {
            if (user.username == usernameSearch) {
                // User found
                found = true;
                userInfoIndex = index;
                break;
            }
            index++;
        }
    } else {
        for (const auto& player : playerData) {
            if (player.username == usernameSearch) {
                // User found
                found = true;
                playerDataIndex = index;
                break;
            }
            index++;
        }
    }
    if (!found) {
        cout << "User " << usernameSearch << " not found" << endl;
    }
}

void Admin::displayUsersInfo(string usernameSearch) {
    findUsername(usernameSearch, 1);
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    cout << setw(25) << userInfo[userInfoIndex].username;
    cout << setw(25) << userInfo[userInfoIndex].password;
    cout << setw(25) << (userInfo[userInfoIndex].adminFlag ? "True" : "False");
    cout << setw(25) << (userInfo[userInfoIndex].status ? "Active" : "Inactive");
    cout << endl;
}

void Admin::displayPlayersData(string usernameSearch) {
    findUsername(usernameSearch, 0);
    cout << endl << "PLAYER DATA" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "WIN";
    cout << setw(25) << "LOSS";
    cout << setw(25) << "POINTS" << endl;
    cout << setw(25) << playerData[playerDataIndex].username;
    cout << setw(25) << playerData[playerDataIndex].win;
    cout << setw(25) << playerData[playerDataIndex].loss;
    cout << setw(25) << playerData[playerDataIndex].points << endl;
}

void Admin::changePlayerWin(string username, int win) {
    bool found = false;
    for (auto& player : playerData) {
        if (player.username == username) {
            // User found
            found = true;
            player.win = win;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::changePlayerLoss(string username, int loss) {
    bool found = false;
    for (auto& player : playerData) {
        if (player.username == username) {
            // User found
            found = true;
            player.loss = loss;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::changePlayerPoints(string username, int points) {
    bool found = false;
    for (auto& player : playerData) {
        if (player.username == username) {
            // User found
            found = true;
            player.points = points;
            break;
        }
    }

    if (!found) {
        cout << "User " << username << " not found" << endl;
    }
}

void Admin::writePlayerDataChanges() {
    char tempUsernameLength = 0;
    fstream data;
    data.open("PlayerData.bin", ios::out | ios::binary);
    data.seekp(0, ios::beg);
    for (int i = 0; i < playerData.size(); i++) {
        tempUsernameLength = playerData[i].username.size();
        data.write(&tempUsernameLength, sizeof (char));
        data.write(&playerData[i].username[0], tempUsernameLength);
        data.write(reinterpret_cast<char*> (&playerData[i].win),
                sizeof (int));
        data.write(reinterpret_cast<char*> (&playerData[i].loss),
                sizeof (int));
        data.write(reinterpret_cast<char*> (&playerData[i].points),
                sizeof (int));
    }
    playerData.clear();
    data.close();
}