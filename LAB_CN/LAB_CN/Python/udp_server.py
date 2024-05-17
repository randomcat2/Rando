import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ("localhost", 12346)
server_socket.bind(server_address)

print("Server is running...")

while True:
    data, client_address = server_socket.recvfrom(1024)

    print(f"Received from client {client_address}: {data.decode()}")

    server_socket.sendto(b"Hello from server!", client_address)