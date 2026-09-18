#pragma once

#include <string>

std::string formatWithComma(long long value);

class Account {
public:
    Account(const std::string& owner, long long initialBalance);

    const std::string& getOwner() const;

    long long getBalance() const;

    void deposit(long long amount);

    bool withdraw(long long amount);

    friend bool transfer(Account& from, Account& to, long long amount);

private:
    std::string owner;
    long long balance;
};

bool transfer(Account& from, Account& to, long long amount);
