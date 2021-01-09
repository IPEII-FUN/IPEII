#include <LiquidCrystal.h>
#include <stdlib.h>

LiquidCrystal lcd(4, 5, 6, 8, 9, 10, 11);

boolean didPrevInput = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int c = 0;
  boolean hasReceivedData = false;
  int moji = 0;
  // put your main code here, to run repeatedly:

  while (Serial.available() > 0) {
    hasReceivedData = true;
    moji = Serial.read();
    //    Serial.println(moji);
    c = c * 10 + moji - 48;
    Serial.println(c);
    delay(10);
  }
  if (hasReceivedData) {
    Serial.print("didPrevInput: ");
    Serial.println((didPrevInput) ? "true" : "false");
    if (!didPrevInput) {
      lcd.print("1P: ");
      didPrevInput = true;
    }
    Serial.print("character");
    Serial.println(moji);
    switch (moji) {
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
        ///        lcd.write(convertKana(c));
        lcd.write(moji);
    }
  }
  delay(100);
}

char convertKana(int c) {
  char returned;
  switch (c) {
    case '｡':
      returned = 0xa1;
      break;
    case '｢':
      returned = 0xa2;
      break;
    case '｣':
      returned = 0xa3;
      break;
    case '､':
      returned = 0xa4;
      break;
    case '･':
      returned = 0xa5;
      break;
    case 'ｦ':
      returned = 0xa6;
      break;
    case 'ｧ':
      returned = 0xa7;
      break;
    case 'ｨ':
      returned = 0xa8;
      break;
    case 'ｩ':
      returned = 0xa9;
      break;
    case 'ｪ':
      returned = 0xaa;
      break;
    case 'ｫ':
      returned = 0xab;
      break;
    case 'ｬ':
      returned = 0xac;
      break;
    case 'ｭ':
      returned = 0xad;
      break;
    case 'ｮ':
      returned = 0xae;
      break;
    case 'ｯ':
      returned = 0xaf;
      break;
    case 'ｰ':
      returned = 0xb0;
      break;
    case 11:
      returned = 0xb1;
      break;
    case 12:
      returned = 0xb2;
      break;
    case 13:
      returned = 0xb3;
      break;
    case 14:
      returned = 0xb4;
      break;
    case 15:
      returned = 0xb5;
      break;
    case 21:
      returned = 0xb6;
      break;
    case 22:
      returned = 0xb7;
      break;
    case 23:
      returned = 0xb8;
      break;
    case 24:
      returned = 0xb9;
      break;
    case 25:
      returned = 0xba;
      break;
    case 31:
      returned = 0xbb;
      break;
    case 32:
      returned = 0xbc;
      break;
    case 33:
      returned = 0xbd;
      break;
    case 34:
      returned = 0xbe;
      break;
    case 35:
      returned = 0xbf;
      break;
    case 41:
      returned = 0xc0;
      break;
    case 42:
      returned = 0xc1;
      break;
    case 43:
      returned = 0xc2;
      break;
    case 44:
      returned = 0xc3;
      break;
    case 45:
      returned = 0xc4;
      break;
    case 51:
      returned = 0xc5;
      break;
    case 52:
      returned = 0xc6;
      break;
    case 53:
      returned = 0xc7;
      break;
    case 54:
      returned = 0xc8;
      break;
    case 55:
      returned = 0xc9;
      break;
    case 61:
      returned = 0xca;
      break;
    case 62:
      returned = 0xcb;
      break;
    case 63:
      returned = 0xcc;
      break;
    case 64:
      returned = 0xcd;
      break;
    case 65:
      returned = 0xce;
      break;
    case 71:
      returned = 0xcf;
      break;
    case 72:
      returned = 0xd0;
      break;
    case 73:
      returned = 0xd1;
      break;
    case 74:
      returned = 0xd2;
      break;
    case 75:
      returned = 0xd3;
      break;
    case 81:
      returned = 0xd4;
      break;
    case 83:
      returned = 0xd5;
      break;
    case 85:
      returned = 0xd6;
      break;
    case 91:
      returned = 0xd7;
      break;
    case 92:
      returned = 0xd8;
      break;
    case 93:
      returned = 0xd9;
      break;
    case 94:
      returned = 0xda;
      break;
    case 95:
      returned = 0xdb;
      break;
    case 01:
      returned = 0xdc;
      break;
    case 03:
      returned = 0xdd;
      break;
    case 04:
      returned = 0xde;
      break;
    case 05:
      returned = 0xdf;
      break;
    case 16:
      returned = 'a';
      break;
    case 17:
      returned = 'b';
      break;
    case 18:
      returned = 'c';
      break;
    case 19:
      returned = 'd';
      break;
    case 10:
      returned = 'e';
      break;
    case 26:
      returned = 'f';
      break;
    case 27:
      returned = 'g';
      break;
    case 28:
      returned = 'h';
      break;
    case 29:
      returned = 'i';
      break;
    case 20:
      returned = 'j';
      break;
    case 36:
      returned = 'k';
      break;
    case 37:
      returned = 'l';
      break;
    case 38:
      returned = 'm';
      break;
    case 39:
      returned = 'n';
      break;
    case 30:
      returned = 'o';
      break;
    case 46:
      returned = 'p';
      break;
    case 47:
      returned = 'q';
      break;
    case 48:
      returned = 'r';
      break;
    case 49:
      returned = 's';
      break;
    case 40:
      returned = 't';
      break;
    case 56:
      returned = 'u';
      break;
    case 57:
      returned = 'v';
      break;
    case 58:
      returned = 'w';
      break;
    case 59:
      returned = 'x';
      break;
    case 50:
      returned = 'y';
      break;
    case 66:
      returned = 'z';
      break;
    default:
      returned = c;
      break;

  }
  return returned;
}



//char convertKana(int c){
//  char returned;
//  Serial.println((int)c);
//  switch(c){
//    case '｡':
//      returned = 0xa1;
//      break;
//    case '｢':
//      returned = 0xa2;
//      break;
//    case '｣':
//      returned = 0xa3;
//      break;
//    case '､':
//      returned = 0xa4;
//      break;
//    case '･':
//      returned = 0xa5;
//      break;
//    case 'ｦ':
//      returned = 0xa6;
//      break;
//    case 'ｧ':
//      returned = 0xa7;
//      break;
//    case 'ｨ':
//      returned = 0xa8;
//      break;
//    case 'ｩ':
//      returned = 0xa9;
//      break;
//    case 'ｪ':
//      returned = 0xaa;
//      break;
//    case 'ｫ':
//      returned = 0xab;
//      break;
//    case 'ｬ':
//      returned = 0xac;
//      break;
//    case 'ｭ':
//      returned = 0xad;
//      break;
//    case 'ｮ':
//      returned = 0xae;
//      break;
//    case 'ｯ':
//      returned = 0xaf;
//      break;
//    case 'ｰ':
//      returned = 0xb0;
//      break;
//    case 'ｱ':
//      returned = 0xb1;
//      break;
//    case 'ｲ':
//      returned = 0xb2;
//      break;
//    case 'ｳ':
//      returned = 0xb3;
//      break;
//    case 'ｴ':
//      returned = 0xb4;
//      break;
//    case 'ｵ':
//      returned = 0xb5;
//      break;
//    case 'ｶ':
//      returned = 0xb6;
//      break;
//    case 'ｷ':
//      returned = 0xb7;
//      break;
//    case 'ｸ':
//      returned = 0xb8;
//      break;
//    case 'ｹ':
//      returned = 0xb9;
//      break;
//    case 'ｺ':
//      returned = 0xba;
//      break;
//    case 'ｻ':
//      returned = 0xbb;
//      break;
//    case 'ｼ':
//      returned = 0xbc;
//      break;
//    case 'ｽ':
//      returned = 0xbd;
//      break;
//    case 'ｾ':
//      returned = 0xbe;
//      break;
//    case 'ｿ':
//      returned = 0xbf;
//      break;
//    case 'ﾀ':
//      returned = 0xc0;
//      break;
//    case 'ﾁ':
//      returned = 0xc1;
//      break;
//    case 'ﾂ':
//      returned = 0xc2;
//      break;
//    case 'ﾃ':
//      returned = 0xc3;
//      break;
//    case 'ﾄ':
//      returned = 0xc4;
//      break;
//    case 'ﾅ':
//      returned = 0xc5;
//      break;
//    case 'ﾆ':
//      returned = 0xc6;
//      break;
//    case 'ﾇ':
//      returned = 0xc7;
//      break;
//    case 'ﾈ':
//      returned = 0xc8;
//      break;
//    case 'ﾉ':
//      returned = 0xc9;
//      break;
//    case 'ﾊ':
//      returned = 0xca;
//      break;
//    case 'ﾋ':
//      returned = 0xcb;
//      break;
//    case 'ﾌ':
//      returned = 0xcc;
//      break;
//    case 'ﾍ':
//      returned = 0xcd;
//      break;
//    case 'ﾎ':
//      returned = 0xce;
//      break;
//    case 'ﾏ':
//      returned = 0xcf;
//      break;
//    case 'ﾐ':
//      returned = 0xd0;
//      break;
//    case 'ﾑ':
//      returned = 0xd1;
//      break;
//    case 'ﾒ':
//      returned = 0xd2;
//      break;
//    case 'ﾓ':
//      returned = 0xd3;
//      break;
//    case 'ﾔ':
//      returned = 0xd4;
//      break;
//    case 'ﾕ':
//      returned = 0xd5;
//      break;
//    case 'ﾖ':
//      returned = 0xd6;
//      break;
//    case 'ﾗ':
//      returned = 0xd7;
//      break;
//    case 'ﾘ':
//      returned = 0xd8;
//      break;
//    case 'ﾙ':
//      returned = 0xd9;
//      break;
//    case 'ﾚ':
//      returned = 0xda;
//      break;
//    case 'ﾛ':
//      returned = 0xdb;
//      break;
//    case 'ﾜ':
//      returned = 0xdc;
//      break;
//    case 'ﾝ':
//      returned = 0xdd;
//      break;
//    case 'ﾞ':
//      returned = 0xde;
//      break;
//    case 'ﾟ':
//      returned = 0xdf;
//      break;
//    default:
//      returned = c;
//      break;
//  }
//  return returned;
//}
//
