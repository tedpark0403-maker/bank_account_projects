# Java 은행 계좌 프로젝트 (interface 버전)

`java_bank`가 class 하나로 계좌를 표현했다면, 이 프로젝트는 **interface**를 사용해서
"서로 다른 종류의 계좌(일반 계좌 / 저축 계좌)"를 같은 방식으로 다루는 방법을 보여줍니다.

## 파일 구성
- `BankAccount.java` — 계좌라면 반드시 지켜야 할 규칙(입금/출금/잔액조회 등)만 정의한 **interface**
- `CheckingAccount.java` — BankAccount를 구현한 일반 입출금 계좌 (class)
- `SavingsAccount.java` — BankAccount를 구현한 저축 계좌 (class). 최소 잔액 유지 규칙과
  이자 지급(`addInterest`) 기능이 추가로 있습니다.
- `Main.java` — 두 계좌를 `BankAccount` 타입 하나로 다루는 예제

## class와 interface의 차이
- **class**: 데이터와 동작을 실제로 구현한 완성된 설계도
- **interface**: "이런 기능이 반드시 있어야 한다"는 약속만 정의하고, 실제 구현은 없는 설계도.
  이 인터페이스를 `implements`하는 클래스가 각자 자기 방식대로 구현을 채워 넣습니다.

이렇게 나누면 `Main.java`처럼 계좌를 사용하는 코드는 그 계좌가 정확히 어떤 클래스인지 몰라도
`BankAccount` 타입으로만 다루면 되고, 나중에 새로운 계좌 종류(예: 마이너스 통장)가 추가돼도
사용하는 쪽 코드는 거의 그대로 유지할 수 있습니다.

## 컴파일 및 실행
```bash
javac BankAccount.java CheckingAccount.java SavingsAccount.java Main.java
java Main
```
