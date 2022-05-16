#include "radio.h"
#include "param.h"

uint8_t pipe0Addr[5] = {201,202,203,204,205};
uint8_t txLsByte;
nrfNodeConfig_t nrfConfig;
pong_t pong;


void radio_begin()
{

  nrfSetTimers(millis_esp32, second);   
  nrfSetPin( NRF_CE_PIN, NRF_CSN_PIN);   
  nrfSetDebug(true);   
  nrfBegin(SPEED_2MB, POWER_ZERO_DBM, SPI_SPEED);   
  nrfSetIrqs(txIsr, rxIsr, maxRtIsr);   
  
  nrfQryObj.pipe = QUERY_PIPE;   
  nrfQryObj.activePingAddr = pipe0Addr;   
  // nrfQryObj.pipeAddr = &pipeAddr;
  Serial.println((uint32_t)&nrfQryObj);
  nrfQueryBeginClient(&nrfQryObj);
   
  // nrfQueryClientSet(QUERY_PIPE, pipe0Addr);
  //nrfQueryBufferSet((uint8_t*)&queryBuffer, sizeof(queryData_t));

  //  nrfSetTx(pipeAddr[TX_PIPE], true);
  nrfPowerDown();
  Serial.println(F("Radio setup done"));
}

void radioStart()
{
  //  nrfStandby1();
  //  nrfTXStart(); //nrf goes standby-1
  pinMode(NRF_IRQ, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NRF_IRQ), nrfIrq, FALLING );
}
void txIsr(void)
{
//  nrfClearTxDs();
}

void rxIsr(void)
{
  Serial.println(F("RX IRQ"));
//  nrfClearRxDr();
}

void maxRtIsr(void)
{
//  nrfClearMaxRt();
  nrf_flush_rx();
  nrf_flush_tx();

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
