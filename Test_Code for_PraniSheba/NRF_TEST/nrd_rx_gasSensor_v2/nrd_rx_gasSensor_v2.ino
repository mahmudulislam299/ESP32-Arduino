 #include "nRF24.h"
 #include "nRF24_Client.h"
 #include "nRF24_Qry_Common.h"
    
 #define NRF_CE_PIN 14
 #define NRF_CSN_PIN 12
 #define NRF_IRQ 15
 #define FLASH_CS 26
 #define FLASH_HOLD 2

 #define TX_PIPE      5
 #define QUERY_PIPE   0

 #define SPI_SPEED 1000000UL

 #define TIMER_INTERVAL 1
volatile int i,prev_i;
hw_timer_t * timer = NULL;


 void txIsr(void);
 void rxIsr(void);
 void maxRtIsr(void);

 uint8_t pipe0Addr[5] = {201,202,203,204,205};
 uint8_t txLsByte;
 nrfNodeConfig_t nrfConfig;
 pong_t pong;

void IRAM_ATTR onTimer() 
{
  i= i + TIMER_INTERVAL;
//  Serial.print("t:"); 
//  Serial.println(i);
}


 void radio_begin()
 {
   int n=1;
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

void gpioBegin()
{
  pinMode(FLASH_CS,OUTPUT);
  digitalWrite(FLASH_CS,HIGH);
  
  
}

void setup()
{
  Serial.begin(250000);
  SerialBegin(115200);
  gpioBegin();
  Serial.println("gpio begin");
  timerbegin();

  radio_begin();
  radioStart();
  Serial.println("radio setup done");
}

void loop()
{
  Serial.println("nrf ping start");
  Serial.print("ping: ");Serial.println(nrfPing());
  delay(5000);

  Serial.println("pingSlot");
  uint32_t uTime = nrfPingSlot(2030, 0, &pong); //device id, slot id, &pong
  Serial.println(uTime);

  delay(5000);
  
  Serial.println("\n");
}
