#include "Account_no_comments.h"
#include <algorithm>
#include <iostream>
#include <string>

std::string formatWithComma(long long value) {
    std::string digits = std::to_string(value);
    std::string result;
    int count = 0;

    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        result.push_back(digits[i]);
        ++count;
        if (count % 3 == 0 && i != 0) {
            result.push_back(',');
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

Account::Account(const std::string& owner, long long initialBalance)
    : owner(owner), balance(initialBalance) {
}

const std::string& Account::getOwner() const {
    return owner;
}

long long Account::getBalance() const {
    return balance;
}

void Account::deposit(long long amount) {
    if (amount <= 0) {
        std::cout << "입금액은 0원보다 커야 합니다." << std::endl;
        return;
    }

    balance += amount;

    std::cout << formatWithComma(amount) << "원 입금 완료 (현재 잔액: "
              << formatWithComma(balance) << "원)" << std::endl;
}

bool Account::withdraw(long long amount) {
    if (amount <= 0) {
        std::cout << "출금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    if (amount > balance) {
        std::cout << "잔액이 부족합니다." << std::endl;
        return false;
    }

    balance -= amount;

    std::cout << formatWithComma(amount) << "원 출금 완료 (현재 잔액: "
              << formatWithComma(balance) << "원)" << std::endl;
    return true;
}

bool transfer(Account& from, Account& to, long long amount) {
    if (amount <= 0) {
        std::cout << "이체 금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    if (amount > from.balance) {
        std::cout << "잔액이 부족하여 이체할 수 없습니다." << std::endl;
        return false;
    }

    from.balance -= amount;
    to.balance += amount;

    std::cout << "[" << from.owner << "] -> [" << to.owner << "] "
              << formatWithComma(amount) << "원 이체 완료" << std::endl;
    return true;
}
