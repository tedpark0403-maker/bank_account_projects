public class SavingsAccount_no_comments implements BankAccount {
    private static final long MINIMUM_BALANCE = 1000;

    private final String owner;
    private long balance;

    public SavingsAccount_no_comments(String owner, long initialBalance) {
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
        if (this.balance - amount < MINIMUM_BALANCE) {
            System.out.printf("저축 계좌는 최소 %,d원을 유지해야 하므로 출금할 수 없습니다.%n", MINIMUM_BALANCE);
            return false;
        }
        this.balance -= amount;
        System.out.printf("%,d원 출금 완료 (현재 잔액: %,d원)%n", amount, this.balance);
        return true;
    }

    public void addInterest(double annualRatePercent) {
        long interest = (long) (this.balance * (annualRatePercent / 100.0));
        this.balance += interest;
        System.out.printf("이자 %,d원이 지급되었습니다. (현재 잔액: %,d원)%n", interest, this.balance);
    }
}
