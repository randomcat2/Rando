import java.io.*;
import java.net.*;

public class UDPServer {
    public static void main(String[] args) {
        int port = 12345; // Port number
        DatagramSocket socket = null;

        try {
            socket = new DatagramSocket(port);
            byte[] receiveBuffer = new byte[1024];

            System.out.println("Server waiting for client...");

            DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            socket.receive(receivePacket);

            // Extracting client's information
            InetAddress clientAddress = receivePacket.getAddress();
            int clientPort = receivePacket.getPort();

            System.out.println("Client connected: " + clientAddress + ":" + clientPort);

            // Receiving file name
            String fileName = new String(receivePacket.getData()).trim();

            // Reading file contents
            FileInputStream fis = new FileInputStream(fileName);
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                baos.write(buffer, 0, bytesRead);
            }

            byte[] fileBytes = baos.toByteArray();

            // Sending file contents to client
            DatagramPacket sendPacket = new DatagramPacket(fileBytes, fileBytes.length, clientAddress, clientPort);
            socket.send(sendPacket);

            System.out.println("File sent");

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (socket != null) {
                socket.close();
            }
        }
    }
}