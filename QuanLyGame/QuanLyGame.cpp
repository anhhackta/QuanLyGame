#include <iostream>
#include "AccountManager.h"
using namespace std;
int main() {
    AccountManager manager;
    manager.loadData("Data.txt");

    string username, password;
    cout << "======================================\n";
    cout << "|                                     |\n";
    cout << "|              QuanLyGame             |\n";
    cout << "|                                     |\n";
    cout << "======================================\n";
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
 

    return 0;
}