#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

uint32_t nonce_counter[2] = {0, 0};
uint32_t keystream_block[2];
uint8_t  tx_data_counter = 0;       

void Speck64128_Encrypt(const uint32_t pt[2], uint32_t ct[2]);
void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);

void setup() {
  // put your setup code here, to run once:
    USART_Init(MYUBRR);
}

void loop() {
    // put your main code here, to run repeatedly:
    Speck64128_Encrypt(nonce_counter, keystream_block);

    uint8_t key_byte = (keystream_block[0] & 0xFF); 

    uint8_t ciphertext = tx_data_counter ^ key_byte;

    USART_Transmit(ciphertext);

    tx_data_counter++;     
    nonce_counter[0]++;    

    for(volatile long i = 0; i < 200000; i++);
}

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}
void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

static const uint32_t key[4] = {0x1A2B3C4D, 0x5E6F7A8B, 0x91A2B3C4, 0xD5E6F7A8};

#define ROR8(x) (((x) >> 8) | ((x) << 24)) 
#define ROL3(x) (((x) << 3) | ((x) >> 29)) 

void Speck64128_Encrypt(const uint32_t pt[2], uint32_t ct[2]) {
    uint32_t y = pt[0];
    uint32_t x = pt[1];
    uint32_t b = key[0];
    uint32_t a[3];
    a[0] = key[1]; a[1] = key[2]; a[2] = key[3];

    ct[0] = y; ct[1] = x;

    for (int i = 0; i < 27; i++) {
        ct[1] = (ROR8(ct[1]) + ct[0]) ^ b;
        ct[0] = ROL3(ct[0]) ^ ct[1];

        b = (ROR8(b) + a[i % 3]) ^ i;
        a[i % 3] = ROL3(a[i % 3]) ^ b;
    }
}
