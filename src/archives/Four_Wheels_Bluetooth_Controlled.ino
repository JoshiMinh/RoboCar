#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

const int enAPin = 6, in1Pin = 7, in2Pin = 5, in3Pin = 4, in4Pin = 2, enBPin = 3;

void setup() {
    pinMode(enAPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(in3Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);
    pinMode(enBPin, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(9600);
}

void loop() {
    if (Serial.available()) processCommand(Serial.read());
    if (BTSerial.available()) processCommand(BTSerial.read());
}

void processCommand(char command) {
    int speed = 255;
    switch (command) {
        case 'F': moveMotors(HIGH, LOW, HIGH, LOW, speed); break;
        case 'B': moveMotors(LOW, HIGH, LOW, HIGH, speed); break;
        case 'L': moveMotors(LOW, HIGH, HIGH, LOW, speed); break;
        case 'R': moveMotors(HIGH, LOW, LOW, HIGH, speed); break;
        case 'S': stopMotors(); break;
    }
}

void moveMotors(int in1, int in2, int in3, int in4, int speed) {
    digitalWrite(in1Pin, in1);
    digitalWrite(in2Pin, in2);
    digitalWrite(in3Pin, in3);
    digitalWrite(in4Pin, in4);
    analogWrite(enAPin, speed);
    analogWrite(enBPin, speed);
}

void stopMotors() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
    analogWrite(enAPin, 0);
    analogWrite(enBPin, 0);
}