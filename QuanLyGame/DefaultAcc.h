#pragma once
#ifndef DEFAULTACC_H
#define DEFAULTACC_H

#include "Account.h"

class DefaultAcc : public Account {
public:
    DefaultAcc(int id, const string& username, const string& password, double balance);
};

#endif
