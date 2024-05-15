import java.util.*;

public class IPAddress {
    public static void ExtractIP(String sourceString, short[] ipaddress) {
        int len = sourceString.length();
        short oct[] = new short[4];
        int cnt = 0;
        int cnt1 = 0;
        StringBuilder buf = new StringBuilder();

        for (int i = 0; i < len; i++) {
            char c = sourceString.charAt(i);
            if (c != '.') {
                buf.append(c);
            }
            if (c == '.' || i == len - 1) {
                oct[cnt1++] = Short.parseShort(buf.toString());
                cnt = 0;
                buf.setLength(0);
            }
        }

        ipaddress[0] = oct[0];
        ipaddress[1] = oct[1];
        ipaddress[2] = oct[2];
        ipaddress[3] = oct[3];
    }

    static boolean isPrivate(short[] ip) {
        return (ip[0] == 10) ||
                (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) ||
                (ip[0] == 192 && ip[1] == 168);
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter ip address (xxx.xxx.xxx.xxx format): ");
        String ip = sc.nextLine();
        short[] ipAddress = new short[4];
        ExtractIP(ip,ipAddress);

        System.out.printf("\nIp Address: %03d.%03d.%03d.%03d\n", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);

        if (ipAddress[0] >= 0 && ipAddress[0] <= 127)
            System.out.println("Class A Ip Address.");
        if (ipAddress[0] > 127 && ipAddress[0] < 191)
            System.out.println("Class B Ip Address.");
        if (ipAddress[0] > 191 && ipAddress[0] < 224)
            System.out.println("Class C Ip Address.");
        if (ipAddress[0] > 224 && ipAddress[0] <= 239)
            System.out.println("Class D Ip Address.");
        if (ipAddress[0] > 239)
            System.out.println("Class E Ip Address.");

        if (isPrivate(ipAddress)) {
            System.out.printf("The IP address %d.%d.%d.%d is private.\n", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
        } else {
            System.out.printf("The IP address %d.%d.%d.%d is public.\n", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
        }

    }

}