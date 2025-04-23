#include <Arduino.h>

const int enAPin = 6, in1Pin = 7, in2Pin = 5;
const int enBPin = 3, in3Pin = 4, in4Pin = 2;

const int farLeftIR = 8, leftIR = 9, centerIR = 10, rightIR = 11, farRightIR = 12;

void setup() {
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(farLeftIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(centerIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(farRightIR, INPUT);

  stopMotors();
}

void loop() {
  bool farLeft = digitalRead(farLeftIR);
  bool left = digitalRead(leftIR);
  bool center = digitalRead(centerIR);
  bool right = digitalRead(rightIR);
  bool farRight = digitalRead(farRightIR);

  // Line undetected
  if (!farLeft && !left && !center && !right && !farRight) {
    spinInPlace();
    return;
  }

  // All 5 IR sensors detect the line
  else if (farLeft && left && center && right && farRight) {
    stopMotors();
    return;
  }

  // Smart turning logic
  else if (farLeft || left) {
    turnLeft();
    return;
  } else if (farRight || right) {
    turnRight();
    return;
  }

  // Move forward if the center sensor detects the line
  else if (center) {
    moveForward();
    return;
  }

  // Default to stopping motors
  else {
    stopMotors();
  }
}

void turnLeft() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enAPin, 150);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enBPin, 150);
}

void turnRight() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enAPin, 150);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enBPin, 150);
}

void moveForward() {
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enAPin, 200);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enBPin, 200);
}

void spinInPlace() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enAPin, 180);

  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enBPin, 180);
}

void stopMotors() {
  analogWrite(enAPin, 0);
  analogWrite(enBPin, 0);
}