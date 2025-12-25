volatile uint8_t digit = 0;

const uint8_t segmentMasks[10] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

void displayDigit(uint8_t n) {
    uint8_t mask = segmentMasks[n];

    PORTB &= ~((1 << PB0) | (1 << PB1));
    PORTD &= ~((1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));

    if (mask & (1 << 0)) PORTB |= (1 << PB1);
    if (mask & (1 << 1)) PORTB |= (1 << PB0);
    if (mask & (1 << 2)) PORTD |= (1 << PD7);
    if (mask & (1 << 3)) PORTD |= (1 << PD6);
    if (mask & (1 << 4)) PORTD |= (1 << PD5);
    if (mask & (1 << 5)) PORTD |= (1 << PD4);
    if (mask & (1 << 6)) PORTD |= (1 << PD3);
}

ISR(TIMER1_COMPA_vect) {
    if (PIND & (1 << PIND2)) { 
        digit++;
        if (digit > 9) digit = 0;
        displayDigit(digit);
    }
}

void setup() {
    // put your setup code here, to run once: 
    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRD |= (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    TCCR1A = 0; 
    TCCR1B = (1 << WGM12) | (1 << CS12); 
    OCR1A = 31249; 
    TIMSK1 |= (1 << OCIE1A); 

    displayDigit(0);
    sei();
}

void loop() {
    // put your main code here, to run repeatedly: 
    
}