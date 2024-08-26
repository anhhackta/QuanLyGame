#pragma once
#ifndef BIGSMALL_GAME_H
#define BIGSMALL_GAME_H

#include "Account.h"
#include "VipAcc.h"
#include "DefaultAcc.h"
#include <random>
using namespace std;
class bigsmallgame {
private:
    default_random_engine generator;
    uniform_int_distribution<int> distribution;

    int generateNumber();
public:
    bigsmallgame();
    void play(Account* user);

};

#endif // BIGSMALL_GAME_H