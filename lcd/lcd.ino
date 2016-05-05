/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte cat[64] = {
  B00000,
  B01000,
  B10000,
  B10000,
  B10000,
  B01111,
  B00111,
  B00111,
  
  B00100,
  B00110,
  B00111,
  B01111,
  B00101,
  B11111,
  B11111,
  B11111,
  
  B00010,
  B00110,
  B11110,
  B11111,
  B11010,
  B01111,
  B11110,
  B11100,
  
  0,0,0,0,0,0,0,0,
  
  B00111,
  B00111,
  B00101,
  B00101,
  B00100,
  B00000,
  B00000,
  B00000,

  B11111,
  B00010,
  B00010,
  B00010,
  B00010,
  B00000,
  B00000,
  B00000,

  B11000,
  B01100,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  
  0,0,0,0,0,0,0,0
};

byte cat2[64] = {
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
  B01111,
  B01111,
 
  B00100,
  B00110,
  B00111,
  B01111,
  B00101,
  B11111,
  B11111,
  B11111,
  
  B00010,
  B00110,
  B11110,
  B11111,
  B11010,
  B01111,
  B11110,
  B11100,
  
  0,0,0,0,0,0,0,0,
  
  B00111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
  B00000,
  B00000,
  
  B11111,
  B00010,
  B00010,
  B00010,
  B00010,
  B00000,
  B00000,
  B00000,

  B11000,
  B01000,
  B01000,
  B01000,
  B01000,
  B00000,
  B00000,
  B00000,
  
  0,0,0,0,0,0,0,0
};

byte cat_frame1[64];
byte cat_frame2[64];

void createImage(byte* image, int numImages) {
  for (int i = 0; i < numImages; i++) {
    lcd.createChar(i, image+i*8);
  }
}


/** Bewegt die komplette Zeile 1 Pixel nach rechts. 
 * Von jedem Byte werden nur die 5 least significant Bits verwendet.
 */
void shiftRight(byte* imageLine, int numBytes) {
  for (int i = 0; i < 8; i++) {
    int overflow = 0;
    for (int b = 0; b < numBytes; b++) {
      if (overflow > 0) {
        imageLine[b*8+i] |= 0b00100000;
      }
      overflow = imageLine[b*8+i] & 1;
      
      imageLine[b*8+i] >>= 1;
    }
  }
  
}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void writeImage(int col, int width) {
  byte charNum = 0;
  lcd.setCursor(col, 0);
  for (int i = 0; i < width; i++) {
    lcd.write(charNum++);
  }
  lcd.setCursor(col, 1);
  for (int i = 0; i < width; i++) {
    lcd.write(charNum++);
  }
}

void loop() {
  while (1) {
    byte animation = 0;
    for (int col = 0; col < 13; col++) {
      lcd.clear();
      memcpy(cat_frame1, cat, 64);
      memcpy(cat_frame2, cat2, 64);
      createImage(cat_frame1, 6);
      writeImage(col,4);
      for (int pixel = 0; pixel < 5; pixel++) {
        createImage(animation == 0 ? cat_frame1 : cat_frame2, 8);
        animation++;
        animation &= 1;
        delay(500);
        shiftRight(cat_frame1,4);
        shiftRight(cat_frame1+4*8,4);
        shiftRight(cat_frame2,4);
        shiftRight(cat_frame2+4*8,4);
      }
    }
  }
  
}
