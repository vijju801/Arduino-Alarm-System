#include <LiquidCrystal.h>

// Define ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Define LED pins
const int redLedPin = 7;
const int greenLedPin = 6;

// Define buzzer pin
const int buzzerPin = 8;

// Define LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pins Connected with Controller

// Define threshold distance for intrusion detection
const int intrusionThreshold = 20; // 20 cm distance set

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LED pins
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2); // LCD Display

  // Display initial message on LCD
  lcd.print("Intruder Alarm System");
  lcd.setCursor(0, 1);
  lcd.print("System is Ready to Use");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Trigger ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time taken for the pulse to return
  long duration = pulseIn(echoPin, HIGH);

  // Convert the time to distance (cm)
  int distance = duration * 0.034 / 2;

  // Display the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an intruder is detected
  if (distance < intrusionThreshold) {
    // Intruder detected, activate alarm
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    tone(buzzerPin, 1000); // Alarm from the buzzer
    lcd.clear();
    lcd.print("Intruder Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
  } else {
    // No intruder, system is in standby
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    noTone(buzzerPin); // Stop the tone on the buzzer
    lcd.clear();
    lcd.print("No one is There!");
  }

  // Delay before the next sensor reading
  delay(3000);
}
