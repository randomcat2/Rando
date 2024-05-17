import java.net.*;

class client{
public static void main(String arg[]) throws Exception{


ServerSocket s = new ServerSocket(2021);
Socket so = s.accept();
System.out.println("Connection Established!!...");

}

}