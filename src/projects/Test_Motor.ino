const int enAPin = 6, in1Pin = 7, in2Pin = 5, in3Pin = 4, in4Pin = 2, enBPin = 3;

void setup() {
    pinMode(enAPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(in3Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);
    pinMode(enBPin, OUTPUT);
}

void loop() {
    goAhead(160, 160); delay(3000);
    goBack(160, 160); delay(3000);
    turnRight(160, 160); delay(3000);
    turnLeft(160, 160); delay(3000);
}

void goAhead(int speedCar, int speedCar2) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, HIGH);
    analogWrite(enAPin, speedCar);
    analogWrite(enBPin, speedCar2);
}

void goBack(int speedCar, int speedCar2) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    analogWrite(enAPin, speedCar);
    analogWrite(enBPin, speedCar2);
}

void turnRight(int speedCar, int speedCar2) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    analogWrite(enAPin, speedCar);
    analogWrite(enBPin, speedCar2);
}

void turnLeft(int speedCar, int speedCar2) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, HIGH);
    analogWrite(enAPin, speedCar);
    analogWrite(enBPin, speedCar2);
}

void stopRobot() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
    analogWrite(enAPin, 0);
    analogWrite(enBPin, 0);
}