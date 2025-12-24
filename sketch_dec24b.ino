void setup() {
    // put your setup code here, to run once:
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)103;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (UCSR0A & (1 << RXC0)) {
        uint8_t data = UDR0;
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = data;
    }
}