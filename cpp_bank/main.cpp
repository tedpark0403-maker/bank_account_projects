#include "Account.h"
#include <iostream>
#include <string>

int main() {
    Account acc("홍길동", 10000);
    std::cout << "[" << acc.getOwner() << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc.getBalance()) << "원)" << std::endl;

    bool running = true;
    std::string line;

    while (running) {
        std::cout << "\n=== 은행 메뉴 ===" << std::endl;
        std::cout << "1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 종료" << std::endl;
        std::cout << "선택 >> ";
        std::getline(std::cin, line);

        if (line == "1") {
            std::cout << "입금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                acc.deposit(amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "2") {
            std::cout << "출금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                acc.withdraw(amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "3") {
            std::cout << "[" << acc.getOwner() << "]님의 현재 잔액: "
                      << formatWithComma(acc.getBalance()) << "원" << std::endl;
        } else if (line == "4") {
            std::cout << "프로그램을 종료합니다." << std::endl;
            running = false;
        } else {
            std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
        }
    }

    return 0;
}
