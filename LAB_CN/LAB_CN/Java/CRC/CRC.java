import java.util.Scanner;

public class CRC {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get Frame
        System.out.print("Enter Frame size: ");
        int fs = scanner.nextInt();

        int[] f = new int[fs];
        System.out.println("Enter Frame (binary values separated by spaces): ");
        for (int i = 0; i < fs; i++) {
            f[i] = scanner.nextInt();
        }

        // Get Generator
        System.out.print("Enter Generator size: ");
        int gs = scanner.nextInt();

        int[] g = new int[gs];
        System.out.println("Enter Generator (binary values separated by spaces): ");
        for (int i = 0; i < gs; i++) {
            g[i] = scanner.nextInt();
        }

        // Append 0's
        int rs = gs - 1;
        System.out.println("Number of 0's to be appended: " + rs);
        int[] temp = new int[fs + rs];
        System.arraycopy(f, 0, temp, 0, fs);

        // Division
        for (int i = 0; i < fs; i++) {
            if (temp[i] == 1) {
                for (int j = 0; j < gs; j++) {
                    temp[i + j] ^= g[j];
                }
            }
        }

        // CRC
        int[] crc = new int[rs];
        for (int i = fs, j = 0; i < fs + rs; i++, j++) {
            crc[j] = temp[i];
        }

        System.out.print("Transmitted Frame: ");
        int[] tf = new int[fs + rs];
        for (int i = 0; i < fs; i++) {
            tf[i] = f[i];
        }

        for (int i = fs, j = 0; i < fs + rs; i++, j++) {
            tf[i] = crc[j];
        }

        for (int i = 0; i < fs + rs; i++) {
            System.out.print(tf[i]);
        }

        // Receiver side
        System.out.println("\n\nReceiver side : ");
        System.out.print("Received Frame: ");
        for (int i = 0; i < fs + rs; i++) {
            System.out.print(tf[i]);
        }

        // Division
        for (int i = 0; i < fs; i++) {
            if (temp[i] == 1) {
                for (int j = 0; j < gs; j++) {
                    temp[i + j] ^= g[j];
                }
            }
        }

        System.out.print("\nRemainder: ");
        int[] rrem = new int[rs];
        for (int i = fs, j = 0; i < fs + rs; i++, j++) {
            rrem[j] = temp[i];
        }

        for (int i = 0; i < rs; i++) {
            System.out.print(rrem[i]);
        }

        boolean isError = false;
        for (int i = 0; i < rs; i++) {
            if (rrem[i] != 0) {
                isError = true;
                break;
            }
        }

        if (!isError) {
            System.out.println("\nRemainder = 0, Message Is Correct");
        } else {
            System.out.println("\nRemainder != 0, Message Contains Error");
        }

        scanner.close();
    }
}