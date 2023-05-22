#include <Wire.h>

void setup() {
  Wire.begin(); // Initialize I2C bus
  Serial.begin(115200);
  Serial.println("start i2c master communication");
}

void loop() {
  Wire.beginTransmission(0x25); // Send message to slave at address 0x25
  Serial.println("sending hello slave");
  Wire.write("Hello, slave!"); // Send message
  Wire.endTransmission(); // End transmission
  delay(2000);
}
