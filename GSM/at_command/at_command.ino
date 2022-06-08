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



//#define SerialAT Serial2
//#define MODEM_RST            5
//#define MODEM_PWKEY          4
//#define MODEM_POWER_ON       23
//#define MODEM_TX             17
//#define MODEM_RX             16
//#define SERIAL_AT_BAUD_RATE  115200

#define SerialAT Serial1
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define SERIAL_AT_BAUD_RATE  115200

int state = 0;
int nextState = 0;
uint32_t prevMillis = 0;

enum
{
  GSM_1 = 1,
  GSM_2 = 2,
  GSM_3 = 3,
  GSM_4 = 4,
  GSM_5 = 5,
}State_t;


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
  Serial.begin(115200);
  
  //Begin serial communication with Arduino and SIM800L
  //  Serial2.begin(115200);
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);

  Serial.println("Initializing...");
  delay(1000);
  state = 1; //GSM_1;
  Serial.println("goint to " + state);

//  SerialAT.println("AT"); //Once the handshake test is successful, it will back to OK
//  updateSerial();
//  SerialAT.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
//  SerialAT.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
//  SerialAT.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
}

void loop()
{
  GSM_Func();
  updateSerial();
}

void updateSerial()
{
//  delay(500);
//  while (Serial.available()) 
//  {
//    SerialAT.write(Serial.read());//Forward what Serial received to Software Serial Port
//  }
  while(SerialAT.available()) 
  {
    Serial.write(SerialAT.read());//Forward what Software Serial received to Serial Port
  }
}


void GSM_Func()
{

  switch(state)
  {
    case GSM_1:
      SerialAT.println("AT");
      nextState = GSM_2;
      state = GSM_5;
      break;
    case GSM_2:
      SerialAT.println("AT+CSQ");
      nextState = GSM_3;
      state = GSM_5;
      break;
    case GSM_3:
      nextState = GSM_4;
      state = GSM_5;
      SerialAT.println("AT+CCID");
      break;
    case GSM_4:
      nextState = GSM_1;
      state = GSM_5;
      SerialAT.println("AT+CREG?");
      break;
    case GSM_5:
      if(millis() - prevMillis >10000)
      {
        prevMillis = millis();
        state = nextState;
        Serial.println("goint to next level");
      }
      break;
      
  }
}
