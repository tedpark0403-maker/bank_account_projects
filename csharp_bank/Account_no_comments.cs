namespace BankApp;

public class Account
{
    public string Owner { get; }
    public decimal Balance { get; private set; }

    public Account(string owner, decimal initialBalance = 0)
    {
        Owner = owner;
        Balance = initialBalance;
    }

    public void Deposit(decimal amount)
    {
        if (amount <= 0)
        {
            Console.WriteLine("입금액은 0원보다 커야 합니다.");
            return;
        }
        Balance += amount;
        Console.WriteLine($"{amount:N0}원 입금 완료 (현재 잔액: {Balance:N0}원)");
    }

    public bool Withdraw(decimal amount)
    {
        if (amount <= 0)
        {
            Console.WriteLine("출금액은 0원보다 커야 합니다.");
            return false;
        }
        if (amount > Balance)
        {
            Console.WriteLine("잔액이 부족합니다.");
            return false;
        }
        Balance -= amount;
        Console.WriteLine($"{amount:N0}원 출금 완료 (현재 잔액: {Balance:N0}원)");
        return true;
    }
}
