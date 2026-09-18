#include <algorithm>
#include <iostream>
#include <string>
#include <windows.h>

struct Account {
    std::string owner;
    long long balance;
};

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

void deposit(Account& acc, long long amount) {
    if (amount <= 0) {
        std::cout << "입금액은 0원보다 커야 합니다." << std::endl;
        return;
    }

    acc.balance += amount;

    std::cout << formatWithComma(amount) << "원 입금 완료 (현재 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
}

bool withdraw(Account& acc, long long amount) {
    if (amount <= 0) {
        std::cout << "출금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    if (amount > acc.balance) {
        std::cout << "잔액이 부족합니다." << std::endl;
        return false;
    }

    acc.balance -= amount;

    std::cout << formatWithComma(amount) << "원 출금 완료 (현재 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
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

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Account acc{ "홍길동", 10000 };

    Account acc2{ "김철수", 5000 };

    std::cout << "[" << acc.owner << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
    std::cout << "[" << acc2.owner << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc2.balance) << "원)" << std::endl;

    bool running = true;
    std::string line;

    while (running) {
        std::cout << "\n=== 은행 메뉴 ===" << std::endl;
        std::cout << "1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 이체 | 5. 종료" << std::endl;
        std::cout << "선택 >> ";
        std::getline(std::cin, line);

        if (line == "1") {
            std::cout << "입금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                deposit(acc, amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "2") {
            std::cout << "출금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                withdraw(acc, amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "3") {
            std::cout << "[" << acc.owner << "]님의 현재 잔액: "
                      << formatWithComma(acc.balance) << "원" << std::endl;
            std::cout << "[" << acc2.owner << "]님의 현재 잔액: "
                      << formatWithComma(acc2.balance) << "원" << std::endl;
        } else if (line == "4") {
            std::cout << "이체할 금액 ([" << acc.owner << "] -> ["
                      << acc2.owner << "]): ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                transfer(acc, acc2, amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "5") {
            std::cout << "프로그램을 종료합니다." << std::endl;
            running = false;
        } else {
            std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
        }
    }

    return 0;
}
