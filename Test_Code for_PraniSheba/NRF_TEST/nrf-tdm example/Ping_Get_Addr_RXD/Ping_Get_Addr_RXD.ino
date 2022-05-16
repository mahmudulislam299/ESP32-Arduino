#include "nRF24.h"
#include "nRF24_Query.h"
#include "TDM.h"
#include <EEPROM.h>

#define BOARD_GAS_SENSOR
//#define BOARD_GAS_SENSOR_V_0_2_0
//#define BOARD_TEST
//#define BOARD_BASE_STATION

#if defined(BOARD_GAS_SENSOR)
  #define NRF_CE_PORT   PORTB
  #define NRF_CE_PIN    PB2
  #define NRF_CSN_PORT  PORTB
  #define NRF_CSN_PIN   PB1
  #define NRF_IRQ_PIN   3
  #define BUS_FLASH_PIN 8
#elif defined(BOARD_TEST)
  #define NRF_CE_PORT   PORTB
  #define NRF_CE_PIN    PB1
  #define NRF_CSN_PORT  PORTB
  #define NRF_CSN_PIN   PB2
  #define NRF_IRQ_PIN   2
  #define BUS_FLASH_PIN 6
#elif defined(BOARD_BASE_STATION)
  #define NRF_CE_PORT   PORTB
  #define NRF_CE_PIN    PB2 
  #define NRF_CSN_PORT  PORTB
  #define NRF_CSN_PIN   PB1
  #define NRF_IRQ_PIN   2
  #define BUS_FLASH_PIN 5
#elif defined(BOARD_GAS_SENSOR_V_0_2_0)
  #define NRF_CE_PORT   PORTB
  #define NRF_CE_PIN    PB1
  #define NRF_CSN_PORT  PORTB
  #define NRF_CSN_PIN   PB0
  #define NRF_IRQ_PIN   2
  #define BUS_FLASH_PIN 6
#else
#error "Define a supported board"
#endif

void txIsr(void);
void rxIsr(void);
void maxRtIsr(void);
uint8_t *resolveQuery(uint8_t *queryPtr);
uint32_t sec();
uint8_t *getTxAddr();

#define QUERY_PIPE 0

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



uint8_t pipe0Addr[5]  = {230,1,0,5,3};
uint8_t commonAddr[5] = {2, 2, 3, 4, 5};
uint8_t pipe2Byte     =  3;
uint8_t pipe3Byte     =  4;
uint8_t pipe4Byte     =  5;
uint8_t pipe5Byte     =  6;

uint8_t temp[32];

query_t query;
queryData_t queryBuffer;

uint32_t packetCounter = 0;

/*------------TDM-----------------------*/

#define TDM_EEPROM_ADDR    200
#define MAX_NODE            10
#define MOMENT_SEC          60
#define RESERVE_NODE        2
#define TDM_BUF_SZ          (MAX_NODE*4+6+1)
void eepromUpdate(uint32_t addr, uint8_t *buf, uint16_t len);
void eepromRead(uint32_t addr, uint8_t *buf, uint16_t len);
volatile uint8_t tdmBuf[TDM_BUF_SZ];

void setup()
{
  Serial.begin(250000);
  pinMode(BUS_FLASH_PIN, OUTPUT);
  digitalWrite(BUS_FLASH_PIN , HIGH);

  tdmBegin((uint8_t *)tdmBuf, TDM_EEPROM_ADDR, eepromRead, eepromUpdate, 
           MOMENT_SEC, MAX_NODE, RESERVE_NODE);
  tdmReset();

  nrfSetTimers(millis,sec);
  nrfSetPin(&NRF_CE_PORT, NRF_CE_PIN, &NRF_CSN_PORT, NRF_CSN_PIN);
  nrfBegin(SPEED_2MB, POWER_ZERO_DBM, 1000000);

  nrfSetPipe(0, pipe0Addr, true);
  nrfSetPipe(1, commonAddr, true);
  nrfSetPipe(2, &pipe2Byte, true);
  nrfSetPipe(3, &pipe3Byte, true);
  nrfSetPipe(4, &pipe4Byte, true);
  nrfSetPipe(5, &pipe5Byte, true);
  nrfSetIrqs(txIsr, rxIsr, maxRtIsr);
  
  nrfQryObj.pipe = QUERY_PIPE;
  nrfQryObj.addr = pipe0Addr;
  nrfQryObj.bufPtr = (uint8_t*)&queryBuffer;
  nrfQryObj.len = sizeof(queryData_t);
  nrfQryObj.generateAddr = getTxAddr;
  nrfQryObj.resolver = resolveQuery;
  
  nrfQueryBegin(&nrfQryObj, BASE_STATION);
  nrfSetDebug(true);

  pinMode(NRF_IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NRF_IRQ_PIN), nrfIrq, FALLING );
  nrfPowerDown();
  nrfStandby1();
  nrfRxStart();    //goes to RX mode.
  Serial.println(F("RX Setup done"));
}

void loop()
{
  tdmUpdateSlot(sec());
}

void rxIsr(void)
{
  uint8_t pipe = pipeAvailFast();
  Serial.print(F("PIPE # : ")); Serial.println(pipe);
  int8_t nrfMaxRfBuffer = 3;//total rx buffer in nrf
  if (pipe < 6)
  {
    if (pipe != QUERY_PIPE)
    {
      do
      {
        nrfRead(temp, sizeof(temp));
        printBuffer(temp, sizeof(temp));
        //      nrfPrintRegisters();
      } while (!nrfIsRxEmpty() && --nrfMaxRfBuffer);
    }
    else
    {
//      Serial.println(F("Query ISR"));
      nrfRead((uint8_t*)&query, sizeof(query_t));
      nrfQueryHandler(&query);
    }
  }
}
void txIsr(void)
{
  nrfQryServerEnd(&query);
}
void maxRtIsr(void)
{
  nrf_flush_rx();
  nrf_flush_tx();
  nrfQryServerEnd(&query);
}

void printBuffer(uint8_t *buf, uint8_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    Serial.print(buf[i]); Serial.print(' ');
  }
  Serial.println();
}

uint8_t *resolveQuery(uint8_t *queryPtr)
{
  static uint32_t tm = 16342543;
  static uint16_t counter = 0;
  Serial.println(F("_______Resolving_query________"));
  Serial.print(F("Query Device : ")); Serial.print(query.type);
  Serial.print(F(" | Opcode :")); Serial.print(query.opcode);
  Serial.print(F(" | Counter :"));Serial.println(counter++);

  unixTime_t *ptr;
  ptr = (unixTime_t*)queryPtr;
  ptr -> utime = tm;
  tm++;
  return queryPtr;
}

uint32_t sec()
{
  static uint32_t tm = 16342543;
  Serial.println(F("sec called"));
//  return tm;
  return (tm +millis()/1000);
}


uint8_t *getTxAddr()
{
  return commonAddr;
}

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
    EEPROM.update(eepAddr + i, *(ptr + i));
    Serial.print( *(ptr + i)); Serial.print(F("  "));
  }
  Serial.println();
}