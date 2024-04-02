import cv2
from roboflow import Roboflow
from PIL import Image, ImageDraw
import socket


# # Tải model từ roboflow
rf = Roboflow(api_key="ClU348z8rvLeHCiL5VO0")
project = rf.workspace().project("bottle_detect-hhoxt")
model = project.version(1).model

# # 0 là số ID của camera, có thể là 0 hoặc 1 tùy thiết bị
cap = cv2.VideoCapture(0)

# Địa chỉ server
esp32_ip = "10.2.24.43"
esp32_port = 80


def send_data(data: str):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, esp32_port))
        s.sendall(data.encode())
        print("Đã gửi tín hiệu cho ESP32!")
        response = s.recv(1024)q
        if response.decode() == "C":
            print("Complete!")



while True:
    # # Đọc một khung hình từ camera
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    # Kiểm tra xem việc đọc khung hình có thành công không
    if not ret:
        print("error")
        break

    # # Thực hiện dự đoán trên khung hình từ camera
    detections = model.predict(frame, confidence=50, overlap=30).json() #Kích thước ảnh là 640-640: theo kích thước trên roboflow
    predic = detections['predictions']
    for _ in predic:
        label = _["class"]
        confid = _["confidence"]
        cv2.putText(frame, label + ": " + str(round(confid, 1)),
                    (round(_["x"]), round(_["y"])), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
        cv2.putText(frame, "Center",
                    (center_x,center_y), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
        
        if label == "bottle":
            send_data("Y") # Y-yes: có bottle.
    cv2.imshow("Camera", frame)

    # Để thoát vòng lặp, nhấn phím 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Giải phóng tài nguyên
cap.release()
cv2.destroyAllWindows()
