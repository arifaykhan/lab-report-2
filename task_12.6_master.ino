// master board
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT); 
  DDRB |= (1 << PB0);      
  Serial.println("press the button to begin");
}

void loop() {
  if (digitalRead(2) == HIGH) {
    delay(500); 

    Wire.begin(); 
    runTest("wire.begin() ");

    Wire.begin(); 
    TWSR = (1 << TWPS0);
    TWBR = 72;
    runTest("25khz, twbr 72, prescaler 4");

    Wire.begin(); 
    TWSR &= ~((1 << TWPS1) | (1 << TWPS0)); 
    TWBR = 72;
    runTest("100 khz, twbr 72, prescaler 1");

    Wire.begin(); 
    TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
    TWBR = 12;
    runTest("400 khz, twbr 72, prescaler 1");

    Serial.println("done");
    while(digitalRead(2) == HIGH); 
  }
}

void runTest(const char* label) {
  unsigned long start = micros();

  for (int i = 0; i < 50; i++) {
    Wire.beginTransmission(0x08);
    Wire.write(1); 
    Wire.endTransmission();

    Wire.requestFrom(0x08, 1);
    if (Wire.available()) {
      uint8_t state = Wire.read();
      if(state) PORTB |= (1 << PB0); else PORTB &= ~(1 << PB0);
    }
  }

  unsigned long duration = micros() - start;
  
  Serial.print(label);
  Serial.print(" total time: ");
  Serial.print(duration);
  Serial.println(" us");
}
