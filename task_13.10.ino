#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)

uint8_t data[] = {87, 26, 72, 13, 67, 95, 89, 23, 72, 22, 73, 11, 87, 30, 73};

void tx(char c) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

void print_s(const char* s) {
  while (*s) tx(*s++);
}

void setup() {
  // put your setup code here, to run once:
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  for (uint16_t k = 0; k < 256; k++) {
    uint8_t valid = 1;
    char res[16];
    for (uint8_t i = 0; i < 15; i++) {
      uint8_t p = data[i] ^ (uint8_t)k;
      if (p < 32 || p > 126) {
        valid = 0;
        break;
      }
      res[i] = (char)p;
    }
    res[15] = '\0';
    if (valid) {
      print_s(res);
      tx('\n');
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
