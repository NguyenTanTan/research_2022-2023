#include <AccelStepper.h>
#include <Servo.h> 
// const int stepPin = 7;
// const int dirPin = 2;
// const int enPin = 8;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

AccelStepper stepper(1, stepPin, dirPin);
int stopCondition = 0;
String input="N";
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
   // thiet lap servo
  myservo1.attach(6);
  myservo2.attach(5);
  myservo3.attach(4);
  myservo4.attach(3);
  myservo5.attach(2);
  myservo6.attach(7); 
  // home 
  myservo1.write(130); // 130: vào vị trí gắp vật, 40: thả.
  myservo2.write(130); // 80:...
  myservo3.write(120); // 90: ..
  myservo4.write(180); // 150
  myservo5.write(160); // 160:...
  myservo6.write(50);  // 70: kẹp, 0: mở
}

void loop() {
  if (Serial2.available()>0) {
    String input = Serial2.readStringUntil('\n');
    Serial.println(input);
    input.trim();
    if (input.equals("Y")) {
      stopCondition = 1;
    } else {
      stopCondition = 0;
    }
  }
  if (stopCondition == 1){
      // từ vị trí ban đầu chuyển sang gắp vật
    delay(500);
    for (int i = 180; i>=150; i=i-10){myservo4.write(i);delay(100); };
    delay(500);
    for (int i = 120; i>=90; i=i-10){myservo3.write(i); delay(100);};
    delay(1000);
    myservo6.write(0);
    delay(500);
    for (int i = 130; i>=80; i=i-5){myservo2.write(i); delay(100);};
    delay(1000);
    myservo6.write(50);
    delay(500);

    // thả vật vào thùng
    for (int i = 80; i<=100; i=i+10){myservo2.write(i); delay(100);};
    for (int i = 130; i>=40; i=i-10){myservo1.write(i);delay(100);};
    delay(500);
    myservo6.write(0);
    delay(500);
    myservo6.write(50);
    delay(500);
    // về vị trí chuẩn bị
    for (int i = 100; i<=130; i=i+10){myservo2.write(i); delay(100);};
    delay(500);
    for (int i = 90; i<=120; i=i+10){myservo3.write(i); delay(100);};
    delay(500);
    for (int i = 150; i<=180; i=i+10){myservo4.write(i);delay(100); };
    delay(500);
    for (int i = 40; i<=130; i=i+10){myservo1.write(i);delay(100);};
    //gửi thông báo cho esp
    delay(200);
    Serial2.println("C");
    stopCondition = 0;
    input= "N";

    
  }
  if (stopCondition == 0) {
    digitalWrite(dirPin, LOW);
    for(int x = 0; x < 3200; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }
  
}
