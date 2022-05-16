#include <Wire.h>

/* 
 *  Special Note:
 *  I2C2 is very much slow...........
 */
//set pins for I2C1
#define I2C1_SDA_PIN 21
#define I2C1_SCL_PIN 22

//set pin for I2C2
#define I2C2_SDA_PIN 5
#define I2C2_SCL_PIN 4

TwoWire I2C1 = TwoWire(0); //I2C1 bus
TwoWire I2C2 = TwoWire(1); //I2C2 bus

#define SPEED 100000u

void setup() 
{
//  Wire.begin();
  I2C1.begin(I2C1_SDA_PIN, I2C1_SCL_PIN,SPEED);
  I2C2.begin(I2C2_SDA_PIN, I2C2_SCL_PIN,SPEED);
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}
 
void loop() 
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning... [I2C1]");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Serial.print("addrs :"); Serial.println(address);
    I2C1.beginTransmission(address);
    error = I2C1.endTransmission();
    if (error == 0) 
    {
      Serial.print("I2C1 device found at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.print(address,HEX);
      Serial.print("  |  ");
      Serial.println(address);
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) 
  {
    Serial.println("No I2C1 devices found\n");
  }
  else 
  {
    Serial.print("no of I2C1 device is : ");
    Serial.println(nDevices);
    Serial.println("done\n");
  }
  delay(10000); 

/*******************************I2c********************/

  Serial.println("Scanning... [I2C2]");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Serial.print("addrs :"); Serial.println(address);
    I2C2.beginTransmission(address);
    error = I2C2.endTransmission();
    if (error == 0) 
    {
      Serial.print("I2C2 device found at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.print(address,HEX);
      Serial.print("  |  ");
      Serial.println(address);
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
      {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) 
  {
    Serial.println("No I2C2 devices found\n");
  }
  else 
  {
    Serial.print("no of I2C2 device is : ");
    Serial.println(nDevices);
    Serial.println("done\n");
  }
  delay(10000); 
}
