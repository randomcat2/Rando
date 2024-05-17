import java.io.*;
import java.net.*;
public class Client {
public static void main(String[] args) throws Exception{
        Socket clientSocket = new Socket("localhost", 2020);
        System.out.println("Connected to server");
        // Receive message from the server
        InputStream inputStream = clientSocket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String messageFromServer = reader.readLine();
        System.out.println("Message from server: " + messageFromServer);
        // Close the connection
        clientSocket.close();
}
}