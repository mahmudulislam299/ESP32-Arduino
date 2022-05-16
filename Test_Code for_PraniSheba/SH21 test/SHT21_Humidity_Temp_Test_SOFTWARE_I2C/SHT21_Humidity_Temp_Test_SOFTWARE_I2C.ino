#include <SHT21.h>  // include SHT21 library

SHT21 sht; 

float temp; 	// variable to store temperature
float humidity; // variable to store hemidity
uint8_t serialNumber;

void setup() {
  Serial.begin(115200); // begin Serial
  sht.begin(21,22);		// sda,scl begin Wire(I2C)
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop() {
//  serialNumber = sht.getSerialNumber(uint8_t return_sn)
  temp = sht.getTemperature();  // get temp from SHT 
  humidity = sht.getHumidity(); // get temp from SHT

  Serial.print("Temp: ");			// print readings
  Serial.print(temp);
  Serial.print("\t Humidity: ");
  Serial.println(humidity);

  delay(1000);	// min delay for 14bit temp reading is 85ms
}
