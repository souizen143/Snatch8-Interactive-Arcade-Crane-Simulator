Snatch8: Interactive Arcade Crane Simulator 
Overview

This project is an Arduino-based arcade crane simulator that integrates multiple sensors and actuators to replicate a real-world claw machine.

The system uses:

RFID to start the game

Joystick to control movement

Servo motors to simulate crane motion

Ultrasonic sensor to detect prize proximity

Active buzzer for audio feedback

Features

Real-time joystick control for crane movement
RFID-based game activation system
Ultrasonic-based prize detection
Audio feedback using active buzzer
Smooth servo motor operation
Embedded system logic using Arduino Uno

Components Used
Component	Quantity
Arduino Uno	1
Servo Motors	2
Joystick Module	1
RFID Module (MFRC522)	1
RFID Card/Tag	1
Ultrasonic Sensor (HC-SR04)	1
Active Buzzer	1
Breadboard	1
Jumper Wires	Many
Power Supply	5V

Wiring Connections
RFID Module (MFRC522)
Pin	Arduino
SDA	D10
SCK	D13
MOSI	D11
MISO	D12
RST	D9
GND	GND
3.3V	3.3V

Ultrasonic Sensor (HC-SR04)
Pin	Arduino
VCC	5V
GND	GND
TRIG	D3
ECHO	D2

Joystick Module
Pin	Arduino
VRx	A0
VRy	A1
GND	GND
VCC	5V

Servo Motors
Servo	Arduino
Servo 1	D7
Servo 2	D6
VCC	5V
GND	GND

Active Buzzer
Pin	Arduino
VCC (+)	D4
GND (-)	GND

System Workflow

User scans RFID card
System activates the game
Player controls crane using joystick
Ultrasonic sensor detects object distance
If object is detected:
Buzzer alerts
Servo simulates grabbing motion
Game continues or resets

💻 Arduino Code

Upload using Arduino IDE with required libraries:
Servo.h
SPI.h
MFRC522.h

#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define TRIG 3
#define ECHO 2

#define BUZZER 4

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

// Beep Beep (win sound)
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
Required Libraries

Install via Arduino IDE Library Manager:

MFRC522 (by Miguel Balboa)

Important Notes

RFID module uses 3.3V ONLY
Use external power supply if servos jitter
Adjust detection range in code (distance < 10)
Active buzzer works with simple HIGH/LOW signals
Future Improvements
Add countdown timer system
Integrate LCD display
Credit/coin system
Fully automated crane mechanism
Score tracking system

Authors

Lexus H. Mabansag
Jordan David B. Belgica
John Kenneth Gavilan

License

This project is for educational and academic purposes.

Project Status
Finished 

✅ Completed (Prototype)
🔄 Open for improvement
