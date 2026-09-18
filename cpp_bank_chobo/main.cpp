// main.cpp
// ------------------------------------------------------------
// 아주 쉬운 버전의 은행 계좌 프로그램입니다.
//
// cpp_bank 폴더에 있던 원래 버전과 다른 점:
//   1) .h(헤더) 파일이 없습니다. 모든 코드가 이 파일 하나에 들어있습니다.
//   2) class 대신 struct를 사용합니다.
//      - struct는 "여러 데이터를 하나로 묶는 상자"라고 생각하면 됩니다.
//      - class와 거의 똑같지만, 안에 있는 내용을 기본적으로 다 공개(public)합니다.
//        (그래서 private, public을 따로 신경 쓸 필요가 없어요.)
//   3) private, friend 같은 "접근 제한" 개념을 쓰지 않습니다.
//      - 대신 함수들이 Account를 매개변수로 받아서 직접 값을 읽고 바꿉니다.
//
// 기능은 원래 버전과 동일합니다: 입금 / 출금 / 잔액 조회 / 이체 / 종료
// ------------------------------------------------------------

#include <algorithm> // std::reverse : 문자열을 거꾸로 뒤집을 때 사용
#include <iostream>  // std::cout, std::cin : 화면 출력, 키보드 입력
#include <string>    // std::string : 문자열 타입
#include <windows.h> // SetConsoleOutputCP : 콘솔에서 한글이 깨지지 않게 해줌

// --------------------------------------------------
// 1. 계좌를 표현하는 상자(struct)
// --------------------------------------------------
// struct 안에 있는 변수들을 "멤버 변수"라고 부릅니다.
// class와 다르게 struct는 별다른 표시가 없으면 전부 public(외부 공개) 입니다.
struct Account {
    std::string owner;  // 예금주 이름
    long long balance;  // 현재 잔액 (금액이 클 수 있어서 long long 사용)
};
// 참고: long long은 아주 큰 정수(약 -900경 ~ +900경)를 담을 수 있는 타입입니다.
// 보통 쓰는 int는 약 -21억 ~ +21억까지만 담을 수 있어서, 돈처럼 커질 수 있는
// 값에는 long long을 사용하는 것이 안전합니다.

// --------------------------------------------------
// 2. 숫자를 "1,234,567" 처럼 천 단위 콤마 문자열로 바꾸는 함수
// --------------------------------------------------
std::string formatWithComma(long long value) {
    // 1) 숫자를 문자열로 변환합니다. 예) 1234567 -> "1234567"
    std::string digits = std::to_string(value);
    std::string result;
    int count = 0; // 오른쪽부터 몇 자리를 처리했는지 세는 변수

    // 2) 문자열의 맨 뒤(1의 자리)부터 거꾸로 한 글자씩 확인합니다.
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        result.push_back(digits[i]); // 현재 글자를 result 뒤에 붙임
        ++count;

        // 3자리마다(그리고 맨 앞자리가 아니라면) 콤마를 추가합니다.
        if (count % 3 == 0 && i != 0) {
            result.push_back(',');
        }
    }

    // 3) 지금까지 만든 result는 뒤집힌 상태이므로 다시 뒤집어서 원래 순서로 만듭니다.
    // 예) "765,432,1" -> 뒤집으면 -> "1,234,567"
    std::reverse(result.begin(), result.end());
    return result;
}

// --------------------------------------------------
// 3. 입금 함수
// --------------------------------------------------
// Account& acc : acc라는 이름으로 "진짜 계좌"를 그대로 가리켜서 쓰겠다는 뜻입니다.
// (& 를 안 붙이면 계좌를 복사해서 쓰기 때문에, 원본 잔액이 바뀌지 않습니다.)
void deposit(Account& acc, long long amount) {
    if (amount <= 0) {
        std::cout << "입금액은 0원보다 커야 합니다." << std::endl;
        return;
    }

    acc.balance += amount; // 잔액에 입금액을 더함

    std::cout << formatWithComma(amount) << "원 입금 완료 (현재 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
}

// --------------------------------------------------
// 4. 출금 함수 (성공하면 true, 실패하면 false 반환)
// --------------------------------------------------
bool withdraw(Account& acc, long long amount) {
    if (amount <= 0) {
        std::cout << "출금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    if (amount > acc.balance) {
        std::cout << "잔액이 부족합니다." << std::endl;
        return false;
    }

    acc.balance -= amount; // 잔액에서 출금액을 뺌

    std::cout << formatWithComma(amount) << "원 출금 완료 (현재 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
    return true;
}

// --------------------------------------------------
// 5. 이체 함수 (from 계좌 -> to 계좌로 돈을 옮김)
// --------------------------------------------------
// 원래 버전에서는 이 기능을 위해 friend 함수라는 특별한 문법이 필요했지만,
// struct는 멤버가 전부 공개(public)라서 그냥 평범한 함수로 만들 수 있습니다.
bool transfer(Account& from, Account& to, long long amount) {
    if (amount <= 0) {
        std::cout << "이체 금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    if (amount > from.balance) {
        std::cout << "잔액이 부족하여 이체할 수 없습니다." << std::endl;
        return false;
    }

    from.balance -= amount; // 보내는 계좌에서 차감
    to.balance += amount;   // 받는 계좌에 추가

    std::cout << "[" << from.owner << "] -> [" << to.owner << "] "
              << formatWithComma(amount) << "원 이체 완료" << std::endl;
    return true;
}

// --------------------------------------------------
// 6. 프로그램 시작점 (main 함수)
// --------------------------------------------------
int main() {
    // 소스 코드는 UTF-8로 저장되어 있는데, Windows 콘솔(cmd)창은 기본적으로
    // 다른 코드페이지(한국어 Windows는 949)를 사용해서 한글이 깨져 보입니다.
    // 콘솔의 출력 방식을 UTF-8로 맞춰줘서 한글이 정상적으로 보이게 합니다.
    SetConsoleOutputCP(CP_UTF8);

    // "홍길동"이라는 이름과 초기 잔액 10000원으로 계좌를 하나 만듭니다.
    // { } 안의 값들이 순서대로 owner, balance에 들어갑니다.
    Account acc{ "홍길동", 10000 };

    // 이체를 테스트해보기 위한 상대방 계좌를 하나 더 만듭니다.
    Account acc2{ "김철수", 5000 };

    std::cout << "[" << acc.owner << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc.balance) << "원)" << std::endl;
    std::cout << "[" << acc2.owner << "]님의 계좌가 생성되었습니다. (초기 잔액: "
              << formatWithComma(acc2.balance) << "원)" << std::endl;

    bool running = true; // 프로그램을 계속 실행할지 여부
    std::string line;    // 사용자 입력을 저장할 변수

    // running이 true인 동안 메뉴를 계속 보여줍니다.
    while (running) {
        std::cout << "\n=== 은행 메뉴 ===" << std::endl;
        std::cout << "1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 이체 | 5. 종료" << std::endl;
        std::cout << "선택 >> ";
        std::getline(std::cin, line); // 사용자가 입력한 한 줄을 line에 저장

        if (line == "1") {
            // ----- 입금 처리 -----
            std::cout << "입금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line); // 문자열 -> 숫자 변환
                deposit(acc, amount);
            } catch (const std::exception&) {
                // 숫자가 아닌 값을 입력하면 std::stoll에서 오류가 발생하는데,
                // 그 오류를 여기서 잡아서 프로그램이 죽지 않고 안내 메시지를 띄웁니다.
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "2") {
            // ----- 출금 처리 -----
            std::cout << "출금할 금액: ";
            std::getline(std::cin, line);
            try {
                long long amount = std::stoll(line);
                withdraw(acc, amount);
            } catch (const std::exception&) {
                std::cout << "올바른 숫자를 입력하세요." << std::endl;
            }
        } else if (line == "3") {
            // ----- 잔액 조회 -----
            std::cout << "[" << acc.owner << "]님의 현재 잔액: "
                      << formatWithComma(acc.balance) << "원" << std::endl;
            std::cout << "[" << acc2.owner << "]님의 현재 잔액: "
                      << formatWithComma(acc2.balance) << "원" << std::endl;
        } else if (line == "4") {
            // ----- 이체 처리 -----
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
            // ----- 종료 처리 -----
            std::cout << "프로그램을 종료합니다." << std::endl;
            running = false;
        } else {
            std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
