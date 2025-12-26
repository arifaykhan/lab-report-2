void setup() {
  // put your setup code here, to run once:
  DDRB |= (1 << 5); 

  const uint16_t LIMIT = 18000;
  const uint16_t BIT_SIZE = (LIMIT / 2);
  uint8_t sieve[1125]; 

  for (uint16_t i = 0; i < 1125; i++) sieve[i] = 0xFF;

  uint16_t primeCount = 1; 
  PORTB |= (1 << 5); 

  for (uint16_t p = 3; p * p <= LIMIT; p += 2) {
    if (sieve[(p / 2) >> 3] & (1 << ((p / 2) & 7))) {
      for (uint16_t i = p * p; i <= LIMIT; i += 2 * p) {
        sieve[(i / 2) >> 3] &= ~(1 << ((i / 2) & 7));
      }
    }
  }

  for (uint16_t i = 3; i <= LIMIT && primeCount < 2000; i += 2) {
    if (sieve[(i / 2) >> 3] & (1 << ((i / 2) & 7))) {
      primeCount++;
      PORTB ^= (1 << 5); 
    }
  }

  if (primeCount >= 2000) {
    PORTB |= (1 << 5); 
    while(1); 
  }
}

void loop() {
    // put your main code here, to run repeatedly: 
    
}
