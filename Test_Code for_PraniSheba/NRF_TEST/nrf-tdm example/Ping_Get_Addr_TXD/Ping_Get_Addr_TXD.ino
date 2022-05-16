#include "nRF24.h"
#include "nRF24_Query.h"
#include "nRF24_Qry_Common.h"
#include "EEPROM.h"

/*--------------- DEVICE CONFIG-----------------*/
#define DEVICE_ID 100
#define NRF_CONFIG_ROM_ADDR 10
#define SYNC_PING_DELAY_MS 5000


#define NRF_CE_PIN 14
#define NRF_CSN_PIN 12
#define NRF_IRQ 15
#define FLASH_CS 26
#define FLASH_HOLD 2


#define ROM_ADDR_FOR_TXD  10
#define PAYLOAD_LEN 32
#define QUERY_PIPE 0

void txIsr(void);
void rxIsr(void);
void maxRtIsr(void);
void eepromUpdate(uint32_t addr, uint8_t *buf, uint16_t len);
void eepromRead(uint32_t addr, uint8_t *buf, uint16_t len);


typedef struct unixTime_t
{
  uint8_t type;
  uint8_t opCode;
  uint32_t utime;
};
typedef union queryData_t
{
  unixTime_t unixTime;
};


uint8_t payload[PAYLOAD_LEN];

uint8_t pipe0Addr[5] = {201,202,203,204,205};
uint8_t txLsByte;
uint8_t txAddr[5];
queryData_t queryBuffer;

uint32_t packetCounter = 0;

uint32_t waitPrevMillis = 0;

/*--------------------TDM-------------------*/
nrfNodeConfig_t nrfConfig;
volatile uint32_t _nextSlotSec;

bool rfConfig();
uint32_t calcNextSlotUnix(uint32_t uSec, nrfNodeConfig_t *conf);
uint32_t sec();


void setup()
{
  Serial.begin(250000);
  pinMode(BUS_FLASH_PIN, OUTPUT);
  digitalWrite(BUS_FLASH_PIN , HIGH);
   EEPROM.begin(4096);

  nrfSetTimers(millis_esp32, second);   
  nrfSetPin( NRF_CE_PIN, NRF_CSN_PIN);   
  nrfSetDebug(true);   
  nrfBegin(SPEED_2MB, POWER_ZERO_DBM, SPI_SPEED);   
  nrfSetIrqs(txIsr, rxIsr, maxRtIsr);   
  
//    nrfTxBegin(pipe0Addr, true);
  nrfQryObj.pipe = QUERY_PIPE;
  nrfQryObj.addr = pipe0Addr;
//  nrfQueryClientSet(QUERY_PIPE, pipe0Addr);
//  nrfQueryBufferSet((uint8_t*)&queryBuffer, sizeof(queryData_t));
  nrfQueryBegin(&nrfQryObj, SENSOR_NODE);


  pinMode(NRF_IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NRF_IRQ_PIN), nrfIrq, FALLING );
  delay(2000);

  nrfPowerDown();
  nrfStandby1();
  nrfTXMode();
  Serial.println("TX Setup Done");
}

void loop()
{
//  getQry();
   nrfPing();
   delay(1000);
   rfConfig();
//   nrfTxAddrHandler(readAddr,saveAddr);
//   nrfGetAddr(txAddr,sizeof(txAddr));
//   Serial.print(F("TX Addr : ")); 
//   nrfPrintBuffer(txAddr,sizeof(txAddr));
  //  generateData(payload);
  //  printBuffer(payload,32);
  //  bool ok = nrfAckSend(payload,32);
  //  Serial.print(F("NRF Send : "));Serial.println(ok);
  delay(5000);
}


bool rfConfig()
{
  bool conOk = nrfTxConfigHandler(DEVICE_ID, &nrfConfig, NRF_CONFIG_ROM_ADDR, eepromRead, eepromUpdate);
  if (conOk)
  {

    _nextSlotSec = calcNextSlotUnix(sec(), &nrfConfig);
    //    setNextSlotSec(slotSec);
    return conOk;
  }
  else
  {
    delay(SYNC_PING_DELAY_MS);// ping after 2s interval
  }

}

uint32_t sec()
{
  static uint32_t tm = 16342543;
  Serial.println(F("sec called"));
//  return tm;
  return (tm +millis()/1000);
}


uint32_t calcNextSlotUnix(uint32_t uSec, nrfNodeConfig_t *conf)
{
  uint16_t slotSec = (conf -> perNodeInterval) * (conf -> slotId);
  uint16_t curMoment = uSec % conf->momentDuration;

  uint32_t nexSlotSec;
  if (curMoment < slotSec)
  {
    nexSlotSec = uSec + (slotSec - curMoment);
  }
  else
  {
    nexSlotSec = uSec + (conf->momentDuration - curMoment) + slotSec;
  }
  Serial.print(F("curMoment :")); Serial.println(curMoment);
  Serial.print(F("======>>>>>next slot unix :")); Serial.println(nexSlotSec);
  return nexSlotSec;
}

void txIsr(void)
{
//  nrfClearTxDs();
}

void rxIsr(void)
{
//  nrfClearRxDr();
}

void maxRtIsr(void)
{
//  nrfClearMaxRt();
  nrf_flush_rx();
  nrf_flush_tx();

}

void generateData(uint8_t *buf)
{
  uint8_t *p = buf;
  for (uint8_t i = 0; i < PAYLOAD_LEN; i++)
  {
    p[i] = random(100, 250);
  }
}

void printBuffer(uint8_t *buf, uint8_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    Serial.print(buf[i]); Serial.print(' ');
  }
  Serial.println();
}

/*
void getQry()
{
  memset(&queryBuffer, 0, sizeof(queryData_t));
  nrfStandby1();
  nrfTxStart();
  unixTime_t *uPtr = (unixTime_t*)nrfQuery(0, 3,&queryBuffer,sizeof(queryBuffer));
  if (uPtr != NULL)
  {
    Serial.println(uPtr -> utime);
  }
  else
  {
    Serial.println(F("return null"));
  }
}
*/
void eepromRead(uint32_t addr, uint8_t *buf, uint16_t len)
{
  uint16_t eepAddr = (uint16_t)addr;
  uint8_t *ptr = buf;
  Serial.print(F("EEPROM Reading Addr : ")); Serial.println(eepAddr);
  for (uint16_t i = 0 ; i < len; i++)
  {
    *(ptr + i) = EEPROM.read(eepAddr + i);
    Serial.print( *(ptr + i)); Serial.print(F("  "));
  }
  Serial.println();
}

void eepromUpdate(uint32_t addr, uint8_t *buf, uint16_t len)
{
  uint16_t eepAddr = (uint16_t)addr;
  uint8_t *ptr = buf;
  Serial.print(F("EEPROM Update Addr : ")); Serial.println(eepAddr);
  for (uint16_t i = 0; i < len; i++)
  {
    EEPROM.write(eepAddr + i, *(ptr + i));
    Serial.print( *(ptr + i)); Serial.print(F("  "));
  }
  EEPROM.commit();
  Serial.println();
}

uint32_t millis_esp32()
{
  uint32_t t = millis();
  return t;
}

uint32_t second()
{
  uint32_t t = millis()/1000;
  return t;
}
