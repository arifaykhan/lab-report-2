#include <util/delay.h>

volatile uint16_t eeprom_addr = 0;

void EEPROM_write(uint16_t uiAddress, uint8_t ucData) {
    while(EECR & (1 << EEPE));    
    EEAR = uiAddress;             
    EEDR = ucData;
    EECR |= (1 << EEMPE);         
    EECR |= (1 << EEPE);          
}

uint8_t EEPROM_read(uint16_t uiAddress) {
    while(EECR & (1 << EEPE));    
    EEAR = uiAddress;             
    EECR |= (1 << EERE);          
    return EEDR;                  
}

void play_pattern() {
    for (uint16_t i = 0; i < eeprom_addr; i++) {
        uint8_t val = EEPROM_read(i);
        PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7)); 
        
        if (val == '1') PORTD |= (1 << PD5);
        else if (val == '2') PORTD |= (1 << PD6);
        else if (val == '3') PORTD |= (1 << PD7);
        
        _delay_ms(500);
        PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
        _delay_ms(200);
    }
    eeprom_addr = 0;
}

void setup() {
    // put your setup code here, to run once:
    UBRR0H = 0; UBRR0L = 103;
    UCSR0B = (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    DDRD |= (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (UCSR0A & (1 << RXC0)) {
        uint8_t received = UDR0;

        if (received == '4') {
            play_pattern();
        } else if (received >= '1' && received <= '3') {
            EEPROM_write(eeprom_addr++, received);
            PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
            _delay_ms(50);
            PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
        }
    }
}
