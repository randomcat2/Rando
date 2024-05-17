import socket

socket_client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ("localhost", 12346)

message = "Hello from client!"

socket_client.sendto(message.encode(), server_address)

data, server = socket_client.recvfrom(1024)

print(f"Received from server: {data.decode()}")

socket_client.close()