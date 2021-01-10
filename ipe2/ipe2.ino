#include <RGBmatrixPanel.h>
// shiroto added
#include <Wire.h>


#define CLK  8   
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

  uint8_t r=0, g=0, b=0;
  const  int bord_side=32;//const
  const  int bord_ver=16;//const
  const int a5=A5;
  const int a4=A4;
  const int p1=13;
  const int p2=12;
  int in5;
  int in4;
  int p1tf=0;
  int p2tf=0;
  int x=0;
  int y=0;
  int i,j;
  int k=0;
  int p1ver=0;
  int p2ver=0;
  boolean bs=true;//true右
  boolean bv=true;//true上
  int game=0;
  int mozi[16][7]={
  {1,1,1,1,1,1,1},
  {1,0,0,0,0,0,1},
  {1,0,0,0,0,0,1},
  {1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0}
  };

// shiroto added
int frameCount = 0;

int num = 0;

 
void setup() {
  matrix.begin();

  // shiroto added
  Wire.begin();

  // Draw top half
  for(uint8_t aa=0; aa<32; aa++) {
    for(uint8_t bb=0; bb<8; bb++) {
      matrix.drawPixel(aa, bb, matrix.Color333( 0, 0, 0));
      r++;
      if(r == 8) {
        r = 0;
        g++;
        if(g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }

  // Draw bottom half
  for(uint8_t aa=0; aa<32; aa++) {
    for(uint8_t bb=8; bb<16; bb++) {
      matrix.drawPixel(aa, bb, matrix.Color333(0, 0, 0));
      r++;
      if(r == 8) {
        r = 0;
        g++;
        if(g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }
  Serial.begin(9600);
  
}

void loop() {
  // shiroto added
  boolean didSerialInput = false;
  while(Serial.available() >  0){
    didSerialInput = true;
    char c = Serial.read();
    num = num*10 + c-48;
    Serial.println(num);
    if(num > 255) num = 0;
  }
  if(didSerialInput){
    Wire.beginTransmission(8);
    Wire.write(num);
    int succeed = Wire.endTransmission(8);
    Serial.println((succeed == 0) ? "send succeed": "send failed");
    num = 0;
  }
  
  
  in4=analogRead(a4);
  in5=analogRead(a5);
  p1ver=(int)(((double)in4/1023.0)*(15.0));
  p2ver=(int)(((double)in5/1023.0)*(15.0));
  //Serial.print(p2ver);
  for(j=0;j<bord_ver;j++){
    for(i=0;i<bord_side;i++){
      matrix.drawPixel(i, j, matrix.Color333(0, 0, 0));
    }
    }
switch(game){
      case 0:
    
    if(digitalRead(p2)==LOW){
      p2tf=0;
      }else{
      p2tf=1;
        }
        if(digitalRead(p1)==LOW)
        {
      p1tf=0;
      }else{
      p1tf=1;
        }

  

        
  if(bs){
    Serial.println("\np2ver");
    Serial.println(p2ver);
    Serial.println("\ny");
    Serial.println(y);
    
    if(x>=bord_side-2-p2tf){
    if(p2ver-1==y || p2ver==y || p2ver+1==y){
    }else if(p2ver-2==y && (bv == true || y==0)){
        bv=!bv;
      }else if(p2ver+2==y && (bv == false ||y==15)){
        bv=!bv;
        }else{
    game=1;
    x+=2;  
        }
 
    x--;
  bs=!bs;
  }else{  x++; }
  
  }else{
  if(x<=0+1+p1tf){
        if(p1ver-1==y || p1ver==y || p1ver+1==y){
    }else if(p1ver-2==y && (bv == true || y==0)){
        bv=!bv;
      }else if(p1ver+2==y && (bv == false ||y==15)){
        bv=!bv;
        }else{
    game=1;
    x-=2;  
        }
  x++;      
  bs=!bs;

  }
  else{  x--;  }
  }
  
  if(bv){
    
  if(y>=bord_ver-1){
  bv=!bv;
  y--;
  }else{
  y++;
  }
  
  }else{
  if(y<=0){
  bv=!bv;
  y++;
  }
  else{y--;}
  }


      matrix.drawPixel(x, y, matrix.Color333(50, 50, 50));
      for(i=-1;i<2;i++)matrix.drawPixel(31-p2tf, p2ver+i , matrix.Color333(100, 40, 0));
      for(i=-1;i<2;i++)matrix.drawPixel(p1tf, p1ver+i , matrix.Color333(0, 40, 100));

break;
      default:
          if(digitalRead(13)==HIGH){
            game=0;
            bs=true;
            bv=true;
            x=0;
            y=0;
            k=0;
            }


               if(k<5)k++;  
  // Do nothing -- image doesn't change
 j=0;
  while(j<=k){
   for(i=0;i<16;i++){
      if(mozi[i][j]==1){
      matrix.drawPixel(31-(k-j), i, matrix.Color333(50, 50, 50));
      }
      else{
      matrix.drawPixel(31-(k-j), i, matrix.Color333(0, 0, 0));
      }
   }
   j++; 
  }          
      break;
      } 
          if(digitalRead(p1)==LOW &&digitalRead(p2)==LOW){
      delay(100);
          }else if(digitalRead(p1)==LOW || digitalRead(p2)==LOW){
            delay(30);
            }else{
              delay(0);
              }

  //shiroto added
  if(frameCount % 60 == 0){
    Wire.requestFrom(8, 1);
    while(Wire.available()){
      char c = Wire.read();
      Serial.print("gotten value c: ");
      Serial.println((int)c);
      int temperature = c;
      Serial.print("temperature: ");
      Serial.println(temperature);
    }
  }

  frameCount++;
}
