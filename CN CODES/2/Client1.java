
import java.io.*;
import java.net.*;

public class Client1 {
    public static void main(String[] args) {
        try {
            // Specify the server's IP address and port
            InetAddress serverAddress = InetAddress.getByName("127.0.0.1");
            int serverPort = 12345;

            // Create a DatagramSocket for sending and receiving datagrams
            DatagramSocket clientSocket = new DatagramSocket();

            // Send a message to the server
            String message = "Hello, This is Prasad!";
            byte[] sendData = message.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);
            clientSocket.send(sendPacket);

            // Create a buffer to store incoming data
            byte[] receiveData = new byte[1024];

            // Create a DatagramPacket to receive data from the server
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            // Wait for a response from the server
            clientSocket.receive(receivePacket);

            // Extract the response from the received packet
            String response = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Server response: " + response);

            // Close the socket
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
