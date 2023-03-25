//#define RXD1 9
//#define TXD1 10
#define RXD2 16
#define TXD2 17

// this is random pin for serial1 test
// this pin works fine for serial1
//#define RXD1 26 
//#define TXD1 27

// this another test pin for serial1 test
#define RXD1 12 
#define TXD1 13


void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
//  Serial1.begin(250000, SERIAL_8N1, RXD1, TXD1);
//  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    Serial2.begin(250000, SERIAL_8N1, RXD1, TXD1);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
}

void loop() { //Choose Serial1 or Serial2 as required
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }

//  while (Serial1.available()) {
//    Serial.print(char(Serial1.read()));
//  }
}
