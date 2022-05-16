#include "flash.h"
#include "./lib/FlashMemory/src/FlashMemory.h"
#include "param.h"

#define DEFAULT_ADDR 22

uint32_t addr = 0;
uint8_t buf[8]={1,2,3,4,5,6,7,8};
uint8_t readbuf[8]={5,5,5,5,5,6,6,6};
bool flashOk = true;

uint8_t pageBuf[256];


Flash flash(FLASH_CS,FLASH_HOLD);

// void read();
// void write();
// void eraseSector();
// void eraseAllChip();


void flashBegin()
{
  pinMode(FLASH_CS,OUTPUT);
//  pinMode(NRF_CSN_PIN,OUTPUT);
//  digitalWrite(NRF_CSN_PIN,HIGH);
  digitalWrite(FLASH_CS,HIGH); //HIGH
	flash.begin(FLASH_SPEED);
}


void flashCheck(int command) 
{
	switch(command)
	{
		case 1:
			read();
		break;
		case 2:
			write();
		break; 
		case 3:
			eraseSector();
		break;
    case 4:
      eraseAllChip();
    break;
	}
}

void flashCheckAuto() {
  read(true);
  eraseAllChip(true);
  bool checkFlash = write(true);
  read(true);
  eraseAllChip(true);
  if(checkFlash) {
    Serial.println("Flash OK");
  } else {
    Serial.println("Flash NoK");
  }

}


void read(bool automation)
{
 	
  if(automation) {
    addr =  DEFAULT_ADDR;

  } else{
    Serial.println("Enter addr to read");
    while(!Serial.available());
	  addr = Serial.parseInt();
	  Serial.print("Addr: ");
	  Serial.println(addr);
  }
	
	flash.read(addr, readbuf, 8);
	Serial.print("readBUF:  ");
	for(int i =0; i<8; i++) {
		Serial.print(readbuf[i]);
		Serial.print(" ");
	}
	Serial.println("");
  uint32_t curPage = addr>>8;
  Serial.print("current page: "); Serial.println(curPage);
  flash.dumpPage(curPage, pageBuf);
}

bool write(bool automation) {
  if(automation){
    addr = DEFAULT_ADDR;   

  } else {
    Serial.println("enter addr to write :");
    while(!Serial.available());
    addr = Serial.parseInt();
    Serial.print("Addr: ");
    Serial.println(addr);
  }
  
  for(int i =0; i<8; i++)
  {
    buf[i] = 2+i;
  }

  flash.write(addr, buf, 8);
  Serial.println("writing complete");
  flash.read(addr, readbuf, 8);
  Serial.print("readBUF:  ");
  for(int i =0; i<8; i++)
  {
    if(readbuf[i] != (2+i)){
      flashOk = false;
      break;
    }
    Serial.print(readbuf[i]);
    Serial.print(" ");
  }
  Serial.println("");
  
  // if(flashOk) {
  //   Serial.println("Flash OK");
  // } else {
  //   Serial.println("Flash NoK");
  // }

  if(!automation) {
    Serial.println("<< *** you must erase sector after test *** >>");
  }

  return flashOk;
}

void eraseSector(bool automation) {
  if(automation) {
    addr = DEFAULT_ADDR;

  } else {
    Serial.println("Enter addr to eraseSector: ");
    while(!Serial.available());
    addr = Serial.parseInt();
    Serial.print("Addr: ");
    Serial.println(addr);
  }
  flash.eraseSector(addr);
  uint32_t curPage = addr>>8;
  Serial.print("current page: "); Serial.println(curPage);
  flash.dumpPage(curPage, pageBuf);
}

void eraseAllChip(bool automation) {
  Serial.println("Erase full chip");
  flash.eraseChip();
}