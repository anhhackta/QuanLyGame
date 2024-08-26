#include "DefaultAcc.h"
using namespace std;
DefaultAcc::DefaultAcc(int id, const string& username, const string& password, double balance)
    : Account(id, username, password, balance) {}

double DefaultAcc::taxEarn(double win) const {
    return win * 0.8;
}