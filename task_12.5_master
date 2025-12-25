void setup() {
  // put your setup code here, to run once:
  DDRB |= (1 << 5);
  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2);

  TWBR = 72;
  PORTC |= (1 << 4) | (1 << 5);
  TWCR = (1 << TWEN);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buttonState = !(PIND & (1 << 2));
  
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  
  TWDR = (0x08 << 1) | 0;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  
  TWDR = buttonState;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  
  TWDR = (0x08 << 1) | 1;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  uint8_t receivedData = TWDR;
  
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

  if (receivedData) {
    PORTB |= (1 << 5);
  } else {
    PORTB &= ~(1 << 5);
  }
}
