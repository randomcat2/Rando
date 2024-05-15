
import java.io.*;
import java.net.*;

public class Server1 {
    public static void main(String[] args) {
        try {
            // Create a DatagramSocket to listen for incoming datagrams on a specific port (e.g., 12345)
            DatagramSocket serverSocket = new DatagramSocket(12345);

            System.out.println("Server is listening on port 12345...");

            // Create a buffer to store incoming data
            byte[] receiveData = new byte[1024];

            // Create a DatagramPacket to receive data from the client
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            // Wait for a client to send a datagram
            serverSocket.receive(receivePacket);
            System.out.println("Client connected.");

            // Extract the message from the received packet
            String message = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Received from client: " + message);

            // Get client's address and port from the received packet
            InetAddress clientAddress = receivePacket.getAddress();
            int clientPort = receivePacket.getPort();

            // Send a response back to the client
            String response = "This is the server, I got your message, client";
            byte[] sendData = response.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);
            serverSocket.send(sendPacket);

            // Close the socket
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
