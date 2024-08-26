#ifndef GAMERPG_H
#define GAMERPG_H
#include "Account.h"
#include "VipAcc.h"
#include "DefaultAcc.h"
#include <string>
#include <vector>
using namespace std;
class Character {
protected:
    string name;
    int health;
    int attackPower;
    bool isDefending;

public:
    Character(string n, int h, int ap);
    virtual void attack(Character& target);
    void takeDamage(int damage);
    void defend();
    void resetDefend();
    bool getIsDefending();
    string getName();
    int getHealth();
    int getAttackPower();
    void increaseAttackPower(int amount);
    bool isAlive();
    virtual ~Character() {}
};

class Warrior : public Character {
public:
    Warrior(string n, int h, int ap);
};

class Mage : public Character {
public:
    Mage(string n, int h, int ap);
};

class Archer : public Character {
public:
    Archer(string n, int h, int ap);
};

Character* createRandomCharacter(const string& type);
void displayStatus(const vector<Character*>& characters);
void battle(Character& player, Character& bot);
void gamerpg(Account* user);

#endif // GAMERPG_H
