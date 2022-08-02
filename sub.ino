int HS_SOUNDSM = A1;
int Sound_Val;
 
unsigned long previous_time = 0;
unsigned long interval_send = 16000; //서버로 데이터를 보내는 간격 16초
 
int reading; 
int lm35Pin = A0;
int ledPin = 13;
float temperature; 
#include <SoftwareSerial.h>
#include <stdlib.h>
#define DEBUG true
String apiKey = "*************"; //내 서버의 주소
SoftwareSerial ser(2,3); //tx, rx
 
void setup(){ 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  analogReference(INTERNAL);    
  pinMode(HS_SOUNDSM,INPUT);
  ser.begin(9600);                  
}
 
 
void loop()
{ //데이터 수집
  reading = analogRead(lm35Pin);
  temperature = (reading / 10.0);      
  char buf[16];
  String strTemp = dtostrf(temperature, 4, 1, buf);
  Sound_Val=analogRead(HS_SOUNDSM);
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com 접속 IP
  cmd += "\",80";           // api.thingspeak.com 접속 포트, 80
  ser.println(cmd);
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // GET 방식으로 보내기 위한 String, Data 설정
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strTemp);
  getStr +="&field2=";
  getStr += String(Sound_Val);
  getStr += "\r\n\r\n";
 
  // 데이터 보냄
  unsigned long current_time = millis();
  if(current_time - previous_time > interval_send){
    previous_time = current_time;
    Serial.print("Sound : ");
    Serial.println(Sound_Val);
    Serial.print("Temp : ");
    Serial.println(strTemp);
    cmd = "AT+CIPSEND=";
    cmd += String(getStr.length());
    ser.println(cmd);
 
      if(ser.find(">")){
        ser.print(getStr);
      }
      else{
        ser.println("AT+CIPCLOSE");
        // alert user
        Serial.println("AT+CIPCLOSE");
      }
  
}