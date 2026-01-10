const uint8_t key = 0xAA;
uint8_t counter = 0;

void setup() {
  // 1. Set Baud Rate
  UBRR0H = (uint8_t)(103 >> 8);
  UBRR0L = (uint8_t)103;
  
  UCSR0B = (1 << TXEN0);
  
  UCSR0C = (3 << UCSZ00); 
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t cipher = counter;

  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = cipher;
  counter++;
  
  for(volatile long i = 0; i < 200000; i++);
}
