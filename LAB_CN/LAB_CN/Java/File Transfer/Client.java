import java.io.*;
import java.net.*;

public class Client {
    public static void main(String args[]) throws Exception {
        DatagramSocket clientSocket = new DatagramSocket();
        InetAddress IPAddress = InetAddress.getByName("localhost"); // Change to server IP if needed

        // File path declaration
        String filePath = "C:\\Users\\admin\\OneDrive\\Desktop\\abc.txt"; // Replace with your file path

        // For a script file
        // String filePath = "C:\\Users\\admin\\OneDrive\\Desktop\\script.js";

        // For an audio file
        // String filePath = "C:\\Users\\admin\\OneDrive\\Desktop\\audio.mp3";

        // For a video file
        // String filePath = "C:\\Users\\admin\\OneDrive\\Desktop\\video.mp4";

        File file = new File(filePath);
        FileInputStream fis = new FileInputStream(file);
        BufferedInputStream bis = new BufferedInputStream(fis);
        byte[] sendData = new byte[1024];
        sendData = file.getName().getBytes(); // Send file name first
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
        clientSocket.send(sendPacket);

        int bytesRead;
        while ((bytesRead = bis.read(sendData)) != -1) {
            sendPacket = new DatagramPacket(sendData, bytesRead, IPAddress, 9876);
            clientSocket.send(sendPacket);
        }

        bis.close();
        clientSocket.close();
        System.out.println("File transfer complete.");
    }
}
