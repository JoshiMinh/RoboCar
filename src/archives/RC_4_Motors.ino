#include <Arduino.h>
const int enAPin = 6, in1Pin = 7, in2Pin = 5, in3Pin = 4, in4Pin = 2, enBPin = 3;
const int ch1Pin = A0, ch2Pin = A1;

void setup() {
    pinMode(enAPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(in3Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);
    pinMode(enBPin, OUTPUT);
    pinMode(ch1Pin, INPUT);
    pinMode(ch2Pin, INPUT);
}

void loop() {
    int throttle = pulseIn(ch2Pin, HIGH, 25000);
    int steering = pulseIn(ch1Pin, HIGH, 25000);

    if (throttle < 1000 || throttle > 2000 || steering < 1000 || steering > 2000) {
        stopMotors();
        return;
    }

    int speed = map(throttle, 1000, 2000, -255, 255);
    int turn = map(steering, 1000, 2000, -255, 255);

    int leftSpeed = constrain(speed + turn, -255, 255);
    int rightSpeed = constrain(speed - turn, -255, 255);

    setMotor(enAPin, in1Pin, in2Pin, leftSpeed);
    setMotor(enBPin, in3Pin, in4Pin, rightSpeed);
}

void setMotor(int enPin, int in1, int in2, int motorSpeed) {
    if (motorSpeed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (motorSpeed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        motorSpeed = -motorSpeed;
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
    analogWrite(enPin, motorSpeed);
}

void stopMotors() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
    analogWrite(enAPin, 0);
    analogWrite(enBPin, 0);
}