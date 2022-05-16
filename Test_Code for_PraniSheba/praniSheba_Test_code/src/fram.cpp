#include "fram.h"

#include "./lib/FM24I2C/FM24I2c.h"


char str1[21]="12345678901234567890";
char str2[27]="qwertyuiopasdfghjklzxcvbnm";
int a1=0x00;
int a2=0x40;
char buf1[80];
char buf2[80];
bool framOk = true;

void EEPROMRead(uint32_t addr, uint8_t *buf, uint16_t len);
void EEPROMUpdate(uint32_t addr, uint8_t *buf, uint16_t len);


void framInit() {
  Wire.begin();
  
  
}

void framLoop() {

	// for (int i = 0; i< strlen(str1) + 1 ; i++) {
	// 	byte randomValue = random(0, 24);
	// 	str1[i] = randomValue + 'A';
	// }
	// Serial.println(str1);

	// for (int i = 0; i< strlen(str2) + 1 ; i++) {
	// 	byte randomValue = random(0, 9);
	// 	str2[i] = random(0,9) + '0';
	// }
	// Serial.println(str2);

	EEPROMUpdate(a1, (uint8_t *)str1, strlen(str1)+1);
  EEPROMUpdate(a2, (uint8_t *)str2, strlen(str2)+1);

	delay(200);

  EEPROMRead(a1,(uint8_t *)buf1, strlen(str1)+1);
  Serial.println(buf1);
  Serial.println();

  EEPROMRead(a2,(uint8_t *)buf2, strlen(str2)+1);
  Serial.println(buf2);
  Serial.println();

	for (int i = 0; i< strlen(str1) + 1 ; i++) {
		if (buf1[i] != str1[i]) {
			framOk = false;
			break;
		}
	}

	for (int i = 0; i< strlen(str2) + 1 ; i++) {
		if (buf2[i] != str2[i]) {
			framOk = false;
			break;
		}
	}

	if(framOk) {
		Serial.println("Restult: FRAM OK---------------->");
	} else {
		Serial.println("Restult: FRAM Not OK ---------------->");
	}
  

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

// char bb[] = {"QWERTYUIOPASDFGHJKLZXCVBNM"};



void randomArray() 
{
//   Serial.println(bb[random(0, 25)]);
// 	Serial.println(bb);
//   delay(1000);
}