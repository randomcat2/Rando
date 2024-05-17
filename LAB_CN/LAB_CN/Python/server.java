import java.net.*;

class server{
public static void main(String arg[]) throws Exception{

ServerSocket s = new ServerSocket(2021);
System.out.println("Server is waiting...");
s.accept();
System.out.println("Connect Established!!...");


}
}