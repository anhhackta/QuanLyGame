#include "Account.h"
#include <iostream>

Account::Account(int id, const string& username, const string& password, double balance)
    : id(id), username(username), password(password), balance(balance) {}

int Account::getId() const {
    return id;
}

const string& Account::getUsername() const {
    return username;
}

const string& Account::getPassword() const {
    return password;
}

double Account::getBalance() const {
    return balance;
}

void Account::setPassword(const string& password) {
    this->password = password;
}

void Account::setBalance(double balance) {
    this->balance = balance;
}

void Account::displayAccountInfo() const {
    cout << "ID: " << id << ", Username: " << username << ", Balance: " << balance << "\n";
}