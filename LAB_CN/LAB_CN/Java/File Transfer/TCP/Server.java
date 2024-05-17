import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        int port = 12345; // Port number
        try {
            ServerSocket serverSocket = new ServerSocket(port);
            System.out.println("Server waiting for client on port " + port);

            Socket socket = serverSocket.accept();
            System.out.println("Client connected");

            // Create input stream to read file sent by client
            InputStream in = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(in));

            // Read file name
            String fileName = reader.readLine();

            // Create output stream to write file
            FileOutputStream fos = new FileOutputStream(fileName);
            BufferedOutputStream bos = new BufferedOutputStream(fos);

            // Read file data from client and write to file
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                bos.write(buffer, 0, bytesRead);
            }

            bos.close();
            socket.close();
            serverSocket.close();
            System.out.println("File received");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}