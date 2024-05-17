import java.net.*;
import java.io.*;
class client{
	public static void main(String[] args) throws Exception{
		DatagramSocket ds = new DatagramSocket();
		byte [] b = "Server".getBytes();
		InetAddress ip = InetAddress.getByName("localhost");
		int port = 2001;


		DatagramPacket dp = new DatagramPacket(b,b.length,ip,2001);
		ds.send(dp);
		
	}


}

class server{
	public static void main(String[] args) throws Exception{
		DatagramSocket ds = new DatagramSocket(2001);
		byte [] b = new byte[100];
		DatagramPacket dp = new DatagramPacket(b,b.length);
		ds.receive(dp);
		String msg = new String(b);
		System.out.println("Hello"+msg);
	}
}
