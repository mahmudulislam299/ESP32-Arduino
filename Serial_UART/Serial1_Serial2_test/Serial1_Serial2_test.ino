#define RXD1 9
#define TXD1 10
#define RXD2 16
#define TXD2 17

#define SERIAL0_SPEED 115200
#define SERIAL1_SPEED 115200
#define SERIAL2_SPEED 115200

//#define ACTIVE_SERIAL1
#define ACTIVE_SERIAL2

void setup() 
{
  
  Serial.begin(SERIAL0_SPEED);

  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  
#if defined(ACTIVE_SERIAL1)
  Serial1.begin(SERIAL1_SPEED, SERIAL_8N1, RXD1, TXD1);
#elif defined(ACTIVE_SERIAL2)
  Serial2.begin(SERIAL2_SPEED, SERIAL_8N1, RXD2, TXD2);
#else
  #error "No Serial Selected"
#endif
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
}

void loop() 
{ 
#if defined(ACTIVE_SERIAL1)
while (Serial1.available()) 
  {
    Serial.print(char(Serial1.read()));
  }

#elif defined(ACTIVE_SERIAL2)
  while (Serial2.available()) 
  {
    Serial.print(char(Serial2.read()));
  }
#else
  #error "No Serial Selected"
#endif

}
