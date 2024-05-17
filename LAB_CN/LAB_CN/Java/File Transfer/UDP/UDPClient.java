import java.io.*;
import java.net.*;

public class UDPClient {
    public static void main(String[] args) {
        String serverAddress = "127.0.0.1"; // Server IP address
        int serverPort = 12345; // Server port number

        DatagramSocket socket = null;

        try {
            socket = new DatagramSocket();
            InetAddress serverIPAddress = InetAddress.getByName(serverAddress);

            // File to send
            String fileName = "C:\\Users\\saksh\\OneDrive\\Attachments\\Assign.6.R";
            byte[] fileNameBytes = fileName.getBytes();

            // Sending file name to server
            DatagramPacket fileNamePacket = new DatagramPacket(fileNameBytes, fileNameBytes.length, serverIPAddress, serverPort);
            socket.send(fileNamePacket);

            // Receiving file contents from server
            byte[] receiveBuffer = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            socket.receive(receivePacket);

            // Saving received file
            FileOutputStream fos = new FileOutputStream("received_file.txt");
            fos.write(receivePacket.getData(), 0, receivePacket.getLength());
            fos.close();

            System.out.println("File received");

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (socket != null) {
                socket.close();
            }
        }
    }
}

