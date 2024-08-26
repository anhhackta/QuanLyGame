#ifndef DEFAULTACC_H
#define DEFAULTACC_H

#include "Account.h"
using namespace std;
class DefaultAcc : public Account {
public:
    DefaultAcc(int id, const string& username, const string& password, double balance);

    double taxEarn(double win) const override;
};

#endif // DEFAULTACC_H