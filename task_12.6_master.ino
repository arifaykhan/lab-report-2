#include <Wire.h>

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  Wire.begin(); 

  // --- MANUAL SPEED CONFIGURATION (Uncomment the one you are testing) ---
  
  // 25 kHz (Slow Mode): TWPS = 1 (Prescaler 4), TWBR = 72
  // TWSR |= (1 << TWPS0); 
  // TWBR = 72;

  // 100 kHz (Standard Mode): TWPS = 0 (Prescaler 1), TWBR = 72
  // TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); 
  // TWBR = 72;

  // 400 kHz (Fast Mode): TWPS = 0 (Prescaler 1), TWBR = 12
  TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); 
  TWBR = 12;

  // --- START TIMING TEST ---
  unsigned long start = millis();
  
  for (int i = 0; i < 50; i++) {
    // Write 1 byte
    Wire.beginTransmission(0x08);
    Wire.write(0x01);
    Wire.endTransmission();
    
    // Read 1 byte
    Wire.requestFrom(0x08, 1);
    while(Wire.available()) {
      Wire.read();
    }
  }
  
  unsigned long duration = millis() - start;
  Serial.print("Time for 50 messages: ");
  Serial.print(duration);
  Serial.println(" ms");
}

void loop() {}
