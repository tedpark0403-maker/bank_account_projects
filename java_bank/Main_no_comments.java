import java.util.Scanner;

public class Main_no_comments {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Account acc = new Account("홍길동", 10000);
        System.out.printf("[%s]님의 계좌가 생성되었습니다. (초기 잔액: %,d원)%n", acc.getOwner(), acc.getBalance());

        boolean running = true;

        while (running) {
            System.out.println("\n=== 은행 메뉴 ===");
            System.out.println("1. 입금 | 2. 출금 | 3. 잔액 조회 | 4. 종료");
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
