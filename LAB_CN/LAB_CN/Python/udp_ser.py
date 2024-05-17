import socket

server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_address = ("localhost",12345)
server_socket.bind(server_address)

print("Server is running...")

while True:
    data, client_address = server_socket.recvfrom(1024)
    
    print(f"Received from client {data.decode()}")
    
    server_socket.sendto(b"Hello from Server", client_address)