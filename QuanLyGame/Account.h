#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account {

protected:
    int id;
    string username;
    string password;
    double balance;
public:
    Account(int id, const string& username, const string& password, double balance);

    virtual ~Account() {};

    int getId() const;
    const string& getUsername() const;
    const string& getPassword() const;
    double getBalance() const;

    void setPassword(const string& password);
    void setBalance(double balance);

    virtual void displayAccountInfo() const;

};

#endif // ACCOUNT_H