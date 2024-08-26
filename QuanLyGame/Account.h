#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account {
public:
    Account(int id, const string& username, const string& password, double balance);

    virtual ~Account() = default;

    int getId() const;
    const string& getUsername() const;
    const string& getPassword() const;
    double getBalance() const;

    void setPassword(const string& password);
    void setBalance(double balance);
    virtual double taxEarn(double win) const = 0;
    virtual void displayAccountInfo() const;

protected:
    int id;
    string username;
    string password;
    double balance;
};

#endif // ACCOUNT_H