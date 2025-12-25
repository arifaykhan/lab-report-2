#include <Wire.h>

volatile byte state = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  digitalWrite(13, state);
}

void receiveEvent(int bytes) {
  if (Wire.available()) {
    state = Wire.read();
  }
}

void requestEvent() {
  byte btn = (digitalRead(2) == LOW) ? 1 : 0;
  Wire.write(btn);
}
