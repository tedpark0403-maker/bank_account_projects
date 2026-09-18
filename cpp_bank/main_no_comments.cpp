#include "Account_no_comments.h"
#include <iostream>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Account acc("홍길동", 10000);

    Account acc2("김철수", 5000);

    std::cout << "[" << acc.getOwner() << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc.getBalance()) << "원)" << std::endl;
    std::cout << "[" << acc2.getOwner() << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc2.getBalance()) << "원)" << std::endl;

    bool running = true;
    std::string line;

    while (running) {
        std::cout << "\n=== 은행 메뉴 ===" << std::endl;
        std::cout << "1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 이체(friend 함수) | 5. 종료" << std::endl;
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
            std::cout << "[" << acc2.getOwner() << "]님의 현재 잔액: "
                      << formatWithComma(acc2.getBalance()) << "원" << std::endl;
        } else if (line == "4") {
            std::cout << "이체할 금액 ([" << acc.getOwner() << "] -> ["
                      << acc2.getOwner() << "]): ";
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
