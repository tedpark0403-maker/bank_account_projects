public interface BankAccount_no_comments {

    String getOwner();

    long getBalance();

    void deposit(long amount);

    boolean withdraw(long amount);
}
