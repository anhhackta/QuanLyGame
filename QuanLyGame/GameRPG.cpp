#include "GameRPG.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
Character::Character(string n, int h, int ap)
    : name(n), health(h), attackPower(ap), isDefending(false) {}

void Character::attack(Character& target) {
    cout << name << " tan cong " << target.getName() << " gay " << attackPower << " sat thuong!" << endl;
    target.takeDamage(attackPower);
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    cout << name << " nhan " << damage << " sat thuong! Mau con lai: " << health << endl;
}

void Character::defend() {
    isDefending = true;
    int defenseBoost = 0;
    if (name == "Dau si") defenseBoost = 20;
    else if (name == "Phap su") defenseBoost = 10;
    else if (name == "Cung thu") defenseBoost = 15;
    health += defenseBoost;
    cout << name << " phong thu duoc hoi " << defenseBoost << " mau! mau hien tai: " << health << endl;
    cout << name << " dang phong thu luot nay !" << endl;
}

void Character::resetDefend() {
    isDefending = false;
}

bool Character::getIsDefending() {
    return isDefending;
}

string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttackPower() {
    return attackPower;
}

void Character::increaseAttackPower(int amount) {
    attackPower += amount;
}

bool Character::isAlive() {
    return health > 0;
}

Warrior::Warrior(string n, int h, int ap) : Character(n, h, ap) {}
Mage::Mage(string n, int h, int ap) : Character(n, h, ap) {}
Archer::Archer(string n, int h, int ap) : Character(n, h, ap) {}

Character* createRandomCharacter(const string& type) {
    if (type == "Dau si") {
        int health = rand() % 101 + 100;
        int attack = rand() % 21 + 10; 
        return new Warrior("Dau si", health, attack);
    }
    else if (type == "Phap su") {
        int health = rand() % 101 + 50;  
        int attack = rand() % 26 + 20;   
        return new Mage("Phap su", health, attack);
    }
    else if (type == "Cung thu") {
        int health = rand() % 101 + 70;
        int attack = rand() % 21 + 15; 
        return new Archer("Cung thu", health, attack);
    }
    return nullptr;
}
void displayStatus(const vector<Character*>& characters) {
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ": " << characters[i]->getName() << " - Mau: " << characters[i]->getHealth() << " - ST : " << characters[i]->getAttackPower() << (characters[i]->isAlive() ? " (Live)" : " (Death)") << endl;
    }
}

void battle(Character& player, Character& bot) {
    cout << player.getName() << " dau voi " << bot.getName() << endl;

    int playerChoice;
    cout << "Chon hanh dong cua ban: 1. Tan cong, 2. Phong thu: ";
    cout << "\n====================================================" << endl;
    cin >> playerChoice;

    int botChoice = rand() % 2 + 1;

    if (playerChoice == 1 && botChoice == 1) {
        cout << "Ca hai deu chon tan cong!" << endl;
        player.attack(bot);
        bot.attack(player);
    }
    else if (playerChoice == 1 && botChoice == 2) {
        cout << "Ban tan cong va bot phong thu!" << endl;
        bot.defend();
        player.attack(bot);
    }
    else if (playerChoice == 2 && botChoice == 1) {
        cout << "Bot tan cong va ban phong thu!" << endl;
        player.defend();
        bot.attack(player);
    }
    else {
        cout << "Ca hai deu chon phong thu!" << endl;
        player.defend();
        bot.defend();
    }

    player.resetDefend();
    bot.resetDefend();
}

void gamerpg(Account* user) {
    srand(static_cast<unsigned>(time(0))); 
    cout << " Game RPG by Hoang " << endl;
    cout << " Demo - Viet Hoa, y tuong cho bai cocos " << endl;
    double bet;
    cout << "Enter the bet amount: ";
    cin >> bet;

    if (bet > user->getBalance()) {
        cout << "Insufficient balance to place bets.\n";
        return;
    }
    vector<Character*> playerTeam;
    for (int i = 0; i < 3; i++) {
        cout << "Chon loai nhan vat" <<" [ "<< i + 1 << " ]" << " cua ban (1: Dau si, 2: Phap su, 3: Cung thu): ";
        int choice;
        cin >> choice;

        Character* character = nullptr;
        if (choice == 1) character = createRandomCharacter("Dau si");
        else if (choice == 2) character = createRandomCharacter("Phap su");
        else if (choice == 3) character = createRandomCharacter("Cung thu");

        if (character != nullptr) {
            playerTeam.push_back(character);
        }
        else {
            cout << "Lua chon khong hop le!" << endl;
            i--;
        }
    }

    
    vector<Character*> botTeam;
    for (int i = 0; i < 3; i++) {
        int randomChoice = rand() % 3 + 1; // Random 1, 2, hoac 3
        if (randomChoice == 1) botTeam.push_back(createRandomCharacter("Dau si"));
        else if (randomChoice == 2) botTeam.push_back(createRandomCharacter("Phap su"));
        else if (randomChoice == 3) botTeam.push_back(createRandomCharacter("Cung thu"));
    }

    while (!playerTeam.empty() && !botTeam.empty()) {
        cout << "================================================" << endl;
        cout << "\nDoi hinh cua ban:" << endl;
        displayStatus(playerTeam);

        cout << "\nDoi hinh cua bot:" << endl;
        displayStatus(botTeam);

        int playerIndex;
        cout << "\n================================================" << endl;
        cout << "Chon nhan vat cua ban de giao chien (1, 2, 3): ";
        cin >> playerIndex;
        playerIndex = playerIndex - 1;
        if (playerIndex < 0 || playerIndex >= playerTeam.size() || !playerTeam[playerIndex]->isAlive()) {
            cout << "Lua chon khong hop le hoac nhan vat da chet! Vui long chon lai." << endl;
            continue;
        }

        int botIndex = rand() % botTeam.size();
        while (!botTeam[botIndex]->isAlive()) {
            botIndex = rand() % botTeam.size();
        }

        cout << "\nTran dau bat dau!" << endl;
        battle(*playerTeam[playerIndex], *botTeam[botIndex]);

        if (!playerTeam[playerIndex]->isAlive()) {
            cout << playerTeam[playerIndex]->getName() << " cua ban da bi danh bai!" << endl;
        }

        if (!botTeam[botIndex]->isAlive()) {
            cout << botTeam[botIndex]->getName() << " cua bot da bi danh bai!" << endl;
        }

        // Xoa nhan vat da chet khoi doi hinh
        playerTeam.erase(remove_if(playerTeam.begin(), playerTeam.end(), [](Character* c) { return !c->isAlive(); }), playerTeam.end());
        botTeam.erase(remove_if(botTeam.begin(), botTeam.end(), [](Character* c) { return !c->isAlive(); }), botTeam.end());
    }

    if (playerTeam.empty() && botTeam.empty()) {
        cout << "Tran dau ket thuc! Hoa!" << endl;
    }
    else if (playerTeam.empty()) {
        cout << "Bot chien thang!" << endl;
        user->setBalance(user->getBalance() - bet);
        cout << "Sorry! You lost.\n";
    }
    else {
        cout << "Ban chien thang!" << endl;
        double win = user->taxEarn(bet);
        user->setBalance(user->getBalance() + win);
        cout << "Congratulations! You won " << win << "!\n";
    }

    // Giai phong bo nho
    for (auto character : playerTeam) delete character;
    for (auto character : botTeam) delete character;
}
