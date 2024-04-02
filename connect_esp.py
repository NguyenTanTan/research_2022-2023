import socket

esp32_ip = "10.9.5.107"
esp32_port = 80

data_to_send = "Hello from Python"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((esp32_ip, esp32_port))
    s.sendall(data_to_send.encode())
    response = s.recv(1024)
    print("Received:", response.decode())
    print("Đã hoàn thành")
