#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)

uint8_t counter = 0;

uint8_t encrypt(uint8_t p, uint8_t k) {
  uint8_t s1 = p ^ k;
  uint8_t s2 = s1 + k;
  return (s2 << 3) | (s2 >> 5);
}

void setup() {
  // put your setup code here, to run once:
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = encrypt(counter, 0xAB);
  counter++;
  for (volatile uint32_t i = 0; i < 200000; i++);
}
