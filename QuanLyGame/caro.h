#pragma once
#include "Account.h"
#include "VipAcc.h"
#include "DefaultAcc.h"
#ifndef CARO_H
#define CARO_H

#define vitri 3

struct Move {
    int row, col;
};

void khoitao(char bang[vitri][vitri]);
void hienthi(char bang[vitri][vitri]);
bool isMovesLeft(char bang[vitri][vitri]);
int giatri(char bang[vitri][vitri]);
int minimax(char bang[vitri][vitri], int dosau, bool luot);
Move timbuocdi(char bang[vitri][vitri]);
void gamecaro(Account* user);

#endif // CARO
