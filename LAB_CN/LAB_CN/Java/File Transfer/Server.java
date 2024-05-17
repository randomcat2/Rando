import java.io.*;
import java.net.*;

public class Server {
    public static void main(String args[]) throws Exception {
        DatagramSocket serverSocket = new DatagramSocket(9876);
        byte[] receiveData = new byte[1024];
        
        // Specify the destination directory
        String destinationDirectory = "C:\\Users\\admin\\OneDrive\\Desktop\\LAB_CN\\";

        while (true) {
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            serverSocket.receive(receivePacket);
            
            // Extract file name and data
            ByteArrayInputStream bais = new ByteArrayInputStream(receivePacket.getData());
            BufferedReader br = new BufferedReader(new InputStreamReader(bais));
            String fileName = br.readLine();
            
            FileOutputStream fos = new FileOutputStream(destinationDirectory + fileName);
            
            byte[] fileData = new byte[1024];
            int bytesRead;
            while ((bytesRead = bais.read(fileData)) != -1) {
                fos.write(fileData, 0, bytesRead);
            }
            
            fos.close();
            br.close();
        }
    }
}
