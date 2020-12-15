#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define apikey "lJOULFScfN5Xvn2Df4Lg4t3G9Pc= "
#define deviceid 657054151
#define dsName "longitude"
#define dsName2 "latitude"
#define LINEBREAK "\r\n"
char server[]="api.heclouds.com";
double latitude;
double longitude;


TinyGPSPlus gps;
SoftwareSerial ss(4, 3);
SoftwareSerial mySerial(10, 11);

void updateSerial()
{
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) {
    Serial.write(mySerial.read());
  }
    if(mySerial.available()) 
    {
      Serial.write(mySerial.read());
    }
    if(Serial.available())    
    {
     mySerial.write(Serial.read());
    }   
}
void sendlocation()
{
  mySerial.println("AT+CIPSTATUS ");//查询状态
  updateSerial();
  delay(100);
  mySerial.println("AT+CGATT?");// 查询模块是否附着网络返回 1则表示附着成功
  updateSerial();
  delay(500);
  mySerial.println("AT+CSTT");//配置APN  
  updateSerial();
  delay(500);
  mySerial.println("AT+CIICR");// 激活移动场景 
  updateSerial();
  delay(500);
  mySerial.println("AT+CIFSR");// 获得本机IP
  updateSerial();
  delay(500);
  mySerial.println("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80");// 建立TCP/IP连接 连接onenet的服务器  进行tcp透传
  updateSerial();
  delay(2000);
  mySerial.println("AT+CIPSEND");// 启动发送数据
  updateSerial();
  delay(100);
  mySerial.print("POST http://api.heclouds.com/devices/");// api地址
  updateSerial();
  delay(100);
  mySerial.print(deviceid);// 为你的设备号
  updateSerial();
  delay(100);
  mySerial.print("/datapoints HTTP/1.1");//
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);//空行
  updateSerial();
  delay(100);
  mySerial.print("Host: ");// 
  updateSerial();
  delay(100);
  mySerial.print(server);// 
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);// 
  updateSerial();
  delay(100);
  mySerial.print("api-key: ");// apikey
  updateSerial();
  delay(100);
  mySerial.print(apikey);// 
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);//
  updateSerial();
  delay(100);
  mySerial.println("Connection: close");// 
  updateSerial();
  delay(100);
  mySerial.print("Content-Length: ");//传输长度
  updateSerial();
  delay(100);
  mySerial.print(150);// 
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);//
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);// 
  updateSerial();
  delay(100);
  mySerial.print("{\"datastreams\":[{\"id\":\"");//
  updateSerial();
  delay(100);
  mySerial.print(dsName);// 
  updateSerial();
  delay(100);
  mySerial.print("\",\"datapoints\":[{\"value\":");//
  updateSerial();
  delay(100);
  mySerial.print(longitude,15);//
  updateSerial();
  delay(100);
  mySerial.print("}]},{\"id\":\"");//
  updateSerial();
  delay(100);
  mySerial.print(dsName2);//
  updateSerial();
  delay(100);
  mySerial.print("\",\"datapoints\":[{\"value\":");//
  updateSerial();
  delay(100);
  mySerial.print(latitude,15);//
  updateSerial();
  delay(100);
  mySerial.print("}]}]}");//
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);// 空行不可省
  updateSerial();
  delay(100);
  mySerial.print(LINEBREAK);//空行不可省
  updateSerial();
  delay(100);
  mySerial.write(26);// 为1A的16进制用于结束
  updateSerial();
  delay(4000);
}



void setup()
  {
    Serial.begin(9600); //set the baud rate of serial port to 9600;
    ss.begin(9600); //set the GPS baud rate to 9600;
    mySerial.begin(9600);
    ss.listen();
  }

void loop()
  {
     while (ss.available() > 0)
      {
        gps.encode(ss.read()); //The encode() method encodes the string in the encoding format specified by encoding.
        
        if (gps.location.isUpdated())
          {
            latitude = gps.location.lat(); //gps.location.lat() can export latitude
            longitude = gps.location.lng();//gps.location.lng() can export latitude
            Serial.print("Latitude=");
            Serial.print(latitude, 6);  //Stable after the fifth position
            Serial.print(" Longitude=");
            Serial.println(longitude, 6);
            sendlocation();
            delay(500);
            
          }
        
     }
      
  }
