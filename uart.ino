void setup() {
  Serial.begin(115200);      // Initialize Serial Monitor for debugging
  Serial2.begin(9600);       // Initialize Serial2 on UART1 for external communication
}

void loop() {
  Serial.println("Gửi tín hiệu");
  Serial2.println("Y");
  delay(100);
  if (Serial2.available()){
      String a = Serial2.readStringUntil('\n');
      a.trim();
      if (a.equals("C")){
        Serial.println("From arduino:");
        Serial.println(a);
        Serial.println("Complete!");
      }
    }

  // if (Serial2.available()) { // Check if there is data available on Serial2
  //   String a = Serial2.readStringUntil('\n'); // Read the incoming string from Serial2
  //   a.trim();
  //   Serial.print("Input: ");
  //   Serial.println(a); // Print the received string to Serial Monitor

  //   if (a.equals("Y")){ // Use equals() method to compare strings
  //     Serial2.println("C"); // Send "C" back through Serial2
  //     Serial.println("Done!"); // Print "Done!" to Serial Monitor
  //   } else {
  //     Serial2.println("C");
  //     Serial.println("Error!");
  //   }
  // }
}
