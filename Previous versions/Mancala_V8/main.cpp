#include "SignIn.h"
void readUserInfo(fstream&, vector<UserInfo>&);
void printUserInfo(const vector<UserInfo>&);

int main() {
    SignIn interface;
    vector<UserInfo> userData;
    fstream userInfoBinaryFile;
    fstream playerDataBinaryFile;

    interface.displayMenu();
    while (!interface.getExitSignIn()) {
        if (interface.getUserInput() == 'u') {
            // Create a normal user account
            cout << "Register for a Normal User account" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else if (interface.getUserInput() == 'a') {
            // Create an admin account
            cout << "Register for Admin account" << endl << endl;
            interface.validateAdminKey();
            interface.setUsername();
            interface.setPassword();
            interface.setStatus();
            // Store information to file
            interface.writeBinary();
            interface.setExitSignIn(true);
        } else {
            // Sign-in to an existing account
            cout << "Sign-In" << endl << endl;
            interface.setUsername();
            interface.setPassword();
            interface.validateUser();
            // If no account is found display an error and prompt user
            // to create an account or try again
            if (!interface.getExitSignIn()) {
                // The user only gets 5 attempts
                interface.displayError();
            }
        }
    }

    if (interface.getAdminStatus()) {
        cout << "Admin User" << endl;
        userInfoBinaryFile.open("UserInfo.bin", ios::in | ios::binary);
        readUserInfo(userInfoBinaryFile, userData);
        printUserInfo(userData);
        userInfoBinaryFile.close();
    } else {
        cout << "Normal User" << endl;
    }

    return 0;
}

void readUserInfo(fstream& userInfo, vector<UserInfo>& userData) {
    char tempUsernameLength = 0; // User's username length 
    char tempPasswordLength = 0; // User's password length
    UserInfo temp;
    userInfo.seekg(0, ios::beg);

    while (userInfo.read(&tempUsernameLength, sizeof (char))) {
        temp.username.resize(tempUsernameLength);
        userInfo.read(&temp.username[0], tempUsernameLength);

        userInfo.read(&tempPasswordLength, sizeof (char));
        temp.password.resize(tempPasswordLength);
        userInfo.read(&temp.password[0], tempPasswordLength);
        userInfo.read(reinterpret_cast<char*>
                (&temp.adminFlag), sizeof (bool));
        userInfo.read(reinterpret_cast<char*>
                (&temp.status), sizeof (bool));
        userData.push_back(temp);
    }
}

void printUserInfo(const vector<UserInfo>& userData) {
    cout << endl << "USER INFORMATION" << endl << endl;
    cout << left << setw(25);
    cout << "USERNAME";
    cout << setw(25) << "PASSWORD";
    cout << setw(25) << "ADMIN STATUS";
    cout << setw(25) << "ACCOUNT STATUS" << endl;
    for (int i = 0; i < userData.size(); i++) {
        cout << setw(25) << userData[i].username;
        cout << setw(25) << userData[i].password;
        cout << setw(25) << userData[i].adminFlag;
        cout << setw(25) << (userData[i].status == true ? 'T' : 'F') << endl;
    }
}