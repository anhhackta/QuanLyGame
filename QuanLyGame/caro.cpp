#include "caro.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char nguoi = 'O', may = 'X';

void khoitao(char bang[vitri][vitri]) {
    for (int i = 0; i < vitri; i++) {
        for (int j = 0; j < vitri; j++) {
            bang[i][j] = ' ';
        }
    }
}

void hienthi(char bang[vitri][vitri]) {
    cout << "\n";
    for (int i = 0; i < vitri; i++) {
        for (int j = 0; j < vitri; j++) {
            cout << " " << bang[i][j];
            if (j < vitri - 1) cout << " |";
        }
        cout << "\n";
        if (i < vitri - 1) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool isMovesLeft(char bang[vitri][vitri]) {
    for (int i = 0; i < vitri; i++)
        for (int j = 0; j < vitri; j++)
            if (bang[i][j] == ' ')
                return true;
    return false;
}

int giatri(char bang[vitri][vitri]) {
    for (int row = 0; row < vitri; row++) {
        if (bang[row][0] == bang[row][1] && bang[row][1] == bang[row][2]) {
            if (bang[row][0] == nguoi)
                return -10;
            else if (bang[row][0] == may)
                return 10;
        }
    }
    for (int col = 0; col < vitri; col++) {
        if (bang[0][col] == bang[1][col] && bang[1][col] == bang[2][col]) {
            if (bang[0][col] == nguoi)
                return -10;
            else if (bang[0][col] == may)
                return 10;
        }
    }
    if (bang[0][0] == bang[1][1] && bang[1][1] == bang[2][2]) {
        if (bang[0][0] == nguoi)
            return -10;
        else if (bang[0][0] == may)
            return 10;
    }
    if (bang[0][2] == bang[1][1] && bang[1][1] == bang[2][0]) {
        if (bang[0][2] == nguoi)
            return -10;
        else if (bang[0][2] == may)
            return 10;
    }
    return 0;
}

int minimax(char bang[vitri][vitri], int dosau, bool luot) {
    int diem = giatri(bang);
    if (diem == 10)
        return diem;
    if (diem == -10)
        return diem;
    if (!isMovesLeft(bang))
        return 0;

    if (luot) {
        int best = -1000;
        for (int i = 0; i < vitri; i++) {
            for (int j = 0; j < vitri; j++) {
                if (bang[i][j] == ' ') {
                    bang[i][j] = may;
                    best = max(best, minimax(bang, dosau + 1, !luot));
                    bang[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < vitri; i++) {
            for (int j = 0; j < vitri; j++) {
                if (bang[i][j] == ' ') {
                    bang[i][j] = nguoi;
                    best = min(best, minimax(bang, dosau + 1, !luot));
                    bang[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

Move timbuocdi(char bang[vitri][vitri]) {
    int giatritot = -1000;
    Move bestdichuyen;
    bestdichuyen.row = -1;
    bestdichuyen.col = -1;
    for (int i = 0; i < vitri; i++) {
        for (int j = 0; j < vitri; j++) {
            if (bang[i][j] == ' ') {
                bang[i][j] = may;
                int gtdichuyen = minimax(bang, 0, false);
                bang[i][j] = ' ';
                if (gtdichuyen > giatritot) {
                    bestdichuyen.row = i;
                    bestdichuyen.col = j;
                    giatritot = gtdichuyen;
                }
            }
        }
    }
    return bestdichuyen;
}

void gamecaro(Account* user) {
    char bang[vitri][vitri];
    khoitao(bang);
    double bet;
    cout << "Enter the bet amount: ";
    cin >> bet;

    if (bet > user->getBalance()) {
        cout << "Insufficient balance to place bets.\n";
        return;
    }
    int luotChoi;
    cout << "Chon nguoi di truoc (1 - Nguoi choi, 2 - May): ";
    cin >> luotChoi;
    cout << "\n";

    hienthi(bang);

    for (int i = 0; i < vitri * vitri && isMovesLeft(bang); i++) {
        if (luotChoi == 1) {
            int chon;
            cout << "Nhap so tu 1 den 9 de chon o di: ";
            cin >> chon;

            int x = (chon - 1) / vitri;
            int y = (chon - 1) % vitri;

            if (bang[x][y] != ' ') {
                cout << "O da duoc chon. Chon lai!\n";
                i--;
                continue;
            }

            bang[x][y] = nguoi;
            luotChoi = 2; 
        }
        else {
            Move dichuyen = timbuocdi(bang);
            bang[dichuyen.row][dichuyen.col] = may;
            cout << "May di vao o " << dichuyen.row * vitri + dichuyen.col + 1 << "\n";
            luotChoi = 1;
        }

        hienthi(bang);
        
        int diem = giatri(bang);
        if (diem == 10) {
            cout << "May thang!\n";
            user->setBalance(user->getBalance() - bet);
            cout << "Sorry! You lost.\n";
            return;
        }
        else if (diem == -10) {
            cout << "Nguoi choi thang!\n";
            double win = user->taxEarn(bet);
            user->setBalance(user->getBalance() + win);
            cout << "Congratulations! You won " << win << "!\n";
            return;
        }
    }

    cout << "Hoa!\n";
}
