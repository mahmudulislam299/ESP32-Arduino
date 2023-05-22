#include <Wire.h>

void setup() {
  Wire.begin(0x50); // Set slave address to 0x25
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  Serial.println("slave start communication");
  
}

void loop() {
  delay(100);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
}
