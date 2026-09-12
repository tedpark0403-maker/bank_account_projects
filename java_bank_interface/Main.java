import java.util.Scanner;

// Main.java
// 인터페이스(BankAccount)를 활용해서 "서로 다른 종류의 계좌"를 똑같은 방식으로
// 다루는 모습을 보여주는 예제입니다.
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // 배열의 타입을 BankAccount(인터페이스)로 선언했습니다.
        // 실제로 담기는 값은 CheckingAccount, SavingsAccount로 서로 다른 클래스지만
        // 둘 다 BankAccount 인터페이스를 구현했기 때문에 같은 배열에 담을 수 있습니다.
        BankAccount[] accounts = {
                new CheckingAccount("홍길동", 10000),
                new SavingsAccount("김철수", 5000)
        };

        System.out.println("=== 계좌 목록 ===");
        for (int i = 0; i < accounts.length; i++) {
            // accounts[i]의 실제 타입이 CheckingAccount든 SavingsAccount든 상관없이
            // BankAccount 인터페이스에 정의된 getOwner()/getBalance()를 그대로 호출할 수 있습니다.
            System.out.printf("%d. [%s]님 (%s) - 잔액: %,d원%n",
                    i + 1,
                    accounts[i].getOwner(),
                    accounts[i].getClass().getSimpleName(),
                    accounts[i].getBalance());
        }

        System.out.print("\n조작할 계좌 번호를 선택하세요: ");
        int index = Integer.parseInt(scanner.nextLine().trim()) - 1;

        // 인터페이스 타입의 변수 acc는 두 계좌 타입을 모두 가리킬 수 있습니다.
        // 이렇게 인터페이스 타입으로 실제 객체를 다루는 것을 "다형성(polymorphism)"이라고 합니다.
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
                        // acc의 실제 타입이 CheckingAccount든 SavingsAccount든,
                        // 각 클래스가 구현해 둔 deposit()이 알아서 실행됩니다.
                        acc.deposit(amount);
                    } catch (NumberFormatException e) {
                        System.out.println("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "2":
                    System.out.print("출금할 금액: ");
                    try {
                        long amount = Long.parseLong(scanner.nextLine().trim());
                        // 여기서도 마찬가지로, 계좌 종류에 따라 다른 출금 규칙이 자동으로 적용됩니다.
                        // (SavingsAccount는 최소 잔액 규칙이 있고, CheckingAccount는 없습니다.)
                        acc.withdraw(amount);
                    } catch (NumberFormatException e) {
                        System.out.println("올바른 숫자를 입력하세요.");
                    }
                    break;

                case "3":
                    System.out.printf("[%s]님의 현재 잔액: %,d원%n", acc.getOwner(), acc.getBalance());
                    break;

                case "4":
                    // addInterest()는 BankAccount 인터페이스에 없는, SavingsAccount만의 기능입니다.
                    // 그래서 BankAccount 타입인 acc로는 바로 호출할 수 없고,
                    // "이 계좌가 진짜로 SavingsAccount가 맞는지" instanceof로 확인한 뒤
                    // SavingsAccount 타입으로 형변환(cast)해야 호출할 수 있습니다.
                    if (acc instanceof SavingsAccount) {
                        SavingsAccount savings = (SavingsAccount) acc;
                        savings.addInterest(2.0); // 연 2% 이자 지급 예시
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
