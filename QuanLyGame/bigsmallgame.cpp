#include "bigsmallgame.h"
#include <iostream>
using namespace std;

bigsmallgame::bigsmallgame() : distribution(1, 6) {
    random_device rd;
    generator.seed(rd());
}

int bigsmallgame::generateNumber() {
    return distribution(generator);
}

void bigsmallgame::play(Account* user) {
    double bet;
    cout << "Enter the bet amount: ";
    cin >> bet;

    if (bet > user->getBalance()) {
        cout << "Insufficient balance to place bets.\n";
        return;
    }

    int userChoice;
    cout << "========================\n";
    cout << "     EVEN - ODD game!   \n";
    cout << "========================\n";
    cout << "Dice to 1 - 6\n";
    cout << "Choose \n1.EVEN \n2.ODD\nchoice : ";
    cin >> userChoice;

    int generatedNumber = generateNumber();
    cout << "The randomly generated number is: " << generatedNumber << "\n";

    bool winf = false;
    if (userChoice == 1 && generatedNumber % 2 == 0) { 
        winf = true;
    }
    else if (userChoice == 2 && generatedNumber % 2 != 0) { 
        winf = true;
    }

    if (winf) {
        double win = user->taxEarn(bet);
        user->setBalance(user->getBalance() + win);
        cout << "Congratulations! You won " << win << "!\n";
    }
    else {
        user->setBalance(user->getBalance() - bet);
        cout << "Sorry! You lost.\n";
    }
}
