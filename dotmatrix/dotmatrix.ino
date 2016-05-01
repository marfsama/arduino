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

unsigned char data_array[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

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

void clock(int pin) {
  digitalWrite(pin, 1);
  delay(1);
  digitalWrite(pin, 0);
}

void hc595_out() {
  clock(RCLK);
}

void hc595_in(unsigned char data) {
  for (unsigned int i = 0; i < 8; i++) {
    digitalWrite(SDI, 0x80 & (data << i));
    clock(SRCLK);
  }
}

// the loop routine runs over and over again forever:
void loop() {
 for (unsigned int i = 0; i < LENGTH(data_array); i++) {
   hc595_in(~data_array[i]);
   hc595_in(data_array[i]);
   hc595_out();
   delay(500);
 }
}
