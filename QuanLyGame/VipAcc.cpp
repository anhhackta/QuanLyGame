#include "VipAcc.h"
#include <iostream>

VipAcc::VipAcc(int id, const string& username, const string& password, double balance, const string& nickname)
    : Account(id, username, password, balance), nickname(nickname) {}

const string& VipAcc::getNickname() const {
    return nickname;
}

void VipAcc::setNickname(const string& nickname) {
    this->nickname = nickname;
}

void VipAcc::displayAccountInfo() const {
    cout << "ID: " << id << ", Username: " << username << ", Nickname: " << nickname << ", Balance: " << balance << "\n";
}