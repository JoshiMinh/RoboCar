#include <Arduino.h>

// Motor control pins
const int enAPin = 6, in1Pin = 7, in2Pin = 5;
const int enBPin = 3, in3Pin = 4, in4Pin = 2;

// IR sensor pins
const int farLeftIR = 8, leftIR = 9, centerIR = 10, rightIR = 11, farRightIR = 12;

void setup() {
  // Configure motor pins as outputs
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // Configure IR sensor pins as inputs
  pinMode(farLeftIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(centerIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(farRightIR, INPUT);

  // Stop motors initially
  stopMotors();
}

void loop() {
  // Read IR sensor states
  bool farLeft = digitalRead(farLeftIR);
  bool left = digitalRead(leftIR);
  bool center = digitalRead(centerIR);
  bool right = digitalRead(rightIR);
  bool farRight = digitalRead(farRightIR);

  // Stop if all sensors detect the line
  if (!farLeft && !left && !center && !right && !farRight) {
    stopMotors();
    return;
  }

  // Move forward if any sensor detects the line
  if (farLeft || left || center || right || farRight) {
    moveForward();
  } 
  // Spin in place if no sensor detects the line
  else {
    spinInPlace();
  }
}

void moveForward() {
  // Drive both motors forward
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enAPin, 200); // Adjust speed

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enBPin, 200);
}

void spinInPlace() {
  // Left motor backward, right motor forward
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enAPin, 180);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enBPin, 180);
}

void stopMotors() {
  // Stop both motors
  analogWrite(enAPin, 0);
  analogWrite(enBPin, 0);
}