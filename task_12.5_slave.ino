void setup() {
  // put your setup code here, to run once:
  DDRB |= (1 << 5);
  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2);

  TWAR = (0x08 << 1);
  PORTC |= (1 << 4) | (1 << 5);
  TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (TWCR & (1 << TWINT)) {
    uint8_t status = TWSR & 0xF8;

    if (status == 0x60) {
      TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    } 
    else if (status == 0x80) {
      uint8_t receivedData = TWDR;
      if (receivedData) {
        PORTB |= (1 << 5);
      } else {
        PORTB &= ~(1 << 5);
      }
      TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    }
    else if (status == 0xA8) {
      uint8_t buttonState = !(PIND & (1 << 2));
      TWDR = buttonState;
      TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    }
    else if (status == 0xB8) {
      TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    }
    else {
      TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    }
  }
}
