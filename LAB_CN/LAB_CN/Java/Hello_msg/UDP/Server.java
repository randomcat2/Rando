import java.net.*;

class Server {
    public static void main(String[] args) throws Exception {
        DatagramSocket ds = new DatagramSocket(1234);
        byte[] b = new byte[100];
        DatagramPacket dp = new DatagramPacket(b, b.length);
        System.out.println("Server running. Waiting for messages...");
        ds.receive(dp);
        String msg = new String(b, 0, dp.getLength());
        System.out.println("Received: " + msg);
    }
}
