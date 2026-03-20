#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Ultrasonic
#define TRIG 3
#define ECHO 2

// Buzzer
#define BUZZER 4

// Servos
Servo servo1;
Servo servo2;

int eje1 = 90;
int eje2 = 90;

bool gameStarted = false;

void setup() {
  Serial.begin(9600);

  // Servo
  servo1.attach(7);
  servo2.attach(6);

  servo1.write(90);
  servo2.write(90);

  // RFID
  SPI.begin();
  mfrc522.PCD_Init();

  // Ultrasonic
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Serial.println("Scan RFID to start...");
}

void loop() {

  // ================= RFID START =================
  if (!gameStarted) {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    Serial.println("Game Started!");
    gameStarted = true;

    // 🔊 Start sound
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);

    delay(1000);
  }

  // ================= JOYSTICK =================
  if (analogRead(A0) < 200 && eje1 < 180) {
    eje1++;
    servo1.write(eje1);
  }
  if (analogRead(A0) > 700 && eje1 > 0) {
    eje1--;
    servo1.write(eje1);
  }

  if (analogRead(A1) < 200 && eje2 < 180) {
    eje2++;
    servo2.write(eje2);
  }
  if (analogRead(A1) > 700 && eje2 > 0) {
    eje2--;
    servo2.write(eje2);
  }

  // ================= ULTRASONIC =================
  long duration;
  int distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // ================= PRIZE DETECT =================
  if (distance > 0 && distance < 10) {
    Serial.println("Prize Detected!");

    // 🔊 Beep Beep (win sound)
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER, HIGH);
      delay(150);
      digitalWrite(BUZZER, LOW);
      delay(150);
    }















    // Simulate grab
    servo2.write(120);
    delay(1000);
  }

  delay(15);
}