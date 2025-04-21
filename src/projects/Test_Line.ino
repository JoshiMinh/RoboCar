
/*****************************/
//WWW.LINHKIENTOT.VN
// Test chức năng BLUETOOTH
/*****************************/

#include <LiquidCrystal_I2C.h>    //Include the I2C protocol LCD1602 Lib
#include <Wire.h>                 // Include I2C Lib
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27,16,2); // Define LCD1602

/*************************Define Line Track pins************************************/
const int SensorLeft   = 10;      //Left sensor input (A1)
const int SensorMiddle = 9;       //Midd sensor input (A2)
const int SensorRight  = 8;       //Right sensor input(A3)
int SL;    //Status of Left line track sensor
int SM;    //Status of Midd line track sensor
int SR;    //Status of Righ line track sensor

unsigned char old_SL,old_SM,old_SR;     //trang thai truoc cua cam bien do line

void setup()
{
      lcd.begin();
      delay(10); 
      lcd.backlight();
      lcd.clear(); 
      lcd.backlight();
      lcd.clear();
      
      pinMode(SensorLeft,INPUT); 
      pinMode(SensorMiddle,INPUT);
      pinMode(SensorRight,INPUT);
}
void loop()
{
      SL = digitalRead(SensorLeft);
      SM = digitalRead(SensorMiddle);
      SR = digitalRead(SensorRight);
      if(old_SL!=SL||old_SM!=SM||old_SR!=SR)     //nếu trạng thái dò line có thay đổi, sẽ được cập nhật lên LCD
      {
        old_SL = SL;
        old_SM = SM;
        old_SR = SR;
        lcd.setCursor(0, 0); 
        lcd.print("SL="); 
        lcd.print(old_SL,DEC); 
        lcd.print(" SM =");
        lcd.print(old_SM,DEC);
        lcd.print(" SR =");
        lcd.print(old_SR,DEC);
      }
}
