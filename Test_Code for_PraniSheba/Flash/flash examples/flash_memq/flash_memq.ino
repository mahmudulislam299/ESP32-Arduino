#include "memq.h"
#include "FlashMemory.h"
#include "RingEEPROM.h"
#include "Serial.h"

#define FLASH_CS  26
#define FLASH_HOLD 2
#define NRF_CSN_PIN 12 //consider other spi device is connected in bus
#define RING_EEPROM_ADDR  0
#define RING_BUF_LEN      4

#define FLASH_SPEED 1000000  //1000000

Flash flash(FLASH_CS,FLASH_HOLD);
RingEEPROM ringObj(RING_EEPROM_ADDR);
uint8_t pageBuf[256];

typedef struct payload_t
{
  uint32_t value[8];
};

payload_t pldWrite;
payload_t pldRead;
struct memq_t memq;

void gpioBegin()
{
  pinMode(FLASH_CS,OUTPUT);
  pinMode(NRF_CSN_PIN,OUTPUT);
  digitalWrite(NRF_CSN_PIN,HIGH);
  digitalWrite(FLASH_CS,HIGH); //HIGH
}

void setup()
{
  Serial.begin(9600);
  SerialBegin(9600);
  Serial.println(F("Setup Done"));
  gpioBegin();
  flash.begin(FLASH_SPEED);
  ringObj.begin(RING_BUF_LEN, sizeof(struct memqPtr_t)); //begin eeprom.

  memqBegin(&memq, 0, sizeof(payload_t), 360);
  memqSetMem(&memq, memReader, memWriter, memEraser, 4096);
  memqAttachBusSafety(&memq, enableOthersOnbus,disableOthersOnbus);
  memqSetMemPtr(&memq, memPtrReader, memPtrWriter,10);

//  memqReset(&memq);

}

void loop()
{
  uint8_t cmd = getSerialCmd();
  Serial.println(F("------------------------------"));
  if (cmd == 1)
  {
    Serial.println("c1");
    generatePld(&pldWrite);Serial.println("c2");
    memqWrite(&memq, (uint8_t*)&pldWrite); Serial.println("c3");//writing single data point
    printPld(&pldWrite);Serial.println("c4");
    uint32_t curPage = (memq.ringPtr._head)>>8;Serial.println("c5");
    flash.dumpPage(curPage, pageBuf);Serial.println("c6");
    Serial.print(F("Counter : "));Serial.println(memq._ptrEventCounter);
  }
  else if (cmd == 2)
  {
    memqRead(&memq, (uint8_t*)&pldRead);
    printPld(&pldRead);
    Serial.print(F("Counter : "));Serial.println(memq._ptrEventCounter);
  }
  memqSaveMemPtr(&memq);
}

void memReader(uint32_t addr, uint8_t *buf, uint16_t len)
{
//  uint8_t *flashPtr = (uint8_t*)&dataStruct + (uint16_t)addr;
//  memcpy(buf, flashPtr, len);
  
  flash.read(addr, buf, sizeof(payload_t));
}

void memWriter(uint32_t addr, uint8_t *buf, uint16_t len)
{
//  uint8_t *flashPtr = (uint8_t*)&dataStruct + (uint16_t)addr;
//  memcpy(flashPtr, buf, len);
  flash.write(addr,buf,sizeof(payload_t));
}
void memEraser(uint32_t addr, uint16_t len)
{
//  uint8_t *flashPtr = (uint8_t*)&dataStruct + (uint16_t)addr;
//  memset(flashPtr, 0, len);
 flash.eraseSector(addr);
 uint32_t curPage = addr>>8;
 flash.dumpPage(curPage, pageBuf);
}

void memPtrReader(memqPtr_t *ptr)
{
  Serial.println(F("MemQPtr Reader called"));
//  memcpy(ptr, &ring, sizeof(memqPtr_t));
  ringObj.readPacket((byte *)ptr); 
}

void memPtrWriter(memqPtr_t *ptr)
{
  Serial.println(F("MemQPtr Writer called"));
   ringObj.savePacket((byte *)ptr);
  //memcpy(&ring, ptr, sizeof(memqPtr_t));
}

void printBuffer(uint8_t *buf, uint8_t len)
{
  Serial.print(F("Buffer :"));
  for (uint8_t i = 0; i < len; i++)
  {
    Serial.print(*(buf + i));
    Serial.print(F("  "));
  }
  Serial.println();
}

uint8_t getSerialCmd()
{
  Serial.print(F("Input Cmd :"));
  while (!Serial.available())
  {
    delay(10);
  }
  int cmd = Serial.parseInt();
  Serial.println(cmd);
  return cmd;
}

void generatePld(payload_t *pld)
{
  static uint32_t data;
  for(uint8_t i = 0; i< 8; i++)
  {
    pld ->value[i] = ++data;
  }
}
void printPld(payload_t *pld)
{
  Serial.print(F("Payload :"));
  for(uint8_t i = 0; i<8 ; i++)
  {
    Serial.print(pld -> value[i]);Serial.print(F("  "));
  }
  Serial.println();
}

void disableOthersOnbus()
{
  Serial.println(F("Disable others on bus"));
}

void enableOthersOnbus()
{
  Serial.println(F("Enable others on bus"));
}
