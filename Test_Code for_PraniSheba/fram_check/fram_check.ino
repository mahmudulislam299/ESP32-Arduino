#include "FM24I2C.h"

//FM24I2C fram(0x57);

char str1[]="12345678901234567890";
char str2[]="qwertyuiopasdfghjklzxcvbnm";
int a1=0x00;
int a2=0x40;
char buf1[80];
char buf2[80];

void setup() {
  Wire.begin();
  Serial.begin(115200);


  EEPROMUpdate(a1, (uint8_t *)str1, strlen(str1)+1);
  EEPROMUpdate(a2, (uint8_t *)str2, strlen(str2)+1);
  
}

void loop() {
//  // put your main code here, to run repeatedly:
//  fm.unpack(a2,buf,strlen(str2)+1);
//  Serial.println(buf);
//  fm.unpack(a1,buf,strlen(str1)+1);
//  Serial.println(buf);
//  delay(3000);

  EEPROMRead(a1,(uint8_t *)buf1, strlen(str1)+1);
  Serial.println(buf1);
  Serial.println();

  EEPROMRead(a2,(uint8_t *)buf2, strlen(str2)+1);
  Serial.println(buf2);
  Serial.println();

  delay(3000);
  

}


void EEPROMRead(uint32_t addr, uint8_t *buf, uint16_t len)
{

  uint16_t eepAddr = (uint16_t)addr;
  uint8_t *ptr = buf;
  Serial.print(F("EEPROM>R>: ")); Serial.println(eepAddr);
  fram.read(addr,(void *)buf,len);

  // Serial.println();
}

void EEPROMUpdate(uint32_t addr, uint8_t *buf, uint16_t len)
{

  uint16_t eepAddr = (uint16_t)addr;
  uint8_t *ptr = buf;
  Serial.print(F("EEPROM>W>: ")); Serial.println(eepAddr);

  fram.write(addr,(void *)buf,len);

  // Serial.println();
}
