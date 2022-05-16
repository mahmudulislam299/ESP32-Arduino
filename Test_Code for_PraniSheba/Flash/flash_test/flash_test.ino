#include "FlashMemory.h"

#define FLASH_CS 16//15//26
#define FLASH_HOLD 17//2
#define FLASH_SPEED 1000000  //1000000

#define NRF_CSN_PIN 12

uint32_t addr = 0;
uint8_t buf[8]={1,2,3,4,5,6,7,8};
uint8_t readbuf[8]={5,5,5,5,5,6,6,6};
uint8_t commandNo;

uint8_t pageBuf[256];


Flash flash(FLASH_CS,FLASH_HOLD);

void gpioBegin()
{
  pinMode(FLASH_CS,OUTPUT);
//  pinMode(NRF_CSN_PIN,OUTPUT);
//  digitalWrite(NRF_CSN_PIN,HIGH);
  digitalWrite(FLASH_CS,HIGH); //HIGH
}

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  gpioBegin();
  flash.begin(FLASH_SPEED);

//  Serial.println("erasing...........");
//  flash.eraseSector(0);
  instruction();

}

void loop() 
{
  if (Serial.available() > 0)
  {
    commandNo = Serial.parseInt();

    switch(commandNo)
    {
      case 1:
      instruction();
      break;
  
      case 2:
        read();
//          Serial.println("Enter addr to read");
//          while(!Serial.available());
//          addr = Serial.parseInt();
//          Serial.print("Addr: ");
//          Serial.println(addr);
//          flash.read(addr, readbuf, 8);
//          Serial.print("readBUF:  ");
//          for(int i =0; i<8; i++)
//          {
//            Serial.print(readbuf[i]);
//            Serial.print(" ");
//          }
//          Serial.println("");
  instruction();
      break;
      case 3:
        write(); 
      break;
      case 4:
        erase();
       break;
    }

  }

  
}

void instruction()
{
  Serial.println("-------------------");
  Serial.println("1. Enter 2 to read");
  Serial.println("2. Enter 3 to write");
  Serial.println("2. Enter 4 to erase sector");
  Serial.println("-------------------");
}

void read()
{
  Serial.println("Enter addr to read");
  while(!Serial.available());
  addr = Serial.parseInt();
  Serial.print("Addr: ");
  Serial.println(addr);
  flash.read(addr, readbuf, 8);
  Serial.print("readBUF:  ");
  for(int i =0; i<8; i++)
  {
  Serial.print(readbuf[i]);
  Serial.print(" ");
  }
  Serial.println("");
}

void write()
{
  Serial.println("enter addr to write");
  while(!Serial.available());
  addr = Serial.parseInt();
  Serial.print("Addr: ");
  Serial.println(addr);
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
    Serial.print(readbuf[i]);
    Serial.print(" ");
  }
  Serial.println("");
  instruction();
}

void erase()
{
  Serial.println("Enter addr to erase");
  while(!Serial.available());
  addr = Serial.parseInt();
  Serial.print("Addr: ");
  Serial.println(addr);
  flash.eraseSector(addr);
  uint32_t curPage = addr>>8;
  Serial.print("current page: "); Serial.println(curPage);
  flash.dumpPage(curPage, pageBuf);
  instruction();

}
