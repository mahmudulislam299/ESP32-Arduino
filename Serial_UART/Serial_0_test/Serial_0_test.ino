#define RXD1 9
#define TXD1 10
#define RXD2 16
#define TXD2 17

int count = 0;
String buf="";
int serialAvail = 0;

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  Serial.println("Start Test Begin");

}

void loop() 
{
  //Choose Serial1 or Serial2 as required
  while (Serial.available()) 
  {
    if(count == 0) {serialAvail = Serial.available();}
    buf = buf + char(Serial.read());
//    Serial.println(buf);
    count++;
  }
  if(count>0)
  {
      Serial.println("");
      Serial.println(buf);
      count = 0;
      buf = "";
      Serial.println("");
      Serial.println("SerialAvial = " + serialAvail);
      Serial.println("");
  }
  
//  Serial.println(millis());
//  delay(10000);
//  Serial.println(millis());

  
}
