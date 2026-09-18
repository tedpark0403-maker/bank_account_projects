public class Account_no_comments {
    private final String owner;
    private long balance;

    public Account_no_comments(String owner, long initialBalance) {
        this.owner = owner;
        this.balance = initialBalance;
    }

    public String getOwner() {
        return owner;
    }

    public long getBalance() {
        return balance;
    }

    public void deposit(long amount) {
        if (amount <= 0) {
            System.out.println("입금액은 0원보다 커야 합니다.");
            return;
        }
        this.balance += amount;
        System.out.printf("%,d원 입금 완료 (현재 잔액: %,d원)%n", amount, this.balance);
    }

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
