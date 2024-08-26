#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <vector>
#include <string>
#include "Account.h"
#include "bigsmallgame.h"
#include "caro.h"
#include "GameRPG.h"
using namespace std;
class AccountManager {
public:
    ~AccountManager();

    void loadData(const string& filename);
    void saveData(const string& filename);
    Account* findAccount(const string& username);
    void addAccount(Account* account);
    void deleteAccount(const string& username);
    void adminMenu();
    void userMenu(Account*& user);
    void displayRanking();

private:
    bigsmallgame game;
    vector<Account*> accounts;
};

#endif // ACCOUNTMANAGER_H