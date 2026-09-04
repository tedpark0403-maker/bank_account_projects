"""
Python 기초 프로젝트: 콘솔 은행 계좌 관리 시스템
- 객체지향 기초 (클래스, 생성자, 메서드)
- 콘솔 인터랙션 및 입출금 예외 처리
"""

class Account:
    def __init__(self, owner: str, balance: float = 0.0):
        self.owner = owner
        self.balance = balance

    def deposit(self, amount: float) -> None:
        if amount <= 0:
            print("입금액은 0원보다 커야 합니다.")
            return
        self.balance += amount
        print(f"{amount:,.0f}원 입금 완료 (현재 잔액: {self.balance:,.0f}원)")

    def withdraw(self, amount: float) -> bool:
        if amount <= 0:
            print("출금액은 0원보다 커야 합니다.")
            return False
        if amount > self.balance:
            print("잔액이 부족합니다.")
            return False
        self.balance -= amount
        print(f"{amount:,.0f}원 출금 완료 (현재 잔액: {self.balance:,.0f}원)")
        return True


def run_bank_app():
    acc = Account("홍길동", 10000)
    print(f"[{acc.owner}]님의 계좌가 생성되었습니다. (초기 잔액: {acc.balance:,.0f}원)")

    while True:
        print("\n=== 은행 메뉴 ===")
        print("1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 종료")
        choice = input("선택 >> ").strip()

        if choice == "1":
            try:
                amount = float(input("입금할 금액: "))
                acc.deposit(amount)
            except ValueError:
                print("올바른 숫자를 입력하세요.")

        elif choice == "2":
            try:
                amount = float(input("출금할 금액: "))
                acc.withdraw(amount)
            except ValueError:
                print("올바른 숫자를 입력하세요.")

        elif choice == "3":
            print(f"[{acc.owner}]님의 현재 잔액: {acc.balance:,.0f}원")

        elif choice == "4":
            print("프로그램을 종료합니다.")
            break

        else:
            print("잘못된 선택입니다. 다시 입력해주세요.")


if __name__ == "__main__":
    run_bank_app()
