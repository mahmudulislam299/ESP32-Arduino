#define MODEM_RST            13
#define MODEM_PWKEY          100
#define MODEM_POWER_ON       102
#define MODEM_TX             14
#define MODEM_RX             12



// Select your modem:
#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SerialAT Serial2
//#define SerialAT mySerial
// #define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200



// Your GPRS credentials, if any
const char apn[]      = "gpinternet";
const char gprsUser[] = "";
const char gprsPass[] = "";


// Server details
const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";

#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
const int      port = 80;
uint32_t lastReconnectAttempt = 0;



void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
 
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);


//  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);


}

void loop() {

  Serial.println("<------------Network check Begin---------------------->");
  if (!modem.isNetworkConnected()) 
  {
    SerialMon.println("Network disconnected");
    if (!modem.waitForNetwork(180000L, true)) 
    {
      SerialMon.println(" fail");
      SerialMon.println("[[[delay for network 10000]]]]");
      delay(10000);
      return;
    }
    if (modem.isNetworkConnected()) 
    {
      SerialMon.println("Network re-connected");
    }

  }

  Serial.println("<------------GPRS check Begin---------------------->");
    // and make sure GPRS/EPS is still connected
    if (!modem.isGprsConnected()) 
    {
      SerialMon.println("GPRS disconnected!");
      SerialMon.print(F("Connecting to "));
      SerialMon.print(apn);
      if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
      {
        SerialMon.println(" fail");
        SerialMon.println("[[[delay for gprs 10000]]]]");
        delay(10000);
        return;
      }
      if (modem.isGprsConnected()) { SerialMon.println("GPRS reconnected"); }
    }

//  }

  Serial.println("<------------HTTP connect Begin---------------------->");
  
  SerialMon.print("Connecting to ");
  SerialMon.println(server);
  if (!client.connect(server, port)) {
    SerialMon.println(" fail");
    SerialMon.println("[[[delay for http client 10000]]]]");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

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
  
}
