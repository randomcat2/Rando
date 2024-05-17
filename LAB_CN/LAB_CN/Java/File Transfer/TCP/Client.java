import java.io.*;
import java.net.*;

public class \Client {
    public static void main(String[] args) {
        String serverAddress = "127.0.0.1"; // Server IP address
        int port = 12345; // Server port number

        try {
            Socket socket = new Socket(serverAddress, port);
            System.out.println("Connected to server");

            // File to send
            String filePath = "C:\\Users\\saksh\\OneDrive\\Attachments\\index.js";
            File file = new File(filePath);

            // Create output stream to send file to server
            OutputStream out = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(out, true);

            // Send file name
            writer.println(file.getName());

            // Create input stream to read file
            FileInputStream fis = new FileInputStream(file);
            BufferedInputStream bis = new BufferedInputStream(fis);

            // Send file data to server
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = bis.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }

            bis.close();
            socket.close();
            System.out.println("File sent");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}