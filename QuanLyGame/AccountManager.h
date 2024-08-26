#pragma once
#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <vector>
#include <string>
#include "Account.h"

class AccountManager {
public:
    void loadData(const string& filename);
    void saveData(const string& filename);
    Account* findAccount(const string& username);
    void addAccount(Account* account);
    void deleteAccount(const string& username);
    void adminMenu();
    void userMenu(Account* user);
    void displayRanking();

private:
    vector<Account*> accounts;
};

#endif // ACCOUNTMANAGER_H

