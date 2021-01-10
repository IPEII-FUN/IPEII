// 液晶パネルを実装したほう。（Slave側）
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal lcd(4, 5, 6, 8, 9, 10, 11);
Servo myservo1;
Servo myservo2;

const int SW = 7;
const int led = 12;
boolean didPrevInput = false;
unsigned char wireData = 0;
char score1c[3] = {};
char score2c[3] = {};
int score1 = 0;
int score2 = 0;
int speaker = 13;
int BEAT = 1000;
int vibe = A0;
int servoPins[2] = {A1, A2};
int therm = A3;

int state = 0;
int preState = 0;
boolean buttonState = false;

int speakerStatus = 0;

int do1 = 262;
int re = 294;
int mi = 330;
int fa = 349;
int so = 392;
int ra = 440;
int si = 493;
int do2 = 523;

int thermValue = 0;
float temperature = 0;// 気温
float resistor = 0;  // 抵抗値

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.setTimeout(50);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  myservo1.attach(servoPins[0]);
  myservo2.attach(servoPins[1]);
  myservo1.write(0);
  myservo2.write(0);
}

void requestEvent(){
  thermValue = analogRead(therm);
  resistor = 10.0 * thermValue/(1023.0 - thermValue);
  temperature = (25.83 - resistor )/0.63;
  Serial.print("Tempearture(C): ");
  Serial.println(temperature);
  int sentValue = (int)temperature;
  Serial.print("sending: ");
  Serial.println((int) sentValue);
  Wire.write(sentValue);
}

void receiveEvent(){
  // データを受信
  Serial.println("data received");
  if(Wire.available() > 0 ){
    wireData = Wire.read();
    Serial.println((int)wireData);
    if(wireData == 2 || wireData == 4 ){
      Serial.println(score1);
      if(0 <= score1 && score1 < 1000){
        if(wireData == 2 )score1++; else score1--;
        if(score1 < 0) score1 = 0;
      }else{
        score1 = 0;
      }
      score1c[0] = (score1 / 100) + 48;
      score1c[1] = score1 % 100 / 10 + 48;
      score1c[2] = score1 % 10 + 48;
      if(score1 < 10){
        lcd.setCursor(13, 0);
      }else if(score1 < 100){
        lcd.setCursor(13, 0);
      }else{
        lcd.setCursor(13, 0);
      }
      lcd.print(score1c);
    }else if(wireData == 3 || wireData == 5){
      Serial.println(score2);
      if(0 <= score2 && score2 < 1000){
        if(wireData == 3) score2++; else score2--;
        if(score2 < 0) score2 = 0;
      }else{
        score2 = 0;
      }
      score2c[0] = (score2 / 100) + 48;
      score2c[1] = score2 % 100 / 10 + 48;
      score2c[2] = score2 % 10 + 48;
      if(score2 < 10){
        lcd.setCursor(13, 1);
      }else if(score2 < 100){
        lcd.setCursor(13, 1);
      }else{
        lcd.setCursor(13, 1);
      }
      lcd.print(score2c);
    }else if(wireData == 0 || wireData == 1){
      if(wireData == 0){
        score1 = 0;
        score1c[0] = (score1 / 100) + 48;
        score1c[1] = score1 % 100 / 10 + 48;
        score1c[2] = score1 % 10 + 48;
        if(score1 < 10){
          lcd.setCursor(13, 0);
        }else if(score1 < 100){
          lcd.setCursor(13, 0);
        }else{
          lcd.setCursor(13, 0);
        }
        lcd.print(score1c);
      }else if(wireData == 1){
        score2 = 0;
        score2c[0] = (score2 / 100) + 48;
        score2c[1] = score2 % 100 / 10 + 48;
        score2c[2] = score2 % 10 + 48;
        if(score2 < 10){
          lcd.setCursor(13, 1);
        }else if(score2 < 100){
          lcd.setCursor(13, 1);
        }else{
          lcd.setCursor(13, 1);
        }
        lcd.print(score2c);
      }
    }else if(6 <= wireData && wireData <= 11 ){
      Serial.println("BEEP SPEAKER");
      speakerStatus = wireData;
    }else if(12 <= wireData && wireData <= 15){
      switch(wireData){
        case 12:
          Serial.println("stand flag servo1");
          myservo1.write(90);
          break;
        case 13:
          Serial.println("stand flag servo2");
          myservo2.write(90);
          break;
        case 14:
          Serial.println("fold flag servo1");
          myservo1.write(0);
          break;
        case 15:
          Serial.println("fold flag servo2");
          myservo2.write(0);
          break;
      }
    }
  }
}


void beepSpeaker (int value ){
  Serial.println("beepSpeaker function");
}

void loop() {
  
  lcd.blink();
  int c = 0;
  boolean hasReceivedData = false;
  int moji = 0;
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
    hasReceivedData = true;
      moji = Serial.read();
//    Serial.println(moji);
    c = c*10 + moji-48;
    Serial.println(c);
    delay(100);    
  }
  if(hasReceivedData){
    Serial.print("didPrevInput: ");
    Serial.println((didPrevInput) ? "true" : "false");
    if(!didPrevInput){
      lcd.setCursor(0,0);
      lcd.print("1P: ");
      didPrevInput = true;
    }
    Serial.print("character");
    Serial.println(moji);
    switch(moji){
      case '^':
        lcd.clear();
        break;
      case '#':
        lcd.setCursor(0, 1); 
        lcd.print("2P: ");
        break;
      case ';':
        didPrevInput = false;
        break;
      default:
        lcd.write(moji);
    }
  }

  if(speakerStatus != 0){
    switch (speakerStatus){
      case 6:
        analogWrite(vibe, 255);
        tone(speaker, mi);
        delay(100);
        tone(speaker, so);
        delay(100);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      case 7:
        analogWrite(vibe, 255);
        tone(speaker, so);
        delay(100);
        tone(speaker, mi);
        delay(100);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      case 8:
        analogWrite(vibe, 255);
        tone(speaker, so);
        delay(100);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      case 9:
        analogWrite(vibe, 255);
        tone(speaker, mi);
        delay(100);
        tone(speaker, so);
        delay(100);
        tone(speaker, mi);
        delay(100);
        tone(speaker, so);
        delay(100);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      case 10:
        analogWrite(vibe, 255);
        tone(speaker, so);
        delay(100);
        tone(speaker, mi);
        delay(100);
        tone(speaker, so);
        delay(100);
        tone(speaker, mi);
        delay(100);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      case 11:
        analogWrite(vibe, 255);
        tone(speaker, do1);
        delay(200);        
        tone(speaker, mi);
        delay(200);
        tone(speaker, so);
        delay(200);
        tone(speaker, si);
        delay(200);
        tone(speaker, do2);
        delay(200);
        tone(speaker, 0);
        noTone(speaker);
        analogWrite(vibe, 0);
        break;
      default:
      break;
    }
    speakerStatus = 0;
  }

  state = digitalRead(SW);
  if(state && !(preState)){
    if(buttonState){
      buttonState = false;
    }else{
      buttonState = true;
    }
    Serial.println(buttonState ? "true" : "false");
    delay(10);
  }
  preState = state;

  if(buttonState){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }

  
  delay(100);
}
