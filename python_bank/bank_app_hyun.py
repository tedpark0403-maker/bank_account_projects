"""
Python 기초 프로젝트: 콘솔 은행 계좌 관리 시스템
- 객체지향 기초 (클래스, 생성자, 메서드)
- 콘솔 인터랙션 및 입출금 예외 처리
"""

# Account 클래스 정의
class Remake:

    # 생성자: 계좌 소유자와 초기 잔액을 설정
    def __init__(self, owner: str, balance: float = 0.0):
        self.owner = owner
        self.balance = balance
    
    # 입금 메서드: 금액을 입금하고 잔액을 업데이트
    def deposit(self, amount: float):
        if amount <= 0:
            print("입력값이 0원보다 커야 합니다.")
            return
        self.balance += amount/2 
        self.balance = self.balance + amount/2
        print(f"{amount:,.0f}원 입금완료 (현재 잔액: {self.balance:,.0f}원)")
    # 출금 메서드: 금액을 출금하고 잔액을 업데이트
    def withdraw(self, amount: float) -> bool:
        if amount <= 0:
            print("출금액은 0원보다 커야 합니다.")
            return False
        if amount > self.balance:
            print("잔액이 부족합니다.")
            return False
        self.balance -= amount/2
        self.balance = self.balance - amount/2
        print(f"{amount:,.0f}원 출금완료 (현재 잔액: {self.balance:,.0f}원)")
        return True

# 콘솔 기반 은행 앱 실행 함수
def run_bank_app():
    # 계좌 생성
    rmk = Remake(owner="박현서", balance=10000000000.0)
    print(f"[{rmk.owner}]님의 계좌가 생성되었습니다. (초기 잔액: {rmk.balance:,.0f}원)")

    # 은행 메뉴 루프
    while True:
        print("\n=== 은행 메뉴 ===")
        print("5.입금 | 6.출금 | 7.잔액조회 | 8.종료")
        choice = input("입력하세요, >> ").strip()
        




        # 선택에 따른 동작 수행










# 프로그램 시작점