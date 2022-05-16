/*
 * https://lastminuteengineers.com/sim800l-gsm-module-arduino-tutorial/
 * 
 * 
 * Keep both NL & CR in serial monitor
 * 
 * 
 * AT – It is the most basic AT command. It also initializes Auto-baud’er. If it works you should see the AT characters echo and then OK, telling you it’s OK and it’s understanding you correctly! You can then send some commands to query the module and get information about it such as
 * AT+CSQ – Check the ‘signal strength’ – the first # is dB strength, it should be higher than around 5. Higher is better. Of course it depends on your antenna and location!
 * AT+CCID – get the SIM card number – this tests that the SIM card is found OK and you can verify the number is written on the card.
 * AT+CREG? Check that you’re registered on the network. The second # should be 1 or 5. 1 indicates you are registered to home network and 5 indicates roaming network. Other than these two numbers indicate you are not registered to any network
 * ATI – Get the module name and revision
 * AT+COPS? – Check that you’re connected to the network
 * AT+COPS=? – Return the list of operators present in the network.
 * AT+CBC – will return the lipo battery state. The second number is the % full (in this case its 93%) and the third number is the actual voltage in mV (in this case, 3.877 V)
 */

//#include <SoftwareSerial.h>
#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <PubSubClient.h>
#include <ArduinoHttpClient.h>


const char apn[]      = "gpinternet"; //"gpinternet"; //WAP
const char gprsUser[] = "";
const char gprsPass[] = "";


#define MODEM_RST            5
#define MODEM_PWKEY          100
#define MODEM_POWER_ON       101
#define MODEM_TX             17
#define MODEM_RX             16
#define SERIAL_AT_BAUD_RATE  38400

//Create software serial object to communicate with SIM800L
//SoftwareSerial Serial2(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

//  Serial2.begin(SERIAL_AT_BAUD_RATE, SERIAL_8N1, MODEM_RX, MODEM_TX);
  
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println("Initializing modem...");
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  Serial2.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  Serial2.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial2.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  Serial2.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  Serial2.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial2.available()) 
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}
