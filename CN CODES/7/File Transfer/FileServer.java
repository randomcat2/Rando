import java.io.*;
import java.net.*;

public class FileServer {
    public static void main(String[] args) {
        System.out.println("Listening");
        try {
            ServerSocket serverSocket = new ServerSocket(5000);
            Socket connectionSocket = serverSocket.accept();
            
            byte[] buffer = new byte[256];
            int bytesRead;
            
            FileInputStream fileInputStream = new FileInputStream("sample_file.txt");
            OutputStream outputStream = connectionSocket.getOutputStream();
            
            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            
            outputStream.close();
            fileInputStream.close();
            serverSocket.close();
            System.out.println("File sent successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}