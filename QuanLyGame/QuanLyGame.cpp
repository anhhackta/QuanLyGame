#include <iostream>
#include "AccountManager.h"
#include "GameRPG.h"
using namespace std;
int main() {
    AccountManager manager;
    manager.loadData("Data.txt");

    string username, password;
    cout << "Nhập Username: ";
    cin >> username;
    cout << "Nhập Password: ";
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
            cout << "Tài khoản hoặc mật khẩu không đúng\n";
        }
    }
    //startGame();

    return 0;
}