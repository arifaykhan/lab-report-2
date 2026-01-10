const uint8_t key = 0xAA;

void setup() {
  UBRR0H = (uint8_t)(103 >> 8);
  UBRR0L = (uint8_t)103;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  
  UCSR0C = (3 << UCSZ00);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (UCSR0A & (1 << RXC0)) {
    uint8_t cipher = UDR0;

    uint8_t decrypted = cipher;
    
    USART_Transmit('D');
    USART_Transmit(':');
    
    USART_Transmit(decrypted); 
    USART_Transmit('\n');
  }
}

void USART_Transmit(char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}
