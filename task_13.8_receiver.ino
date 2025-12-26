#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)

uint8_t decrypt(uint8_t c, uint8_t k) {
  uint8_t s2 = (c >> 3) | (c << 5);
  uint8_t s1 = s2 - k;
  return s1 ^ k;
}

void tx(char c) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

void print_num(uint8_t n) {
  if (n >= 100) tx((n / 100) + '0');
  if (n >= 10)  tx(((n / 10) % 10) + '0');
  tx((n % 10) + '0');
}

void setup() {
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void loop() {
  if (UCSR0A & (1 << RXC0)) {
    uint8_t plain = decrypt(UDR0, 0xAB);
    print_num(plain);
    tx('\n');
  }
}
