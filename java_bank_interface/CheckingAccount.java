// CheckingAccount.java
// "일반 입출금 계좌" — BankAccount 인터페이스를 implements(구현)하는 클래스입니다.
//
// implements를 쓰면, 이 클래스는 BankAccount 인터페이스에 있는 메서드들
// (getOwner, getBalance, deposit, withdraw)을 전부 실제 코드로 채워 넣어야 합니다.
// 하나라도 빠뜨리면 컴파일 오류가 납니다. (인터페이스는 "약속"이기 때문에 지켜야 함)
public class CheckingAccount implements BankAccount {
    private final String owner;
    private long balance;

    public CheckingAccount(String owner, long initialBalance) {
        this.owner = owner;
        this.balance = initialBalance;
    }

    @Override // 인터페이스(또는 부모 클래스)의 메서드를 구현/재정의한다는 표시
    public String getOwner() {
        return owner;
    }

    @Override
    public long getBalance() {
        return balance;
    }

    @Override
    public void deposit(long amount) {
        if (amount <= 0) {
            System.out.println("입금액은 0원보다 커야 합니다.");
            return;
        }
        this.balance += amount;
        System.out.printf("%,d원 입금 완료 (현재 잔액: %,d원)%n", amount, this.balance);
    }

    @Override
    public boolean withdraw(long amount) {
        if (amount <= 0) {
            System.out.println("출금액은 0원보다 커야 합니다.");
            return false;
        }
        if (amount > this.balance) {
            System.out.println("잔액이 부족합니다.");
            return false;
        }
        this.balance -= amount;
        System.out.printf("%,d원 출금 완료 (현재 잔액: %,d원)%n", amount, this.balance);
        return true;
    }
}
