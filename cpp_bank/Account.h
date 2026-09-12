// Account.h
// 이 파일은 "설계도" 역할을 하는 헤더 파일입니다.
// 실제 동작 코드는 없고, "이런 함수와 클래스가 있다"는 것만 미리 선언해 둡니다.
// 실제 구현(코드 내용)은 Account.cpp 파일에 들어있습니다.

#pragma once
// #pragma once : 이 헤더 파일이 같은 곳에서 여러 번 include 되어도
// 딱 한 번만 처리되도록 막아주는 역할을 합니다. (중복 정의 오류 방지)

#include <string>
// 문자열(std::string)을 사용하기 위해 필요한 표준 라이브러리를 불러옵니다.

// 숫자를 천 단위 콤마가 포함된 문자열로 변환하는 함수
// 예) 1234567 -> "1,234,567"
// long long 을 int64_t 로 바꾸고싶으면 #include <cstdint> 를 추가하고 int64_t 로 바꾸면 됩니다.
/*
long long: C++ 표준 기본 타입이라 헤더 include 없이 바로 쓸 수 있고, "최소 64비트"만 보장합니다(대부분의 플랫폼에서 정확히 64비트지만 표준상 보장은 아님).
int64_t: <cstdint>를 include해야 하고, 정확히 64비트임을 명시적으로 보장합니다. 크기가 중요한 코드(파일 포맷, 네트워크 프로토콜, 크로스플랫폼 일관성이 중요한 경우)에는 이쪽이 더 명확합니다.
*/
std::string formatWithComma(long long value);

// 은행 계좌 하나를 표현하는 클래스
// 클래스 = 데이터(변수)와 그 데이터를 다루는 함수(기능)를 하나로 묶어놓은 것
class Account {
public:
    // public: 아래쪽은 클래스 밖에서도 자유롭게 사용할 수 있는 부분입니다.

    // 생성자: Account 객체를 만들 때 자동으로 호출되는 함수
    // 예) Account acc("홍길동", 10000); 이렇게 만들면 이 함수가 실행됩니다.
    Account(const std::string& owner, long long initialBalance);

    // 예금주 이름을 알려주는 함수 (값을 바꾸지 않고 읽기만 함 -> const)
    const std::string& getOwner() const;

    // 현재 잔액을 알려주는 함수
    long long getBalance() const;

    // 입금 기능: 계좌에 돈을 더하는 함수
    void deposit(long long amount);

    // 출금 기능: 계좌에서 돈을 빼는 함수
    // 성공하면 true, 실패(잔액 부족 등)하면 false를 돌려줍니다.
    bool withdraw(long long amount);

    // friend 함수 선언
    // friend로 선언된 함수는 Account 클래스의 멤버 함수가 아니지만,
    // 예외적으로 private/protected 멤버(owner, balance)에 직접 접근할 수 있습니다.
    // 여기서는 계좌 두 개의 balance를 동시에 다뤄야 하는 "이체(transfer)" 기능을
    // 어느 한쪽 클래스의 멤버 함수로 넣기 애매해서 friend 함수로 구현합니다.
    friend bool transfer(Account& from, Account& to, long long amount);

private:
    // private: 아래쪽은 클래스 내부에서만 사용할 수 있는 비공개 데이터입니다.
    // 외부에서 직접 접근하지 못하게 막아서, getOwner()/deposit() 같은
    // 함수를 통해서만 안전하게 값을 읽고 바꿀 수 있게 합니다.

    std::string owner;   // 예금주 이름
    long long balance;   // 현재 잔액 (금액이 클 수 있어 long long 타입 사용)
};

// from 계좌에서 to 계좌로 amount 만큼 돈을 이체하는 함수
// 위에서 friend로 선언했기 때문에, 멤버 함수가 아닌데도
// from.balance, to.balance 처럼 private 멤버에 직접 접근할 수 있습니다.
// 성공하면 true, 실패(금액 오류/잔액 부족)하면 false를 반환합니다.
bool transfer(Account& from, Account& to, long long amount);
