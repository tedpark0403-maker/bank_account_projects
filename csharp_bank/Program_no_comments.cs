using System;

namespace BankApp;

class Program
{
    static void Main()
    {
        var acc = new Account("홍길동", 10000);
        Console.WriteLine($"[{acc.Owner}]님의 계좌가 생성되었습니다. (초기 잔액: {acc.Balance:N0}원)");

        bool isRunning = true;

        while (isRunning)
        {
            Console.WriteLine("\n=== 은행 메뉴 ===");
            Console.WriteLine("1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 종료");
            Console.Write("선택 >> ");
            string? choice = Console.ReadLine()?.Trim();

            switch (choice)
            {
                case "1":
                    Console.Write("입금할 금액: ");
                    if (decimal.TryParse(Console.ReadLine(), out decimal depAmount))
                    {
                        acc.Deposit(depAmount);
                    }
                    else
                    {
                        Console.WriteLine("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "2":
                    Console.Write("출금할 금액: ");
                    if (decimal.TryParse(Console.ReadLine(), out decimal withAmount))
                    {
                        acc.Withdraw(withAmount);
                    }
                    else
                    {
                        Console.WriteLine("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "3":
                    Console.WriteLine($"[{acc.Owner}]님의 현재 잔액: {acc.Balance:N0}원");
                    break;

                case "4":
                    Console.WriteLine("프로그램을 종료합니다.");
                    isRunning = false;
                    break;

                default:
                    Console.WriteLine("잘못된 선택입니다. 다시 입력해주세요.");
                    break;
            }
        }
    }
}
