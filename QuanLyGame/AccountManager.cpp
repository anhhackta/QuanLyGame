#include "AccountManager.h"
#include "DefaultAcc.h"
#include "VipAcc.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

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
    accounts.erase(it, accounts.end());
}

void AccountManager::adminMenu() {
    int choice;
    do {
        cout << "Admin Menu:\n";
        cout << "1. Thêm tài khoản\n";
        cout << "2. Xóa tài khoản\n";
        cout << "3. Tìm kiếm tài khoản\n";
        cout << "4. Thoát\n";
        cout << "Nhập lựa chọn: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string username, password;
            double balance;
            cout << "Nhập ID: ";
            cin >> id;
            cout << "Nhập Username: ";
            cin >> username;
            cout << "Nhập Password: ";
            cin >> password;
            cout << "Nhập Balance: ";
            cin >> balance;
            addAccount(new DefaultAcc(id, username, password, balance));
            saveData("Data.txt");
        }
        else if (choice == 2) {
            string username;
            cout << "Nhập Username cần xóa: ";
            cin >> username;
            deleteAccount(username);
            saveData("Data.txt");
        }
        else if (choice == 3) {
            string username;
            cout << "Nhập Username cần tìm: ";
            cin >> username;
            Account* account = findAccount(username);
            if (account) {
                account->displayAccountInfo();
            }
            else {
                cout << "Không tìm thấy tài khoản\n";
            }
        }
    } while (choice != 4);
}

void AccountManager::userMenu(Account* user) {
    int choice;
    do {
        cout << "User Menu:\n";
        cout << "1. Nạp tiền\n";
        cout << "2. Rút tiền\n";
        cout << "3. Chuyển tiền\n";
        cout << "4. Sửa thông tin\n";
        cout << "5. Bảng xếp hạng\n";
        cout << "6. Thoát\n";
        cout << "Nhập lựa chọn: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            cout << "Nhập số tiền cần nạp: ";
            cin >> amount;
            user->setBalance(user->getBalance() + amount);

            // Kiểm tra và nâng cấp lên VipAcc nếu đủ số tiền quy định
            if (user->getBalance() >= 1000 && dynamic_cast<DefaultAcc*>(user)) {
                string nickname;
                cout << "Bạn đã được nâng cấp lên VipAcc. Nhập Nickname: ";
                cin >> nickname;
                auto* vip = new VipAcc(user->getId(), user->getUsername(), user->getPassword(), user->getBalance(), nickname);
                delete user;
                user = vip;
                accounts.push_back(vip);
            }

            saveData("Data.txt");
        }
        else if (choice == 2) {
            double amount;
            cout << "Nhập số tiền cần rút: ";
            cin >> amount;
            if (user->getBalance() >= amount) {
                user->setBalance(user->getBalance() - amount);
                saveData("Data.txt");
            }
            else {
                cout << "Số dư không đủ\n";
            }
        }
        else if (choice == 3) {
            string username;
            double amount;
            cout << "Nhập Username cần chuyển tiền: ";
            cin >> username;
            Account* recipient = findAccount(username);
            if (recipient) {
                cout << "Nhập số tiền cần chuyển: ";
                cin >> amount;
                if (user->getBalance() >= amount) {
                    user->setBalance(user->getBalance() - amount);
                    recipient->setBalance(recipient->getBalance() + amount);
                    saveData("Data.txt");
                }
                else {
                    cout << "Số dư không đủ\n";
                }
            }
            else {
                cout << "Không tìm thấy tài khoản cần chuyển\n";
            }
        }
        else if (choice == 4) {
            string newPassword;
            cout << "Nhập mật khẩu mới: ";
            cin >> newPassword;
            user->setPassword(newPassword);
            saveData("Data.txt");
        }
        else if (choice == 5) {
            displayRanking();
        }
    } while (choice != 6);
}

void AccountManager::displayRanking() {
    sort(accounts.begin(), accounts.end(), [](Account* a, Account* b) {
        return a->getBalance() > b->getBalance();
        });
    cout << "Bảng xếp hạng:\n";
    for (const auto& account : accounts) {
        account->displayAccountInfo();
    }
}