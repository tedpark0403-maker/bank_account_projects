// SavingsAccount.java
// "저축 계좌" — 이것도 BankAccount 인터페이스를 implements(구현)하는 클래스입니다.
//
// CheckingAccount(일반 계좌)와 똑같이 getOwner/getBalance/deposit/withdraw를 갖고 있지만,
// 세부 동작 규칙은 다르게 구현되어 있습니다.
//   1) 출금 시 "최소 유지 잔액" 밑으로는 못 내려가게 막습니다.
//   2) 인터페이스에는 없는 addInterest(이자 지급) 기능이 추가로 있습니다.
//
// 이렇게 같은 인터페이스를 구현해도 클래스마다 내부 동작은 자유롭게 다르게 만들 수 있다는 것이
// 인터페이스의 핵심 포인트입니다. 사용하는 쪽(Main.java)에서는 "BankAccount"라고만 다루면
// CheckingAccount인지 SavingsAccount인지 신경 쓰지 않고 deposit/withdraw를 호출할 수 있습니다.
public class SavingsAccount implements BankAccount {
    private static final long MINIMUM_BALANCE = 1000; // 저축 계좌는 최소 1,000원을 남겨둬야 함

    private final String owner;
    private long balance;

    public SavingsAccount(String owner, long initialBalance) {
        this.owner = owner;
        this.balance = initialBalance;
    }

    @Override
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
        // 저축 계좌만의 규칙: 출금 후 잔액이 최소 유지 잔액보다 적어지면 안 됨
        if (this.balance - amount < MINIMUM_BALANCE) {
            System.out.printf("저축 계좌는 최소 %,d원을 유지해야 하므로 출금할 수 없습니다.%n", MINIMUM_BALANCE);
            return false;
        }
        this.balance -= amount;
        System.out.printf("%,d원 출금 완료 (현재 잔액: %,d원)%n", amount, this.balance);
        return true;
    }

    // BankAccount 인터페이스에는 없는, SavingsAccount만의 고유 기능입니다.
    // 인터페이스 타입(BankAccount)으로는 이 메서드를 호출할 수 없고,
    // SavingsAccount 타입으로 다뤄야만 호출할 수 있습니다.
    public void addInterest(double annualRatePercent) {
        long interest = (long) (this.balance * (annualRatePercent / 100.0));
        this.balance += interest;
        System.out.printf("이자 %,d원이 지급되었습니다. (현재 잔액: %,d원)%n", interest, this.balance);
    }
}
