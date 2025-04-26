#include <Arduino.h>
#include <Servo.h>

Servo myServo;
const int servoPin = 11;

void setup() {
    myServo.attach(servoPin);
    Serial.begin(9600);
    Serial.println("Servo control ready");
}

void loop() {
    if (Serial.available()) {
        char val = Serial.read();
        if (val >= '1' && val <= '9') {
            int angle = (val - '1') * 20;
            Serial.print("Moving servo to ");
            Serial.println(angle);
            myServo.write(angle);
        }
    }
}