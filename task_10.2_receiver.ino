void setup() {
    // put your setup code here, to run once:
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)103;
    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    DDRD |= (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (UCSR0A & (1 << RXC0)) {
        uint8_t received = UDR0;

        PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));

        if (received == '1') PORTD |= (1 << PD5);
        if (received == '2') PORTD |= (1 << PD6);
        if (received == '3') PORTD |= (1 << PD7);
    }
}
