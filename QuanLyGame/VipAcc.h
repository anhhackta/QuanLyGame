#pragma once
#ifndef VIPACC_H
#define VIPACC_H

#include "Account.h"
#include <string>

class VipAcc : public Account {
public:
    VipAcc(int id, const string& username, const string& password, double balance, const string& nickname);

    const string& getNickname() const;
    void setNickname(const string& nickname);
    void displayAccountInfo() const override;

private:
    string nickname;
};

#endif // VIPACC_H
