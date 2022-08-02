int dist_val = A5;
int om ; // one meter
int tm ; // three meter
int cm;
unsigned long previous_time = 0;
unsigned long interval_dist = 10; //0.01초마다 거리체크
 
//블루투스
#include <SoftwareSerial.h> 
#define BT_RX 10 //블루투스의 TX
#define BT_TX 11 //블루투스의 RX
SoftwareSerial BT(BT_RX, BT_TX); 
 
//모터드라이브 L9110S-4WAY
#define Front_Left_A1 2
#define Front_Left_A2 3
#define Front_Right_B1 4
#define Front_Reft_B2 5
#define Back_Left_C1 6
#define Back_Left_C2 7
#define Back_Right_D1 8
#define Back_Right_D2 9
int v=255; //모터 속도
char c = '0';
 
void setup() {
  Serial.begin(9600);
  BT.begin(9600); 
  pinMode(Front_Left_A1, OUTPUT);//1번 모터
  pinMode(Front_Left_A2, OUTPUT);
  
  pinMode(Front_Right_B1, OUTPUT);//2번 모터
  pinMode(Front_Reft_B2, OUTPUT);
  
  pinMode(Back_Left_C1, OUTPUT);//3번 모터
  pinMode(Back_Left_C2, OUTPUT);
  
  pinMode(Back_Right_D1, OUTPUT);//4번 모터
  pinMode(Back_Right_D2, OUTPUT);
}
 
void loop() {
  char val = BT.read();
  if(BT.available()){
    Serial.write(BT.read());
  }
//블루투스로 제어하는 용도
  switch (val){
    case 'S':
        Serial.println("stop");
        Stop();
        break;
    case 'F':
        Serial.println("forward");
        Forward();
        break;
    case 'B':
        Serial.println("backward");
        Backward();
        break;
    case 'L':
        Serial.println("Left");
        Left();
        break;
    case 'R':
        Serial.println("Right");
        Right();
        delay(10);
        break;
    case 'D':
        Serial.println("LOW");
        v=150;
        delay(10);
        break;
    case 'U':
        Serial.println("HIGH");
        v=255;
        delay(10);
        break;
    case 'O':
      for(;;){
        unsigned long current_time = millis();
        if(current_time - previous_time > interval_dist){
        previous_time = current_time;
        cm = (analogRead(dist_val)*3)/10;
        Serial.print(cm);
        Serial.println(" cm");
      }
            
      if(cm<15){
        Stop();
        delay(650);
        Backward();
        delay(550);
        Left();
        delay(170);
      }
      else if(14<cm&&cm<22){
        Left();
      }
      else{
        Forward();
      }
    }
        
}
//시리얼통신으로 제어하는 용도
  char val2 = Serial.read();
  switch (val2){
    case 'S':
      Serial.println("stop");
      Stop();
      break;
    case 'F':
      Serial.println("forward");
      Forward();
      break;
    case 'B':
      Serial.println("backward");
      Backward();
      break;
    case 'L':
      Serial.println("Left");
      Left();
      break;
    case 'R':
      Serial.println("Right");
      Right();
      delay(10);
      break;
    case 'D':
      Serial.println("LOW");
      v=150;
      delay(10);
      break;
    case 'U':
      Serial.println("HIGH");
      v=255;
      delay(10);
      break;
    case 'O':
      for(;;){
        unsigned long current_time = millis();
        if(current_time - previous_time > interval_dist){
          previous_time = current_time;
          cm = (analogRead(dist_val)*3)/10;
          Serial.print(cm);
          Serial.println(" cm");
        }
        if(cm<15){
          Stop();
          delay(650);
          Backward();
          delay(550);
          Left();
          delay(170);
        }
        else if(14<cm&&cm<22){
          Left();
        }
        else{
          Forward();
        }
      }
    
  }
}
 
void Forward(){
  analogWrite(2, v);
  analogWrite(3, 0); 
  analogWrite(4, 0);
  analogWrite(5, v); 
  analogWrite(6, v);       
  analogWrite(7, 0);
  analogWrite(8, 0);       
  analogWrite(9, v); 
}
 
void Backward(){  
  analogWrite(2, 0);
  analogWrite(3, v); 
  analogWrite(4, v);
  analogWrite(5, 0); 
  analogWrite(6, 0);       
  analogWrite(7, v);
  analogWrite(8, v);       
  analogWrite(9, 0); 
}
 
void Stop(){
  analogWrite(2, 0);
  analogWrite(3, 0); 
  analogWrite(4, 0);
  analogWrite(5, 0); 
  analogWrite(6, 0);       
  analogWrite(7, 0);
  analogWrite(8, 0);       
  analogWrite(9, 0); 
}
 
void Left(){
  analogWrite(2, 0);
  analogWrite(3, v); 
  analogWrite(4, 0);
  analogWrite(5, v); 
  analogWrite(6, 0);       
  analogWrite(7, v);
  analogWrite(8, 0);       
  analogWrite(9, v); 
}
 
void Right(){
  analogWrite(2, v);
  analogWrite(3, 0); 
  analogWrite(4, v);
  analogWrite(5, 0); 
  analogWrite(6, v);       
  analogWrite(7, 0);
  analogWrite(8, v);       
  analogWrite(9, 0); 
}
​