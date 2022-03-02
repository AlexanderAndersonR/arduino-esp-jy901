
//ACS
#include <Wire.h>
//#include <JY901.h>
#include "JY901_Serial.h"
//ACS

#include <SD.h> //sd

//disp
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
//#include <SPFD5408_TouchScreen.h>
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//disp

#define VREF 5.0      // точное напряжение на пине 5V (в данном случае зависит от стабилизатора на плате Arduino)
#define DIV_R1 1000  // точное значение 10 кОм резистора
#define DIV_R2 1000   // точное значение 4.7 кОм резистора


// pin for sd
int CS_pin = 53;
float refresh_rate = 5000.0;
// pin for sd
bool flag = false;
void setup()
{
  //for sd
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(74880);
  JY901.attach(Serial1);
  //Serial.println("Initializing Card");
  pinMode(CS_pin, OUTPUT);
  
  if (!SD.begin(CS_pin)) 
  {
      Serial.println("Card Failure");
      return;
  }
//  Serial.println("Card Ready");
  //for sd
pinMode(31, INPUT_PULLUP);
pinMode(39, INPUT_PULLUP);
pinMode(A9, OUTPUT);
//open fail and write string
//if no fail - it's will be created
//analogWrite(A9, 1023);
}

void loop() 
{
  float voltage_b1 = (float)(analogRead(8) * VREF) / 1024;
  float voltage_b2 = ((float)analogRead(7) * VREF * ((DIV_R1 + DIV_R2) / DIV_R2) / 1024) - voltage_b1;

  //Serial2.println("X = 111");
  if(voltage_b1<3|| voltage_b2<3)
  {
  analogWrite(A9, 1023);
  }
  else
  {
  analogWrite(A9, 0);
  }
  while (Serial1.available()) 
  {
    JY901.receiveSerialData(); //Call JY901 data cope function
  }
  File logFile = SD.open("LOG_1.txt", FILE_WRITE);
  if (logFile) 
 {
  
  Serial.println((String)"B1: " + (String)voltage_b1 + (String)" B2: " + (String)voltage_b2);
  Serial2.println((String)"B1_1:" + (String)voltage_b1 + (String)" B2_1:" + (String)voltage_b2);
  
  String string_time = String(JY901.getTime("year")) + "-" + String(JY901.getTime("month")) + "-" + String(JY901.getTime("day")) + " " + String(JY901.getTime("hour")) + ":" + String(JY901.getTime("minute")) + ":" + String((float)JY901.getTime("second"));
  Serial.println("Time:" + string_time); 
  Serial2.println("Time_1:" + string_time);
  
  String string_Acc = String(JY901.getAccX()) + " " + String(JY901.getAccY()) + " " + String(JY901.getAccZ());     
  Serial.println("Acc:" + string_Acc);
  Serial2.println("Acc_1:" + string_Acc);
  
  String string_Gyro = String(JY901.getGyroX()) + " " + String(JY901.getGyroY()) + " " + String(JY901.getGyroZ());
  Serial.println("Gyro:" + string_Gyro);
  Serial2.println("Gyro_1:" + string_Gyro);
  
  String string_Angle = " Roll_1 " + String(JY901.getRoll()) + " Pitch_1 " + String(JY901.getPitch()) + " Yaw_1 " + String(JY901.getYaw());
  Serial.println("Angle:" + string_Angle);
  Serial2.println("Angle_1:" + string_Angle);
  
  String string_Mag = String(JY901.getMagX()) + " " + String(JY901.getMagY()) + " " + String(JY901.getMagZ());
  Serial.println("Mag:" + string_Mag);
  Serial2.println("Mag_1:" + string_Mag);
//String string_DStatus = String(JY901.getD0Status()) + " " + String(JY901.getD1Status()) + " " + String(JY901.getD2Status()) + " " + String(JY901.getD3Status());
//Serial.println("DStatus:" + string_DStatus);
  
//String string_Longitude = String(JY901.getLon() / 10000000) + "Deg " + String((double)(JY901.getLon() % 10000000) / 1e5) + "m"; 
//Serial.println("Longitude:" + string_Longitude);
///
  String string_Longitude2 = String(JY901.getLon()); 
  Serial.println("Longitude:" + string_Longitude2);
  Serial2.println("Longitude_1:" + string_Longitude2);
///
//String string_Lattitude = String(JY901.getLat() / 10000000) + "Deg " + String((double)(JY901.getLat() % 10000000) / 1e5) + "m";
//Serial.println("Lattitude:" + string_Lattitude);
///
  String string_Lattitude2 = String(JY901.getLat());
  Serial.println("Lattitude:" + string_Lattitude2);
  Serial2.println("Lattitude_1:" + string_Lattitude2);
///
  String string_GPSHeight = String(JY901.getGPSH()) + " GPSYaw_1:" + String(JY901.getGPSY()) + " GPSV_1:" + String(JY901.getGPSV()) + "km/h";
  Serial.println("GPSHeight: " +string_GPSHeight);
  Serial2.println("GPSHeight_1: " +string_GPSHeight);
  
  String string_dop = String(JY901.getDOP("sn")) + " PDOP" + String(JY901.getDOP("pdop")) + " HDOP" + String(JY901.getDOP("hdop")) + " VDOP" + String(JY901.getDOP("vdop"));
  Serial.println("SN:" + string_dop + "\n");
  Serial2.println("SN_1:" + string_dop);
  
    logFile.println("Time:" + string_time);
    logFile.println("Acc:" + string_Acc);
    logFile.println("Gyro:" + string_Gyro);
    logFile.println("Angle:" + string_Angle);
    logFile.println("Mag:" + string_Mag);
    //logFile.println("Longitude:" + string_Longitude);
    //logFile.println("Lattitude:" + string_Lattitude);
    logFile.println("Longitude:" + string_Longitude2);
    logFile.println("Lattitude:" + string_Lattitude2);
    logFile.println("GPSHeight: " +string_GPSHeight);
    logFile.println("SN:" + string_dop);
    logFile.println((String)"B1: " + (String)voltage_b1 + (String)" B2: " + (String)voltage_b2 + "\n");
    logFile.close();
    
    if(digitalRead(39) && !flag)
    {
      tft.begin(0x9341);
    //tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(GREEN);
    //tft.println(1000);
    tft.setRotation(3);
      flag = true;
    }
    
    if (!digitalRead(39) && flag) 
    {  // обработчик отпускания
    flag = false;  
    }
    
    bool btnState = !digitalRead(31);
  if (btnState && flag) 
  {  
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.print("Time " + String(JY901.getTime("day")) + "/" + String(JY901.getTime("month")) + " " +  String(JY901.getTime("hour")) + ":" + String(JY901.getTime("minute")) + ":" + String((float)JY901.getTime("second")));
    tft.setCursor(0, 20);
    tft.print("Lon " + string_Longitude2);
    tft.setCursor(0, 40);
    tft.print("Lat " + string_Lattitude2);
    tft.setCursor(0, 60);
    tft.print("AC: " + string_Acc);
    tft.setCursor(0, 80);
    tft.print("GY: " + string_Gyro);
    tft.setCursor(0, 100);
    tft.print("AN: " + string_Angle);
    tft.setCursor(0, 140);
    tft.print("GPSHeight: " +string_GPSHeight);
    tft.setCursor(0, 180);
    tft.print("SN:" +string_dop);
    tft.setCursor(0, 220);
    tft.print((String)"B1: " + (String)voltage_b1 + (String)" B2: " + (String)voltage_b2);
  }  
  
 //delay(500);
}
  else 
  {
    Serial.println((String)"B1: " + (String)voltage_b1 + (String)" B2: " + (String)voltage_b2);
    Serial2.println((String)"B1_1:" + (String)voltage_b1 + (String)" B2_1:" + (String)voltage_b2);
    
    Serial.println("Couldn't open log file");
    Serial2.println("SD_1_ERROR");
    if(digitalRead(39) && !flag)
    {
      tft.begin(0x9341);
    //tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(GREEN);
    //tft.println(1000);
    tft.setRotation(3);
      flag = true;
    }
    
    if (!digitalRead(39) && flag) 
    {  // обработчик отпускания
    flag = false;  
    }
    
    bool btnState = !digitalRead(31);
    if (btnState && flag) 
  { 
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.print("Couldn't open log file");
    SD.begin(CS_pin);
  }
  }
}
