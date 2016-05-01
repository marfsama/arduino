/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#define LENGTH(x)  (sizeof(x) / sizeof((x)[0]))
#define SDI 2
#define RCLK 3
#define SRCLK 4

 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int pins[4] = {9,10,11,12};

unsigned char data_array[8] = {
0b10000001, 
0b11000011, 
0b11111111, 
0b10000001, 
0b10100101, 
0b10011001, 
0b01000010, 
0b00111100
};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (unsigned int pin = 0; pin < LENGTH(pins); pin++) {
    pinMode(pins[pin], OUTPUT);
  }
  pinMode(SDI, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  digitalWrite(SDI, 0);
  digitalWrite(RCLK, 0);
  digitalWrite(SRCLK, 0);
}

void clock(int pin, int delayms) {
  digitalWrite(pin, 1);
  if (delayms > 0) {
    delay(1);
  }
  digitalWrite(pin, 0);
}

void hc595_out() {
  clock(RCLK,1);
}

void hc595_in(unsigned char data) {
  for (unsigned int i = 0; i < 8; i++) {
    digitalWrite(SDI, 0x80 & (data << i));
    clock(SRCLK,0);
  }
}

unsigned char select_led(int pos) {
  return 1 << pos;
}

// the loop routine runs over and over again forever:
void loop() {
 for (unsigned int x = 0; x < 8; x++) {
    unsigned char row = 0, col = 0;
    row = select_led(x);
    col = data_array[x];
    
    hc595_in(~col);
    hc595_in(row);
    hc595_out();
  }
 
}

