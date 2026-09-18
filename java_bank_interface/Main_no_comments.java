import java.util.Scanner;

public class Main_no_comments {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        BankAccount[] accounts = {
                new CheckingAccount("홍길동", 10000),
                new SavingsAccount("김철수", 5000)
        };

        System.out.println("=== 계좌 목록 ===");
        for (int i = 0; i < accounts.length; i++) {
            System.out.printf("%d. [%s]님 (%s) - 잔액: %,d원%n",
                    i + 1,
                    accounts[i].getOwner(),
                    accounts[i].getClass().getSimpleName(),
                    accounts[i].getBalance());
        }

        System.out.print("\n조작할 계좌 번호를 선택하세요: ");
        int index = Integer.parseInt(scanner.nextLine().trim()) - 1;

        BankAccount acc = accounts[index];

        boolean running = true;
        while (running) {
            System.out.println("\n=== 은행 메뉴 : " + acc.getOwner() + "님 ===");
            System.out.println("1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 이자 지급(저축 계좌 전용) | 5. 종료");
            System.out.print("선택 >> ");
            String choice = scanner.nextLine().trim();

            switch (choice) {
                case "1":
                    System.out.print("입금할 금액: ");
                    try {
                        long amount = Long.parseLong(scanner.nextLine().trim());
                        acc.deposit(amount);
                    } catch (NumberFormatException e) {
                        System.out.println("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "2":
                    System.out.print("출금할 금액: ");
                    try {
                        long amount = Long.parseLong(scanner.nextLine().trim());
                        acc.withdraw(amount);
                    } catch (NumberFormatException e) {
                        System.out.println("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "3":
                    System.out.printf("[%s]님의 현재 잔액: %,d원%n", acc.getOwner(), acc.getBalance());
                    break;

                case "4":
                    if (acc instanceof SavingsAccount) {
                        SavingsAccount savings = (SavingsAccount) acc;
                        savings.addInterest(2.0);
                    } else {
                        System.out.println("이자 지급은 저축 계좌에서만 가능합니다.");
                    }
                    break;

                case "5":
                    System.out.println("프로그램을 종료합니다.");
                    running = false;
                    break;

                default:
                    System.out.println("잘못된 선택입니다. 다시 입력해주세요.");
                    break;
            }
        }
        scanner.close();
    }
}
