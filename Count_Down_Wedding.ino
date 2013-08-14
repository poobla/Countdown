#include <Wire.h>
#include <stdint.h>
#include <TFT.h>
 
void setup()
{
  Tft.init();//init TFT
  Wire.begin();
  Serial.begin(9600);
  Tft.drawString("Days",2,140,8,PURPLE);
  Tft.drawString("Left",2,240,8,PURPLE);
}
 
void loop()
{
  char daysLeft[2];
  int dayCount = 0;
  int lastDayCount;
  // send request to receive data starting at register 0
  Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
  Wire.write((byte)0); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7); // request three bytes (seconds, minutes, hours)
 
  while(Wire.available())
  { 
    int sec_count = Wire.read(); // get seconds
    int min_count = Wire.read(); // get minutes
    int hr_count = Wire.read();   // get hours
    int weekday = Wire.read();    //day of week, monday-sunday
    char weekday_name;
    int days = Wire.read();    //get days
    int months = Wire.read();  //get months
    int years = Wire.read();  //get year
 

    days = (((days & 0b11110000)>>4)*10 + (days & 0b00001111));  //convert BCD

    dayCount = 31-days;
    itoa(dayCount, daysLeft,10);
    Tft.drawString(daysLeft,17,15,14,PURPLE);
  }
 
  delay(120000);
  Tft.drawString(daysLeft,17,15,14,BLACK);
}
