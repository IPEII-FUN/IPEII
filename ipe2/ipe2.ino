// testcolors demo for Adafruit RGBmatrixPanel library.
// Renders 512 colors on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// Library supports 4096 colors, but there aren't that many pixels!  :)

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

  uint8_t r=0, g=0, b=0;

int i = 0;
int j = 0;

int reversei = 0;
int reversej = 0;
 
void setup() {
  matrix.begin();


  // Draw top half
  for(uint8_t x=0; x<32; x++) {
    for(uint8_t y=0; y<8; y++) {
      matrix.drawPixel(x, y, matrix.Color333( 0, 0, 0));
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
  for(uint8_t x=0; x<32; x++) {
    for(uint8_t y=8; y<16; y++) {
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
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
  for(int i2 = 0; i2 < 33 ; i2++){
    for(int j2 = 0; j2 < 17; j2++){
      matrix.drawPixel(i2, j2, matrix.Color333(0, 0, 0));
    }
  }
  // Do nothing -- image doesn't change

  Serial.print("i = ");
  Serial.print(i);
  Serial.print("j = ");
  Serial.print(j);
  Serial.print(" reversei = ");
  Serial.println(reversei);
  Serial.print(" reversej = ");
  Serial.println(reversej);
  if(i >= 31){
      reversei = 1;
  }else if(i <= 0){
      reversei = 0;
  }

  if(j >= 15){
    reversej = 1;
  }else if(j <= 0){
    reversej = 0;
  }
  
  matrix.drawPixel(i, j, matrix.Color333(50, 50, 50));

  if(!reversei){
    i++;
  }else{
    i--;
  }
  if(!reversej){
    j++;
  }else{
    j--;
  }
 
  delay(100);
}
