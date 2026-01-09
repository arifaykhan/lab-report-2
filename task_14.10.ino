const uint8_t cipher[] = { 87, 26, 72, 13, 67, 95, 89, 23, 72, 22, 73, 11, 87, 30, 73 };
const uint8_t cipherLen = sizeof(cipher);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("Starting Brute Force...");
  unsigned long startTime = millis();

  for (int k0 = 0; k0 < 256; k0++) {
    for (int k1 = 0; k1 < 256; k1++) {
      
      char candidate[cipherLen + 1];
      bool isValid = true;
      int spaces = 0;

      for (uint8_t i = 0; i < cipherLen; i++) {
        uint8_t currentKey = (i % 2 == 0) ? k0 : k1;
        char p = (char)(cipher[i] ^ currentKey);
        
        if ((p >= 'a' && p <= 'z') || p == ' ') {
          if (p == ' ') spaces++;
          candidate[i] = p;
        } else {
          isValid = false;
          break; 
        }
      }

      if (isValid && spaces == 1 && candidate[0] != ' ' && candidate[cipherLen-1] != ' ') {
        candidate[cipherLen] = '\0';
        
        Serial.print("Found! Key0: 0x"); Serial.print(k0, HEX);
        Serial.print(" Key1: 0x"); Serial.print(k1, HEX);
        Serial.print(" -> "); Serial.println(candidate);
      }
    }
  }

  Serial.print("Finished in ");
  Serial.print(millis() - startTime);
  Serial.println(" ms.");
}

void loop() {
  // put your main code here, to run repeatedly;
}
