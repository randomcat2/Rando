import java.util.Scanner;

public class Subnet {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter IP Address: ");
        String ip = scanner.nextLine();
        char classip = determineClass(ip);
        System.out.println("Class: " + classip);
        System.out.print("Enter the number of subnets: ");
        int subnets = scanner.nextInt();
        subnetMask(ip, subnets);
        scanner.close();
    }

    public static char determineClass(String ip) {
        String[] octets = ip.split("\\.");
        int first_octet = Integer.parseInt(octets[0]);

        if (first_octet >= 1 && first_octet <= 126)
            return 'A';
        else if (first_octet >= 128 && first_octet <= 191)
            return 'B';
        else if (first_octet >= 192 && first_octet <= 223)
            return 'C';
        else if (first_octet >= 224 && first_octet <= 239)
            return 'D';
        else
            return 'E';
    }

    public static void subnetMask(String ip, int subnets) {
        String[] octets = ip.split("\\.");
        int[] octet = new int[4];

        for (int i = 0; i < 4; i++) {
            octet[i] = Integer.parseInt(octets[i]);
        }

        int bits = 0;
        while ((1 << bits) < subnets)
            bits++;

        int[] mask = new int[4];
        for (int i = 0; i < 4; i++) {
            if (bits >= 8) {
                mask[i] = 255;
                bits -= 8;
            } else if (bits > 0) {
                mask[i] = (255 << (8 - bits)) & 255;
                bits = 0;
            } else {
                mask[i] = 0;
            }
        }

        System.out.println("Subnet Ranges:");
        for (int i = 0; i < subnets; i++) {
            int start = i * (256 / subnets);
            int end = (i + 1) * (256 / subnets) - 1;
            System.out.printf("Subnet %d: %d.%d.%d.%d - %d.%d.%d.%d%n", i + 1,
                    octet[0], octet[1], octet[2], start,
                    octet[0], octet[1], octet[2], end);
        }
    }
}