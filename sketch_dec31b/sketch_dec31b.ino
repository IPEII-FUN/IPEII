// 液晶パネルを実装したほう。（Slave側）
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <Wire.h>

LiquidCrystal lcd(4, 5, 6, 8, 9, 10, 11);

boolean didPrevInput = false;
char wireData = 0;
char score1c[3] = {};
char score2c[3] = {};
int score1 = 0;
int score2 = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.setTimeout(50);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void requestEvent(){
  // データを受信
  if(Wire.available() > 0 ){
    wireData = Wire.read();
    Serial.println(wireData);
    if(wireData == 2 ){
      if(score1 < 1000){
        score1++;
      }else{
        score1 = 0;
      }
      score1c[0] = (score1 / 100) ;
      score1c[1] = score1 % 100 / 10;
      score1c[2] = score1 % 10;
      if(score1 < 10){
        lcd.setCursor(14, 1);
      }else if(score1 < 100){
        lcd.setCursor(13, 1);
      }else{
        lcd.setCursor(12, 1);
      }
      lcd.print(score1c);
    }else if(wireData = 3){
      if(score2 < 1000){
        score2++;
      }else{
        score1 = 0;
      }      if(score2 < 10){
        lcd.setCursor(14,1);
      }else{
        lcd.setCursor(13,1);
      }
      score2c[0] = (score1 / 100) ;
      score2c[1] = score1 % 100 / 10;
      score2c[2] = score1 % 10;
      if(score2 < 10){
        lcd.setCursor(14, 1);
      }else if(score2 < 100){
        lcd.setCursor(13, 1);
      }else{
        lcd.setCursor(12, 1);
      }
      lcd.print(score2c);
    }
  }
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
  delay(100);
}
