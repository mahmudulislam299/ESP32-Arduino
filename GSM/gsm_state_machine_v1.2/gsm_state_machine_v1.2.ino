#include "sim800.h"

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
const int      port = 80;
gsmState_t gsmState;

void simBegin()
{  
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);
  gsmState = GSM_BEGIN;

}

void network()
{
  
}
void setup() 
{
  Serial.begin(115200);
 
  simBegin();

}

void loop() {

  switch(gsmState)
  {
    case GSM_BEGIN:
      Serial.println("<------------GSM loop Begin---------------------->");
      gsmState = GSM_NETWORK;
      break;

    case GSM_NETWORK:
      Serial.println("<------------Network check Begin---------------------->");
      if (!modem.isNetworkConnected()) 
      {
        SerialMon.println("Network disconnected");
        if (!modem.waitForNetwork(180000L, true)) 
        {
          SerialMon.println("...fail");
          SerialMon.println("[[[delay for network 10000]]]]");
          delay(10000);
          gsmState = GSM_NETWORK;
          break;
        }
        if (modem.isNetworkConnected()) 
        {
          SerialMon.println("Network re-connected");
        }
      }

      gsmState = GSM_GPRS;
      break;
    
    case GSM_GPRS:

      Serial.println("<------------GPRS check Begin---------------------->");
      // and make sure GPRS/EPS is still connected
      if (!modem.isGprsConnected()) 
      {
        SerialMon.println("GPRS disconnected!");
        SerialMon.print(F("Connecting to "));
        SerialMon.println(apn);
        if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
        {
          SerialMon.println("...fail");
          SerialMon.println("[[[delay for gprs 10000]]]]");
          delay(10000);
          gsmState = GSM_GPRS;
          break;
        }
        if (modem.isGprsConnected()) { SerialMon.println("GPRS reconnected"); }
      }
      gsmState = GSM_HTTP;
      break;

    case GSM_HTTP:
      Serial.println("<------------HTTP connect Begin---------------------->");
      
      SerialMon.print("Connecting to ");
      SerialMon.println(server);
      if (!client.connect(server, port)) {
        SerialMon.println("...fail");
        SerialMon.println("[[[delay for http client 10000]]]]");
        delay(10000);
        gsmState = GSM_HTTP;
        break;
      }
      SerialMon.println("...success");

      // Make a HTTP GET request:
      SerialMon.println("Performing HTTP GET request...");
      client.print(String("GET ") + resource + " HTTP/1.1\r\n");
      client.print(String("Host: ") + server + "\r\n");
      client.print("Connection: close\r\n\r\n");
      client.println();

      SerialMon.println("[***printing http***]");
      
      uint32_t timeout = millis();
      while (client.connected() && millis() - timeout < 10000L) {
        // Print available data
        while (client.available()) {
          char c = client.read();
          SerialMon.print(c);
          timeout = millis();
        }
      }
      SerialMon.println();

      // Shutdown
      
      client.stop();
      SerialMon.println(F("Server disconnected"));
      SerialMon.println(F("<-----------Loop finished--------------->"));
      
      gsmState = GSM_BEGIN;
      break;
    }
}
