import java.net.*;

class Client {
    public static void main(String[] args) throws Exception {
        DatagramSocket ds = new DatagramSocket();
        byte[] b = "Hello".getBytes();
        int port = 1234;
        InetAddress address = InetAddress.getLocalHost(); // Assuming sending to localhost
        DatagramPacket dp = new DatagramPacket(b, b.length, address, port);
        ds.send(dp);
    }
}
