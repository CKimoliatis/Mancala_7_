/* 
 * File:   Admin.h
 * Author: paulingram
 *
 * Created on March 30, 2023, 10:37 PM
 */
#include "User.h"

struct Admin {
    string username;
    string password;
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
            cout << " 1) Change User Score" << endl;
            cout << " 2) Print All Users" << endl;
            cout << " 3) Change User Password" << endl;
            cout << " 4) Add an Admin" << endl;
            cout << " 5) Display Admins" << endl;
            cout << "-1) Log Out" << endl;
            cin>>choice;

            if (choice == 1) {
                changeUserScore();
            } else if (choice == 2) {
                printUsers();
            } else if (choice == 3) {
                changeUserPassword();
            } else if (choice == 4) {
                addAdmin();
            } else if (choice == 5) {
                printAdmins();
            }

        } while (choice != -1);
    };

    void printUsers() {
        fstream userDB("UserData.dat", ios::in | ios::app | ios::binary);
        UserInfo temp;

        cout << endl << "Username \t Password \t Wins \t High Score \t" << endl << endl;
        userDB.seekg(ios::beg);
        while (userDB.read(reinterpret_cast<char *> (&temp), sizeof (temp))) {
            cout << left << setw(17);
            cout << temp.username << setw(17) << temp.password << setw(10) << temp.wins << setw(10)
                    << temp.highScore << endl;
        }

        userDB.close();
    }

    void printAdmins() {
        fstream adminDB("AdminData.dat", ios::in | ios::app | ios::binary);
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
        fstream userDB("UserData.dat", ios::in | ios::app | ios::binary);
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
        string name;
        int score;
        cout << "Enter the Username for the Score You Would Like to Change : ";
        cin>>name;
        cout << "Enter the New Score for the User : ";
        cin>>score;

        readUsers();

        for (UserInfo &user : users) {
            if (user.username == name) {
                user.highScore = score;
            }
        }

        writeUsers();
    }

    void changeUserPassword() {
        string name;
        string pass;
        cout << "Enter the Username for the Password You Would Like to Change : ";
        cin>>name;
        cout << "Enter the New Password for the User : ";
        cin>>pass;

        readUsers();

        for (UserInfo &user : users) {
            if (user.username == name) {
                user.password = pass;
            }
        }

        writeUsers();
    }

    void writeUsers() {
        fstream userDB("UserData.dat", ios::out | ios::binary);
        userDB.seekp(0, ios::beg);
        for (UserInfo user : users) {
            userDB.write(reinterpret_cast<char *> (&user), sizeof (user));
        }

        userDB.close();
    }

    void addAdmin() {
        //Populates admin DB
        string user, pass;
        cout << "Enter the User Name for the Admin : ";
        cin>>user;
        cout << "Enter the Password for the Admin : ";
        cin>>pass;
        Admin testadmin;
        testadmin.username = user;
        testadmin.password = pass;
        fstream adminDB("AdminData.dat", ios::in | ios::app | ios::binary);
        adminDB.seekp(ios::app);
        adminDB.write(reinterpret_cast<char *> (&testadmin), sizeof (testadmin));
        adminDB.close();
    }

};

#endif /* ADMIN_H */

