#include <Arduino.h>

const int enAPin = 6, in1Pin = 7, in2Pin = 5;
const int enBPin = 3, in3Pin = 4, in4Pin = 2;

const int farLeftIR = 8, leftIR = 9, centerIR = 10, rightIR = 11, farRightIR = 12;

const int forwardPower = 80, turnPower = 100;

enum LastDirection { LEFT, RIGHT };
LastDirection lastDirection = RIGHT;

void setup() {
    pinMode(enAPin, OUTPUT); pinMode(in1Pin, OUTPUT); pinMode(in2Pin, OUTPUT);
    pinMode(enBPin, OUTPUT); pinMode(in3Pin, OUTPUT); pinMode(in4Pin, OUTPUT);
    pinMode(farLeftIR, INPUT); pinMode(leftIR, INPUT); pinMode(centerIR, INPUT);
    pinMode(rightIR, INPUT); pinMode(farRightIR, INPUT);
    stopMotors();
}

void loop() {
    bool farLeft = !digitalRead(farLeftIR);
    bool left = !digitalRead(leftIR);
    bool center = !digitalRead(centerIR);
    bool right = !digitalRead(rightIR);
    bool farRight = !digitalRead(farRightIR);

    if (farLeft && left && center && right && farRight) {
        stopMotors();
        delay(1000);
    } else if (!farLeft && !left && !center && !right && !farRight) {
        smartSpin(lastDirection);
    } else if (farLeft || left) {
        lastDirection = RIGHT;
        smartSpin(RIGHT);
    } else if (farRight || right) {
        lastDirection = LEFT;
        smartSpin(LEFT);
    } else if (center) {
        moveForward(forwardPower);
    }
}

void moveForward(int power) {
    digitalWrite(in1Pin, HIGH); digitalWrite(in2Pin, LOW); analogWrite(enAPin, power);
    digitalWrite(in3Pin, HIGH); digitalWrite(in4Pin, LOW); analogWrite(enBPin, power);
}

void smartSpin(LastDirection direction) {
    if (direction == LEFT) {
        digitalWrite(in1Pin, LOW); digitalWrite(in2Pin, HIGH); analogWrite(enAPin, turnPower);
        digitalWrite(in3Pin, HIGH); digitalWrite(in4Pin, LOW); analogWrite(enBPin, turnPower);
    } else {
        digitalWrite(in1Pin, HIGH); digitalWrite(in2Pin, LOW); analogWrite(enAPin, turnPower);
        digitalWrite(in3Pin, LOW); digitalWrite(in4Pin, HIGH); analogWrite(enBPin, turnPower);
    }
}

void stopMotors() {
    analogWrite(enAPin, 0);
    analogWrite(enBPin, 0);
}