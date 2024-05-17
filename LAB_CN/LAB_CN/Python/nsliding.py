import time
from typing import List

# Structure to represent a packet
class Packet:
    def __init__(self, seq_num: int, data: str):
        self.seq_num = seq_num
        self.data = data

# Structure to represent a peer
class Peer:
    def __init__(self, name: str, window_size: int, timeout: int):
        self.name = name
        self.window_size = window_size
        self.timeout = timeout
        self.next_seq_num = 0
        self.expected_seq_num = 0
        self.sent_packets: List[Packet] = []
        self.received_packets: List[Packet] = []

    # Send a packet
    def send_packet(self, data: str):
        if len(self.sent_packets) - self.expected_seq_num < self.window_size:
            packet = Packet(self.next_seq_num, data)
            self.next_seq_num += 1
            self.sent_packets.append(packet)
            print(f"{self.name} sent packet with sequence number: {packet.seq_num}")
        else:
            print(f"{self.name} Window full. Waiting for acknowledgment.")

    # Receive a packet
    def receive_packet(self, packet: Packet):
        if packet.seq_num == self.expected_seq_num:
            self.received_packets.append(packet)
            print(f"{self.name} received packet with sequence number: {packet.seq_num}")
            self.expected_seq_num += 1
            # Send acknowledgment
            time.sleep(1)  # Simulating delay
            print(f"{self.name} sending acknowledgment for sequence number: {packet.seq_num}")
        else:
            print(f"{self.name} received out-of-order packet. Discarding.")

# Main function to simulate the communication
def main():
    peer1 = Peer("Peer 1", 3, 1)  # Name, window size, timeout
    peer2 = Peer("Peer 2", 3, 1)

    # Simulating sending packets from peer 1 to peer 2
    peer1.send_packet("Packet 1 from Peer 1")
    peer1.send_packet("Packet 2 from Peer 1")
    peer1.send_packet("Packet 3 from Peer 1")
    peer1.send_packet("Packet 4 from Peer 1")

    # Simulating receiving packets at peer 2
    packet1 = Packet(0, "Packet 1 from Peer 1")
    peer2.receive_packet(packet1)

    packet2 = Packet(1, "Packet 2 from Peer 1")
    peer2.receive_packet(packet2)

    packet3 = Packet(3, "Packet 4 from Peer 1")
    peer2.receive_packet(packet3)

if __name__ == "__main__":
    main()
