#include "memq.h"
#include "FlashMemory.h"
#include "RingEEPROM.h"
#include "Serial.h"

#define FLASH_CS  26
#define OTHER_CS 12 //consider other spi device is connected in bus
#define RING_EEPROM_ADDR  0
#define RING_BUF_LEN      4

#define TIMER_INTERVAL 1

Flash flash(FLASH_CS);
RingEEPROM ringObj(RING_EEPROM_ADDR);
uint8_t pageBuf[256];


volatile int i,prev_i;
int totali;
 
hw_timer_t * timer = NULL;
//portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 



typedef struct 
{
  uint32_t value[8];
}payload_t;

payload_t pldWrite;
payload_t pldRead;
struct memq_t memq;

void IRAM_ATTR onTimer() 
{
//  portENTER_CRITICAL_ISR(&timerMux);
  i= i + TIMER_INTERVAL;
//  Serial.println(i);
//  portEXIT_CRITICAL_ISR(&timerMux);
}


void setup()
{
  Serial.begin(9600);
  SerialBegin(9600);
  
  Serial.println(F("Setup Done"));
  timerbegin();
  flash.begin();
  ringObj.begin(RING_BUF_LEN, sizeof(struct memqPtr_t)); //begin eeprom.
  
  memqBegin(&memq, 0, sizeof(payload_t), 360);Serial.println(F("[T1]"));
  memqSetMem(&memq, memReader, memWriter, memEraser, 4096);Serial.println(F("[T2]"));
  memqAttachBusSafety(&memq, enableOthersOnbus,disableOthersOnbus);Serial.println(F("[T3]"));
  memqSetMemPtr(&memq, memPtrReader, memPtrWriter,10);Serial.println(F("[T4]"));
  memqReset(&memq);Serial.println(F("[T5]"));

}

void loop()
{
  printtime();
  uint8_t cmd = getSerialCmd();
  
  if (cmd == 1)
  {
    generatePld(&pldWrite);
    memqWrite(&memq, (uint8_t*)&pldWrite); //writing single data point
    printPld(&pldWrite);
    uint32_t curPage = (memq.ringPtr._head)>>8;
    flash.dumpPage(curPage, pageBuf);
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
  Serial.println("memReader");
  
//  flash.read(addr, buf, sizeof(payload_t));
  flash.read(addr, buf, len);
  Serial.println("memReader end");
}

void memWriter(uint32_t addr, uint8_t *buf, uint16_t len)
{
//  uint8_t *flashPtr = (uint8_t*)&dataStruct + (uint16_t)addr;
//  memcpy(flashPtr, buf, len);
//  flash.write(addr,buf,sizeof(payload_t));
  flash.write(addr,buf,len);
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
  Serial.println(F("MemQPtr Reader called end"));
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
  int cmd;
  if(Serial.available()>0)
  {
    Serial.print(F("Input cmd: "));
    cmd = Serial.parseInt();
    Serial.println(cmd);
    Serial.println(F("------------------------------"));
    return cmd;
  }
  else
  {
    return 0;
  }
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

void timerbegin()
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_INTERVAL*1000000, true);
  timerAlarmEnable(timer);
}


void printtime()
{
    if(i!=prev_i)
  {
    Serial.print("sec: "); Serial.println(i);
    prev_i = i;
  }
}
