#include <EEPROM.h>

int addr=0;
uint8_t data[5]={11,12,13,14,15}, readData[5], *ptr,*ptr2;
float f= 12.5, readf;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512); //max size 4kB(4096byte) we are using 512 byte
  delay(500);
  ptr = (uint8_t*)&f;
  ptr2 = (uint8_t*)&readf;
  for(int i=0; i<sizeof(f); i++)
  {
//    EEPROM.write(i, *ptr);
//    EEPROM.commit();
    *ptr2= EEPROM.read(i);
    ptr++; ptr2++;
  }
  Serial.println(readf);
 
}

void loop() 
{

  for(int i=0; i<sizeof(f); i++)
  {
//    EEPROM.write(i, *ptr);
    *ptr2= EEPROM.read(i);
    ptr++; ptr2++;
  }
  Serial.println(readf);
  delay(1000);

}
