#include "VipAcc.h"
#include <iostream>
using namespace std;
VipAcc::VipAcc(int id, const string& username, const string& password, double balance, const string& nickname)
    : Account(id, username, password, balance), nickname(nickname) {}

const string& VipAcc::getNickname() const {
    return nickname;
}

void VipAcc::setNickname(const string& nickname) {
    this->nickname = nickname;
}

void VipAcc::displayAccountInfo() const {
    cout << "=============================\n";
    cout << "\x1B[95mInfo\nVip Account\nID: " << id << "\nUsername: " << username << "\nNickname: " << nickname << "\nBalance: " << balance << "\033[0m\n";
}

double VipAcc::taxEarn(double win) const {
    return win;
}