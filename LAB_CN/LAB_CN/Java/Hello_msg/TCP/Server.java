import java.io.*;
import java.net.*;
public class Server {
 public static void main(String[] args) {
 try {
 ServerSocket serverSocket = new ServerSocket(2020);
 System.out.println("Server waiting for connection");
 // Wait for a client to connect
 Socket clientSocket = serverSocket.accept();
 System.out.println("Connection established with client");
 // Send a message to the client
 OutputStream outputStream = clientSocket.getOutputStream();
 PrintWriter writer = new PrintWriter(outputStream, true);
 writer.println("Hello from server!");
 // Close the connection
 clientSocket.close();
 serverSocket.close();
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
}
