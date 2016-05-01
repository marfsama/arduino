/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#define LENGTH(x)  (sizeof(x) / sizeof((x)[0]))
#define DOTMATRIX_DATA 2     // weiß, 2
#define DOTMATRIX_LATCH 3    // grün, 3
#define DOTMATRIX_CLOCK 4    // schwarz, 4

 
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
  pinMode(DOTMATRIX_DATA, OUTPUT);
  pinMode(DOTMATRIX_LATCH, OUTPUT);
  pinMode(DOTMATRIX_CLOCK, OUTPUT);
  digitalWrite(DOTMATRIX_DATA, 0);
  digitalWrite(DOTMATRIX_LATCH, 0);
  digitalWrite(DOTMATRIX_CLOCK, 0);
}

void clock(int pin) {
  digitalWrite(pin, 1);
  digitalWrite(pin, 0);
}

void hc595_out() {
  clock(DOTMATRIX_LATCH);
}

void hc595_in(unsigned char data) {
  for (unsigned int i = 0; i < 8; i++) {
    digitalWrite(DOTMATRIX_DATA, 0x80 & (data << i));
    clock(DOTMATRIX_CLOCK);
  }
}

unsigned char select_led(int pos) {
  return 1 << pos;
}

unsigned char rotl8 (unsigned char n, unsigned int c) {
  const unsigned int mask = ((sizeof(n) << 3) -1);
  c &= mask;  // avoid undef behaviour with NDEBUG.  0 overhead for most types / compilers
  return (n<<c) | (n>>( (-c)&mask ));
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned long frametime = 100;
  
  for (int shift = 0; shift < 8; shift++) {
    unsigned long startime = millis();
    while(millis() - startime < frametime) {
      for (unsigned int x = 0; x < 8; x++) {
        unsigned char row = 0, col = 0;
        row = select_led(x);
        col = rotl8(data_array[x],shift);
        
        hc595_in(~col);
        hc595_in(row);
        hc595_out();
      }
    }
  } 
}

