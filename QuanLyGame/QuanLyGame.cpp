#include <iostream>
#include "AccountManager.h"
using namespace std;
int main() {
    AccountManager manager;
    manager.loadData("Data.txt");

    string username, password;
    double balance = 0.0;
    int id,choice;
    do {
        cout << "======================================\n";
        cout << "|                                     |\n";
        cout << "|              QuanLyGame             |\n";
        cout << "|                                     |\n";
        cout << "======================================\n";
        cout << "|                                     |\n";
        cout << "|  1. Login                           |\n";
        cout << "|  2. Register                        |\n";
        cout << "|  3. Exit                            |\n";
        cout << "|                                     |\n";
        cout << "======================================\n";
        cout << "Choice : ";
        cin >> choice;
        switch (choice)
        {
            case 1 : {
                cout << "Input the Username: ";
                cin >> username;
                cout << "Input the Password: ";
                cin >> password;

                if (username == "admin" && password == "admin123") {
                    manager.adminMenu();
                }
                else {
                    Account* user = manager.findAccount(username);
                    if (user && user->getPassword() == password) {
                        manager.userMenu(user);
                    }
                    else {
                        cout << "Account or password is incorrect!\n";
                    }
                }
                break;
            }
            case 2: {
                cout << "Bonus 1000$\n";
                cout << "Enter ID (int): ";
                cin >> id;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                balance += 1000;
                manager.addAccount(new DefaultAcc(id, username, password, balance));
                manager.saveData("Data.txt");
                break;
            }

        default:
            break;
        }
    } while (choice != 3);
    
 

    return 0;
}