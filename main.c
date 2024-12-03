#include <ESP8266WiFi.h>
#include <Servo.h>

// Pin definitions
const int TRIG_PIN = D1;
const int ECHO_PIN = D2;
const int SERVO_PIN = D3;

// Constants
const int DISTANCE_THRESHOLD = 20; // Distance in cm to trigger gate
const int GATE_OPEN_ANGLE = 90;
const int GATE_CLOSED_ANGLE = 0;
const int GATE_DELAY = 5000; // Time to keep gate open in milliseconds

Servo gateServo;
long duration;
int distance;

void setup() {
  Serial.begin(115200);
  
  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo
  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSED_ANGLE); // Start with gate closed
  
  Serial.println("Toll Gate System Ready!");
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Check if vehicle is detected
  if (distance < DISTANCE_THRESHOLD) {
    Serial.println("Vehicle detected! Opening gate...");
    gateServo.write(GATE_OPEN_ANGLE);
    delay(GATE_DELAY);
    
    Serial.println("Closing gate...");
    gateServo.write(GATE_CLOSED_ANGLE);
  }
  
  delay(100); // Small delay to prevent too frequent readings
}
