#include <Arduino.h>

const int SensorLeft = 10;
const int SensorMiddle = 9;
const int SensorRight = 8;

int SL, SM, SR;
unsigned char old_SL, old_SM, old_SR;

void setup() {
      pinMode(SensorLeft, INPUT);
      pinMode(SensorMiddle, INPUT);
      pinMode(SensorRight, INPUT);
}

void loop() {
      SL = digitalRead(SensorLeft);
      SM = digitalRead(SensorMiddle);
      SR = digitalRead(SensorRight);

      if (old_SL != SL || old_SM != SM || old_SR != SR) {
            old_SL = SL;
            old_SM = SM;
            old_SR = SR;
      }
}