#pragma once

#include <string>

// 숫자를 천 단위 콤마가 포함된 문자열로 변환
std::string formatWithComma(long long value);

class Account {
public:
    Account(const std::string& owner, long long initialBalance);

    const std::string& getOwner() const;
    long long getBalance() const;

    void deposit(long long amount);
    bool withdraw(long long amount);

private:
    std::string owner;
    long long balance;
};
