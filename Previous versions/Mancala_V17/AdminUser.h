/* 
 * File:   Admin.h
 * Author: paulingram
 *
 * Created on March 30, 2023, 10:37 PM
 */
#include "User.h"

struct Admin {
    char username[SIZE];
    char password[SIZE];
};

#ifndef ADMIN_H
#define ADMIN_H

class AdminUser {
private:
    vector<UserInfo> users;

public:

    AdminUser() {
        int choice;
        do {
            cout << endl << "Welcome to the Admin Menu" << endl;
            cout << " 1) Print All Users" << endl;
            cout << " 2) Change User Score" << endl;
            cout << " 3) Change User Password" << endl;
            cout << " 4) Change User Status" << endl;
            cout << " 5) Add an Admin" << endl;
            cout << " 6) Display Admins" << endl;
            cout << "-1) Log Out" << endl;
            cin>>choice;

            if (choice == 1) {
                printUsers();
            } else if (choice == 2) {
                changeUserScore();
            } else if (choice == 3) {
                changeUserPassword();
            } else if (choice == 4) {
                changeUserStatus();
            } else if (choice == 5) {
                addAdmin();
            } else if (choice == 6) {
                printAdmins();
            }

        } while (choice != -1);
    };

    void printUsers() {
        fstream userDB("UserData.bin", ios::in | ios::app | ios::binary);
        UserInfo temp;

        cout << endl << "Username \t Password \t Wins \t High Score \t Status" << endl << endl;
        userDB.seekg(ios::beg);
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            cout << left << setw(17);
            cout << boolalpha;
            cout << temp.username << setw(17);
            cout << temp.password;
            cout << temp.wins << "\t     ";
            cout << temp.highScore << "\t         ";
            cout << temp.status;
            cout << endl;
        }

        userDB.close();
    }

    void printAdmins() {
        fstream adminDB("AdminData.bin", ios::in | ios::app | ios::binary);
        Admin temp;

        cout << endl << "Username \t Password" << endl << endl;
        adminDB.seekg(ios::beg);
        while (adminDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            cout << left << setw(17);
            cout << temp.username << setw(17) << temp.password << endl;
        }
        adminDB.close();
    }

    void readUsers() {
        fstream userDB("UserData.bin", ios::in | ios::app | ios::binary);
        UserInfo temp;
        vector<UserInfo> newusers;
        users = newusers;

        userDB.seekg(ios::beg);
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            users.push_back(temp);
        }
        userDB.clear();
        userDB.close();
    }

    void changeUserScore() {
        char name[SIZE];
        int score;
        cout << "Enter the Username for the Score You Would Like to Change : ";
        cin>>name;
        cout << "Enter the New Score for the User : ";
        cin>>score;

        readUsers();

        for (UserInfo &user : users) {
            if (!strcmp(user.username, name)) {
                user.highScore = score;
            }
        }

        writeUsers();
    }

    void changeUserStatus() {
        char name[SIZE];
        bool status;
        cout << "Enter the Username for the Score You Would Like to Change : ";
        cin>>name;
        cout << "Enter the New Status for the User (1 or 0): ";
        cin>>status;

        readUsers();

        for (UserInfo &user : users) {
            if (!strcmp(user.username, name)) {
                user.status = status;
            }
        }

        writeUsers();
    }

    void changeUserPassword() {
        char name[SIZE];
        char pass[SIZE];
        cout << "Enter the Username for the Password You Would Like to Change : ";
        cin>>name;
        cout << "Enter the New Password for the User : ";
        cin>>pass;

        readUsers();

        for (UserInfo &user : users) {
            if (!strcmp(user.username, name)) {
                strcpy(user.password, pass);
            }
        }

        writeUsers();
    }

    void writeUsers() {
        fstream userDB("UserData.bin", ios::out | ios::binary);
        userDB.seekp(0, ios::beg);
        for (UserInfo user : users) {
            userDB.write(reinterpret_cast<char *> (&user), sizeof (user));
        }

        userDB.close();
    }

    void addAdmin() {
        //Populates admin DB
        char user[SIZE], pass[SIZE];
        cout << "Enter the User Name for the Admin : ";
        cin>>user;
        cout << "Enter the Password for the Admin : ";
        cin>>pass;
        Admin testadmin;
        strcpy(testadmin.username, user);
        strcpy(testadmin.password, pass);
        fstream adminDB("AdminData.bin", ios::in | ios::app | ios::binary);
        adminDB.seekp(ios::app);
        adminDB.write(reinterpret_cast<char *> (&testadmin), sizeof (testadmin));
        adminDB.close();
    }

};

#endif /* ADMIN_H */

