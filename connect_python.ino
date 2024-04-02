#include <WiFi.h>
#include <WiFiMulti.h>
// #include <HardwareSerial.h>
WiFiMulti wifiMulti;

WiFiServer server(80);  // Số cổng tùy chọn
// HardwareSerial arduinoSerial(1);  // Khởi tạo UART trên cổng Serial1

// const char* ssid = "TAN TIEN";
// const char* password = "14012003";
// const char* ssid = "HUEUNI-OFFICE";
// const char* password = "hueuniair";
bool isProcessing = false; //Biến theo dõi quá trình xử lý

void setup() {
    // Khởi tạo nhiều kết nối wifi
    wifiMulti.addAP("TAN TIEN", "14012003");
    // wifiMulti.addAP("FPT Telecom ", "12345678");
    wifiMulti.addAP("HUEUNI-OFFICE", "hueuniair");        
    Serial.begin(115200);

    // WiFi.begin(ssid, password);WiFi.status() != WL_CONNECTED
    while (wifiMulti.run() != WL_CONNECTED) {
        delay(100);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    Serial2.begin(9600);  // Khởi tạo UART trên cổng Serial2 với baudrate 9600 - UART2(RX-16,TX-17)

}

void loop() {
    WiFiClient client = server.available() ;
    if (client) {
        Serial.println("Client connected");
        while (client.connected()) {
            // while (client.available()) {
              char act = client.read(); //Lấy tín hiệu đầu vào từ python "Y"-yes,"N"-no
              Serial.println("Input from Python: ");
              Serial.println(act);
              client.println("From ESP32");
              if ((String(act) == "Y") && (!isProcessing) ){
                  Serial.println("Processing!");
                  Serial2.println("Y");  // Chuyển dữ liệu từ ESP32 tới Arduino qua Serial1
                  isProcessing = true;
                  while (Serial2.available() == 0) {}   ;
                }
            // }
              if (Serial2.available()){
                String a = Serial2.readStringUntil('\n');
                a.trim();
                if (a.equals("C")){
                  Serial.println("From arduino:");
                  Serial.println(a);
                  Serial.println("Complete!");
                  // client.println("C");
                  isProcessing = false ; // Kết thúc quá trình xử lý
                }
              } 
          }
        }
    }

