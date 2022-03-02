//#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "kafre";
const char* password = "12345678";
//Wi-Fi
WiFiUDP Udp;
IPAddress apIP(192,168,1,10);
unsigned int localUdpPort = 80;  // local port to listen on
char incomingPacket[5];  // buffer for incoming packets
char  Time[27];  
char  Acc[30];
char  Gyro[31];
char  angle[49];
char  Mag[30];
char  Longitude[21];
char  Lattitude[21];
char  gpsHeight[57];
char  SN[50];
char  bat[21];

char con[] = "con_1";

bool connected_bool = false;

void setup() 
{
  //Настройка и запуск Wi-Fi
Serial.begin(74880);
Serial.printf("Connecting to %s ", ssid);
WiFi.begin(ssid, password);delay(7000);
if (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.println("Not connected");
}
  else 
{
  Serial.println(" connected");
  delay(1000);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  Serial.println(apIP);
  
  Udp.beginPacket(apIP, 80);
  Udp.write(con);  
  Udp.endPacket();
   
  connected_bool = true;
}
}

void loop() 
{
if (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.println("Not connected");
  connected_bool = false;
}
 else 
{
  if (!connected_bool)
  {
  Serial.println(" connected");
  delay(1000);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  Serial.println(apIP);

  Udp.beginPacket(apIP, 80);
  Udp.write(con);  
  Udp.endPacket();
  connected_bool = true;
  }
    while(Serial.available()>0)
   {
     String data = Serial.readStringUntil('\n');
   if (data.startsWith("Time"))
   {
    //data=data.substring(27);
    data.toCharArray(Time,27);
    Udp.beginPacket(apIP, 80);
    Udp.write(Time);  
    Udp.endPacket();
   }
   else if (data.startsWith("Acc"))
   {
    //data=data.substring(30);
    data.toCharArray(Acc,30);
    Udp.beginPacket(apIP, 80);
    Udp.write(Acc);  
    Udp.endPacket();
   }
   else if (data.startsWith("Gyro"))
   {
   // data=data.substring(31);
    data.toCharArray(Gyro,31);
    Udp.beginPacket(apIP, 80);
    Udp.write(Gyro);  
    Udp.endPacket();
   }
   else if (data.startsWith("Angle"))
   {
    //data=data.substring(49);
    data.toCharArray(angle,49);
    Udp.beginPacket(apIP, 80);
    Udp.write(angle);  
    Udp.endPacket();
   }
   else if (data.startsWith("Mag"))
   {
    //data=data.substring(30);
    data.toCharArray(Mag,30);
    Udp.beginPacket(apIP, 80);
    Udp.write(Mag);  
    Udp.endPacket();
   }
   else if (data.startsWith("Longitude"))
   {
    //data=data.substring(21);
    data.toCharArray(Longitude,21);
    Udp.beginPacket(apIP, 80);
    Udp.write(Longitude);  
    Udp.endPacket();
   }
   else if (data.startsWith("Lattitude"))
   {
    //data=data.substring(21);
    data.toCharArray(Lattitude,21);
    Udp.beginPacket(apIP, 80);
    Udp.write(Lattitude);  
    Udp.endPacket();
   }
   else if (data.startsWith("GPSHeight"))
   {
    //data=data.substring(57);
    data.toCharArray(gpsHeight,57);
    Udp.beginPacket(apIP, 80);
    Udp.write(gpsHeight);  
    Udp.endPacket();
   }
   else if (data.startsWith("SN"))
   {
    //data=data.substring(50);
    data.toCharArray(SN,50);
    Udp.beginPacket(apIP, 80);
    Udp.write(SN);  
    Udp.endPacket();
   }
    else if (data.startsWith("B1"))
   {
    data.toCharArray(bat,21);
    Udp.beginPacket(apIP, 80);
    Udp.write(bat);  
    Udp.endPacket();
   }
}
}
}
