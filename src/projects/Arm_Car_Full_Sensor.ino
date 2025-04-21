
#include <SoftwareSerial.h>
//#include <AccelStepper.h>
#include <Servo.h>
#include <NewPing.h>

#define led A5

/******************SERVO***********************************************************/
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int min1,max1,min2,max2,min3,max3,min4,max4;
int servo1Pos,  servo2Pos,  servo3Pos,  servo4Pos;                   
int servo1PPos, servo2PPos, servo3PPos, servo4PPos;                  
int servo1SP[50], servo2SP[50], servo3SP[50], servo4SP[50];          
int speedDelay = 20;
int index = 0;

/*************************Bluetooth************************************************/
SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
int dataIn;
int m = 0;

// Motor control pins: L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1
const int in2Pin = 5; // Left motor Direction 2
const int in3Pin = 4; // Right motor Direction 1
const int in4Pin = 2; // Right motor Direction 2
const int enBPin = 3; // Right motor PWM speed control

/*************************Define Line Track pins************************************/
//Line Tracking IO define
#define LT_R digitalRead(8)
#define LT_M digitalRead(9) 
#define LT_L digitalRead(10)

#define LECH_L -1
#define LECH_R  1
int     LECH = 0;

/***********************ULtra*********************************/
#define ECHO_PIN 12   // chân ECHO của siêu âm - nối 12 Shield V5.0 
#define TRIG_PIN 13   // chân ECHO của siêu âm - nối 13 Shield V5.0         
#define MAX_DISTANCE 200 
int distance = 100;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo2;                                 //servo gắn cảm biến siêu âm

void line();
void avoiding();
int  readPing();
void stopRobot();
void goAhead(int,int);
void goBack(int,int);
void goLeft(int,int);
void goRight(int,int);

void setup() {
      pinMode(enAPin, OUTPUT);
      pinMode(in1Pin, OUTPUT);
      pinMode(in2Pin, OUTPUT);
      pinMode(in3Pin, OUTPUT);
      pinMode(in4Pin, OUTPUT);
      pinMode(enBPin, OUTPUT);
      
      Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
      Bluetooth.setTimeout(5);
      delay(20);
      
      Serial.begin(9600);
        
      //initARM();
      
      pinMode(LT_R,INPUT);
      pinMode(LT_M,INPUT);
      pinMode(LT_L,INPUT);

      myservo2.attach(11);         //servo gắn cảm biến siêu âm
      myservo2.write(100);         //Góc ban đầu Servo, nếu nó lệch (không thẳng) bạn chỉnh giá trị khác tăng hoặc giảm
      delay(2000);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);
      distance = readPing();
      delay(100);

      pinMode(led, OUTPUT);
      
      servo1.attach(A0);
      servo1PPos = 90;
      min1=0;
      max1=179;
      servo1.write(servo1PPos);
      
      servo2.attach(A1);
      servo2PPos = 110;
      min2=80;
      max2=130;
      servo2.write(servo2PPos);
    
      servo3.attach(A2);
      servo3PPos = 130;
      min3=120;
      max3=180;
      servo3.write(servo3PPos);
    
      servo4.attach(A3);
      servo4PPos = 90;
      min4=70;
      max4=110;
      servo4.write(servo4PPos);

}
void loop() {
          // Check for incoming data
  if (Bluetooth.available() > 0) {
      dataIn = Bluetooth.read();      // Read the data
      Serial.println(dataIn);
          //Move car
      if (dataIn == 0) {stopRobot();}
      if (dataIn == 2) {goAhead(200,200);}
      if (dataIn == 7) {goBack(200,200);}
      if (dataIn == 4) {goLeft(200,200);}
      if (dataIn == 5) {goRight(200,200);}
      if (dataIn == 9)  {goLeft(200,200);}
      if (dataIn == 10) {goRight(200,200);}
              
          //line, ultra
      while (dataIn == 24) {
        line();
        stopRobot();         
      }
      if (dataIn == 26) {
        avoiding();
        stopRobot();
      }
        
          // Move robot arm
      while (dataIn == 22) {        // SERVO1
        servo1PPos--;
        servo1PPos = constrain(servo1PPos, min1, max1);
        servo1.write(servo1PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }     
      while (dataIn == 23) {
        servo1PPos++;
        servo1PPos = constrain(servo1PPos, min1, max1);
        servo1.write(servo1PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 20) {        // SERVO2
        servo2PPos--;
        servo2PPos = constrain(servo2PPos, min2, max2);
        servo2.write(servo2PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 21) {        
        servo2PPos++;
        servo2PPos = constrain(servo2PPos, min2, max2);
        servo2.write(servo2PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 18) {        // SERVO3
        servo3PPos--;
        servo3PPos = constrain(servo3PPos, min3, max3);
        servo3.write(servo3PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 19) {        
        servo3PPos++;
        servo3PPos = constrain(servo3PPos, min3, max3);
        servo3.write(servo3PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 16) {        // SERVO4
        servo4PPos--;
        servo4PPos = constrain(servo4PPos, min4, max4);
        servo4.write(servo4PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
      while (dataIn == 17) {        // SERVO4
        servo4PPos++;
        servo4PPos = constrain(servo4PPos, min4, max4);
        servo4.write(servo4PPos);
        delay(speedDelay);
        if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
        }
      }
    
  }              //END IF BLUETOOTH

}

void goAhead(int speedcar1, int speedcar2){ 

      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedcar1);
      analogWrite(enBPin, speedcar2);

  }

void goBack(int speedcar1, int speedcar2){ 
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);         // RIGHT lui
      analogWrite(enAPin, speedcar1);
      analogWrite(enBPin, speedcar2);
  }

void goRight(int speedcar1, int speedcar2){ 
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,HIGH);         // LEFT tien
      digitalWrite(in3Pin,HIGH);      
      digitalWrite(in4Pin,LOW);          // RIGHT lui
      analogWrite(enAPin, speedcar1);
      analogWrite(enBPin, speedcar2);

  }

void goLeft(int speedcar1, int speedcar2){
      digitalWrite(in1Pin,HIGH);      
      digitalWrite(in2Pin,LOW);         // LEFT lui
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,HIGH);         // RIGHT tien
      analogWrite(enAPin, speedcar1);
      analogWrite(enBPin, speedcar2);
      
  }

void stopRobot(){  
      digitalWrite(in1Pin,LOW);      
      digitalWrite(in2Pin,LOW);      
      digitalWrite(in3Pin,LOW);      
      digitalWrite(in4Pin,LOW);         
      analogWrite(enAPin, 0);
      analogWrite(enBPin, 0);  
}

void line(){
  do{
          if(LT_M){
              goAhead(150,150);
          }
          else if(LT_R) {
              LECH = LECH_R;
              goRight(150,150);
              while(LT_R);                             
          }   
          else if(LT_L) {
              LECH = LECH_L;
              goLeft(150,150);
              while(LT_L);  
          } 
          else if (LECH == LECH_R){
              goRight(100,100);
          } 
          else if (LECH == LECH_L){
              goLeft(100,100);
          } 
          
          if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.read();
          }  
   }while(dataIn !=25);
}

void avoiding()
{
    long duration, distance;
    int distanceR = 0;
    int distanceL =  0;
    do{ 
       distance = readPing();
       delay(40);
       if(distance<=30)
       {
            stopRobot();
            delay(100);
            distanceR = lookRight();
            delay(200);
            distanceL = lookLeft();
            delay(200);
            if(distanceR>=distanceL)
            {
              goRight(200,200);
              delay(500);
              stopRobot();
              delay(100);
            }else{
              goLeft(200,200);
              delay(500);
              stopRobot();
              delay(100);
            }
       }else{
          goAhead(200,200);
       } 
        
       if (Bluetooth.available() > 0) {
          dataIn = Bluetooth.read();
       }  
   }while(dataIn != 27);
}
int lookRight()
{
    myservo2.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo2.write(100);               //cái này chỉnh cho thẳng
    return distance;
}
int lookLeft()
{
    myservo2.write(150); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo2.write(100);             //cái này chỉnh cho thẳng
    return distance;
    delay(100);
}
int readPing() { 
    delay(70);
    int cm = sonar.ping_cm();
    if(cm==0)
    {
      cm = 250;
    }
    return cm;
}

 
