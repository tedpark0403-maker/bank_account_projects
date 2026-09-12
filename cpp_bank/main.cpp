// main.cpp
// 프로그램이 시작될 때 가장 먼저 실행되는 파일입니다.
// 사용자에게 메뉴를 보여주고, 입력을 받아 입금/출금/조회/종료를 처리합니다.

#include "Account.h"
#include <iostream>
#include <string>
#include <windows.h> //// 콘솔 출력을 UTF-8(한글 정상 출력)로 설정하는 함수 호출

int main() {
    // 소스 코드는 UTF-8로 저장되어 있는데, Windows 콘솔(cmd)창은 기본적으로
    // 다른 코드페이지(한국어 Windows는 949)를 사용해서 한글이 깨져 보입니다.
    // 콘솔의 출력 방식을 UTF-8로 맞춰줘서 한글이 정상적으로 보이게 합니다.
    SetConsoleOutputCP(CP_UTF8);

    // "홍길동"이라는 이름과 초기 잔액 10000원으로 계좌 객체를 하나 생성합니다.
    Account acc("홍길동", 10000);

    // friend 함수(transfer)로 이체를 테스트해보기 위한 상대방 계좌를 하나 더 만듭니다.
    Account acc2("김철수", 5000);

    // 계좌 생성 안내 메시지 출력
    std::cout << "[" << acc.getOwner() << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc.getBalance()) << "원)" << std::endl;
    std::cout << "[" << acc2.getOwner() << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc2.getBalance()) << "원)" << std::endl;

    bool running = true; // 프로그램을 계속 실행할지 여부를 나타내는 변수
    std::string line;    // 사용자 입력을 저장할 변수

    // running이 true인 동안 계속 반복 (메뉴가 계속 뜨는 부분)
    while (running) {
        // 메뉴 화면 출력
        std::cout << "\n=== 은행 메뉴 ===" << std::endl;
        std::cout << "1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 이체(friend 함수) | 5. 종료" << std::endl;
        std::cout << "선택 >> ";
        //std::getline(입력스트림, 저장할문자열변수, [구분자]);
        std::getline(std::cin, line); // 사용자가 입력한 한 줄을 line에 저장

        if (line == "1") {
            // ----- 입금 처리 -----
            std::cout << "입금할 금액: ";
            std::getline(std::cin, line);
            try {
                // 입력받은 문자열(line)을 숫자(long long)로 변환
                long long amount = std::stoll(line);
                acc.deposit(amount); // Account 클래스의 입금 함수 호출
            } catch (const std::exception&) {
                // 숫자가 아닌 값을 입력하면 std::stoll에서 예외(오류)가 발생하는데,
                // 그 오류를 여기서 잡아서 프로그램이 죽지 않고 안내 메시지를 띄웁니다.
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "2") {
            // ----- 출금 처리 -----
            std::cout << "출금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                acc.withdraw(amount); // Account 클래스의 출금 함수 호출
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "3") {
            // ----- 잔액 조회 -----
            std::cout << "[" << acc.getOwner() << "]님의 현재 잔액: "
                      << formatWithComma(acc.getBalance()) << "원" << std::endl;
            std::cout << "[" << acc2.getOwner() << "]님의 현재 잔액: "
                      << formatWithComma(acc2.getBalance()) << "원" << std::endl;
        } else if (line == "4") {
            // ----- 이체 처리 (friend 함수 transfer 사용) -----
            // transfer는 Account의 멤버 함수가 아니라 friend로 지정된 일반 함수입니다.
            // acc.balance, acc2.balance 같은 private 멤버를 직접 다루기 위해
            // Account.h/.cpp에서 friend로 선언해 두었습니다.
            std::cout << "이체할 금액 ([" << acc.getOwner() << "] -> ["
                      << acc2.getOwner() << "]): ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                transfer(acc, acc2, amount); // friend 함수 호출
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "5") {
            // ----- 종료 처리 -----
            std::cout << "프로그램을 종료합니다." << std::endl;
            running = false; // running을 false로 바꿔서 while문을 빠져나가게 함
        } else {
            // 1~5가 아닌 다른 값을 입력했을 때
            std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
        }
    }

    return 0; // 프로그램 정상 종료를 의미
}
