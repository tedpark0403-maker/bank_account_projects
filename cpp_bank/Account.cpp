// Account.cpp
// Account.h 에서 선언만 해두었던 함수들의 실제 내용(구현)을 작성하는 파일입니다.

#include "Account.h"
#include <algorithm> // std::reverse (문자열 뒤집기)를 사용하기 위해 필요
#include <iostream>  // std::cout (화면 출력)을 사용하기 위해 필요
#include <string>

// 숫자를 천 단위 콤마 문자열로 바꿔주는 함수
// 예) formatWithComma(1234567) -> "1,234,567"
std::string formatWithComma(long long value) {
    // 1. 숫자를 문자열로 변환 (예: 1234567 -> "1234567")
    std::string digits = std::to_string(value);
    std::string result;
    int count = 0; // 오른쪽부터 몇 자리를 처리했는지 세는 변수

    // 2. 문자열의 맨 뒤(오른쪽, 1의 자리)부터 거꾸로 한 글자씩 확인합니다.
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
    /*
    // ❌ 위험한 코드 (무한 루프 발생)
        for (size_t i = digits.size() - 1; i >= 0; --i) { ... }
        i가 0일 때 --i를 실행하면 -1이 되는 대신, 언더플로우(Underflow)가 발생해 해당 타입의 가장 큰 양수(약 1844경) 값으로 되돌아가며 무한 루프에 빠집니다.
    */
        result.push_back(digits[i]); // 현재 글자를 result 뒤에 붙임
        ++count;
        // 3자리마다(그리고 맨 앞자리가 아니면) 콤마를 추가합니다.
        if (count % 3 == 0 && i != 0) {
            result.push_back(',');
        }
    }

    // 3. 지금까지 만든 result는 뒤집힌 상태이므로 다시 뒤집어서 원래 순서로 만듭니다.
    // 예) "765,432,1" -> 뒤집으면 -> "1,234,567"
    std::reverse(result.begin(), result.end());
    return result;
}

// 생성자: Account 객체가 처음 만들어질 때 실행되는 함수
// owner(예금주 이름)와 initialBalance(초기 잔액)를 받아서 멤버 변수를 초기화합니다.
Account::Account(const std::string& owner, long long initialBalance)
    : owner(owner), balance(initialBalance) {
    // : owner(owner), balance(initialBalance) 부분을 "초기화 리스트"라고 부르며,
    // 함수 몸통({}) 실행 전에 멤버 변수 owner, balance에 값을 바로 넣어줍니다.
}

// 예금주 이름을 반환하는 함수
const std::string& Account::getOwner() const {
    return owner;
}

// 현재 잔액을 반환하는 함수
long long Account::getBalance() const {
    return balance;
}

// 입금 함수: 잔액을 늘려줍니다.
void Account::deposit(long long amount) {
    // 입금액이 0 이하면 잘못된 요청이므로 바로 종료(return)합니다.
    if (amount <= 0) {
        std::cout << "입금액은 0원보다 커야 합니다." << std::endl;
        return;
    }

    balance += amount; // 잔액에 입금액을 더함

    // 입금 완료 메시지를 콤마 형식으로 예쁘게 출력
    std::cout << formatWithComma(amount) << "원 입금 완료 (현재 잔액: "
              << formatWithComma(balance) << "원)" << std::endl;
}

// 출금 함수: 잔액을 줄여줍니다. 성공하면 true, 실패하면 false를 반환합니다.
bool Account::withdraw(long long amount) {
    // 출금액이 0 이하면 잘못된 요청
    if (amount <= 0) {
        std::cout << "출금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    // 출금하려는 금액이 잔액보다 많으면 출금할 수 없음
    if (amount > balance) {
        std::cout << "잔액이 부족합니다." << std::endl;
        return false;
    }

    balance -= amount; // 잔액에서 출금액을 뺌

    // 출금 완료 메시지를 콤마 형식으로 예쁘게 출력
    std::cout << formatWithComma(amount) << "원 출금 완료 (현재 잔액: "
              << formatWithComma(balance) << "원)" << std::endl;
    return true;
}

// friend 함수 구현
// 주의: 이 함수는 Account:: 를 붙이지 않습니다. Account의 멤버 함수가 아니라
// 그냥 일반 함수인데, Account.h에서 friend로 지정해줬기 때문에
// from.balance, to.balance 같은 private 멤버에 예외적으로 접근할 수 있는 것입니다.
bool transfer(Account& from, Account& to, long long amount) {
    // 이체 금액이 0 이하면 잘못된 요청
    if (amount <= 0) {
        std::cout << "이체 금액은 0원보다 커야 합니다." << std::endl;
        return false;
    }

    // 보내는 계좌(from)의 잔액이 이체 금액보다 적으면 이체할 수 없음
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
