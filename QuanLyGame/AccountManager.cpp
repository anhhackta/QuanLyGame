#include "AccountManager.h"
#include "DefaultAcc.h"
#include "VipAcc.h"
#include "GameRPG.h"
#include "caro.h"
#include "bigsmallgame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
AccountManager::~AccountManager() {
    for (auto account : accounts) {
        delete account;
    }
}

void AccountManager::loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        replace(line.begin(), line.end(), '-', ' ');
        istringstream iss(line);
        int id;
        string type, username, password, nickname;
        double balance;
        iss >> id >> type >> username >> password >> balance;
        if (type == "DefaultAcc") {
            accounts.push_back(new DefaultAcc(id, username, password, balance));
        }
        else if (type == "VipAcc") {
            iss >> nickname;
            accounts.push_back(new VipAcc(id, username, password, balance, nickname));
        }
    }

    file.close();
}

void AccountManager::saveData(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }
    // su dung dymanic de chuyen kieu giua con tro va tham so trong ke thua
    for (const auto& account : accounts) {
        if (auto* vip = dynamic_cast<VipAcc*>(account)) {
            file << vip->getId() << "-VipAcc-" << vip->getUsername() << "-" << vip->getPassword() << "-" << vip->getBalance() << "-" << vip->getNickname() << "\n";
        }
        else if (auto* def = dynamic_cast<DefaultAcc*>(account)) {
            file << def->getId() << "-DefaultAcc-" << def->getUsername() << "-" << def->getPassword() << "-" << def->getBalance() << "\n";
        }
    }

    file.close();
}

Account* AccountManager::findAccount(const string& username) {
    for (auto& account : accounts) {
        if (account->getUsername() == username) {
            return account;
        }
    }
    return nullptr;
}

void AccountManager::addAccount(Account* account) {
    accounts.push_back(account);
}

void AccountManager::deleteAccount(const string& username) {
    auto it = remove_if(accounts.begin(), accounts.end(), [&](Account* acc) {
        return acc->getUsername() == username;
        });
    for (auto iter = it; iter != accounts.end(); ++iter) {
        delete* iter;
    }
    accounts.erase(it, accounts.end());
}

void AccountManager::adminMenu() {
    int choice;
    do {
        
        cout << "========================\n";
        cout << "        Admin Menu      \n";
        cout << "========================\n";
        cout << "1. Add account\n";
        cout << "2. Delete Account\n";
        cout << "3. Find Account\n";
        cout << "4. Exit\n";
        cout << "Input the choice: ";
        cin >> choice;
        string username, password;
        int id;
        double balance = 0.0;
        switch (choice)
        {
            
            case 1: {

                cout << "Bonus 1000$";
                cout << "Enter ID (int): ";
                cin >> id;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                balance += 1000;
                addAccount(new DefaultAcc(id, username, password, balance));
                saveData("Data.txt");
                break;
            }
                
            case 2 :
                cout << "Input the username for delete: ";
                cin >> username;
                deleteAccount(username);
                saveData("Data.txt");
                break;
            case 3 :
                cout << "Input the username for search: ";
                cin >> username;
                Account* account = findAccount(username);
                if (account) {
                    account->displayAccountInfo();
                }
                else {
                    cout << "Account not found!\n";
                }
                break;
            
        }
       
    } while (choice != 4);
}

void AccountManager::userMenu(Account*& user) {
    int choice;
    if (dynamic_cast<VipAcc*>(user)) {
        cout << "\x1B[95m"; // Đổi màu chữ
    }
    do {
        cout << "========================\n";
        cout << "  Menu : " << user->getUsername() << endl;
        cout << "========================\n";
        cout << "1. Game RPG (hot)\n";
        cout << "2. Game Caro\n";
        cout << "3. Game BigSmall\n";
        cout << "4. Deposit\n";
        cout << "5. Withdrawal\n";
        cout << "6. Transfer\n";
        cout << "7. View info\n";
        cout << "8. Change password\n";
        cout << "9. Rank\n";
        cout << "0. Exit\n";
        cout << "Input the choice: ";
        cin >> choice;
        double amount;
        string username, newPassword;
        switch (choice) {
            case 1 :gamerpg(user);
                    saveData("Data.txt");
                    break;
            case 2 :gamecaro(user);
                    saveData("Data.txt");
                    break;
            case 3: game.play(user);
                    saveData("Data.txt");
                    break;
            case 4 :
            {
                cout << "Input the amount to deposit( 1000 to upgrade Vip Account): ";
                cin >> amount;
                user->setBalance(user->getBalance() + amount);
                if (user->getBalance() >= 1000 && dynamic_cast<DefaultAcc*>(user)) {
                    string nickname;
                    cout << "You have been upgraded to Vip Account. Enter Nickname: ";
                    cin >> nickname;
                    VipAcc* vip = new VipAcc(user->getId(), user->getUsername(), user->getPassword(), user->getBalance(), nickname);
                    auto it = find(accounts.begin(), accounts.end(), user);
                    if (it != accounts.end()) {
                        delete* it;
                        *it = vip;
                    }
                    user = vip;
                    cout << "Upgraded successfully!\n";
                }
                saveData("Data.txt");
                break;
            }
            case 5 : {
                cout << "Input the amount to withdraw: ";
                cin >> amount;
                if (user->getBalance() >= amount) {
                    user->setBalance(user->getBalance() - amount);
                    saveData("Data.txt");
                }
                else {
                    cout << "Insufficient balance\n";
                }
                break;
            }
            case 6 : {
                cout << "Input Username to transfer money: ";
                cin >> username;
                Account* recipient = findAccount(username);
                if (recipient) {
                    cout << "Input the amount to transfer: ";
                    cin >> amount;
                    if (user->getBalance() >= amount) {
                        user->setBalance(user->getBalance() - amount);
                        recipient->setBalance(recipient->getBalance() + amount);
                        saveData("Data.txt");
                        cout << "Successful money transfer!\n";
                    }
                    else {
                        cout << "Insufficient balance\n";
                    }
                }
                else {
                    cout << "Cannot find account to transfer!\n";
                }
                break;
            }
            case 7 : {
                user->displayAccountInfo();
                break;
            }
            case 8 : {
                cout << "Account : " << user->getUsername() << endl;
                cout << "Input a new password: ";
                cin >> newPassword;
                user->setPassword(newPassword);
                saveData("Data.txt");
                cout << "Password changed successfully!\n";
                break;
            }
            case 9 :  displayRanking();break;
            case 0: {
                break;
            }
        }
    } while (choice != 0);
    if (dynamic_cast<VipAcc*>(user)) {
        cout << "\033[0m";
    }

}

void AccountManager::displayRanking() {
    sort(accounts.begin(), accounts.end(), [](Account* a, Account* b) {
        return a->getBalance() > b->getBalance();
        });
    cout << "Rank:\n";
    for (const auto& account : accounts) {
        account->displayAccountInfo();
    }
}