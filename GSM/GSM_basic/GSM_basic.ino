#define TINY_GSM_MODEM_SIM800
//#define SerialAT Serial2
#define SerialAT Serial1

#define debugSerial Serial





#include <TinyGsmClient.h>
#include <PubSubClient.h>

//
//
//#define MODEM_RST            5
//#define MODEM_PWKEY          4
//#define MODEM_POWER_ON       23
//#define MODEM_TX             17
//#define MODEM_RX             16

#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26




// Server details
const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";


// Your GPRS credentials (leave empty, if not needed)
const char apn[]      = "gpinternet"; // APN (example: internet.vodafone.pt) use https://wiki.apnchanger.org
const char gprsUser[] = ""; // GPRS User
const char gprsPass[] = ""; // GPRS Password

// SIM card PIN (leave empty, if not defined)
const char simPIN[]   = ""; 

//#define DUMP_AT_COMMANDS

TinyGsm modem(SerialAT);
//#ifdef DUMP_AT_COMMANDS
//#include <StreamDebugger.h>
//StreamDebugger debugger(Serial1, Serial);
//TinyGsm modem(debugger);
//#else
//TinyGsm modem(Serial1);
//#endif


TinyGsmClient gsmClient(modem);
const int      port = 80;

PubSubClient  simMqtt(gsmClient);

uint32_t lastReconnectAttempt = 0;


void simbegin()
{
    // Set modem reset, enable, power pins
    pinMode(MODEM_PWKEY, OUTPUT);
    pinMode(MODEM_RST, OUTPUT);
    pinMode(MODEM_POWER_ON, OUTPUT);
    digitalWrite(MODEM_PWKEY, LOW);
    digitalWrite(MODEM_RST, HIGH);
    digitalWrite(MODEM_POWER_ON, HIGH);

    // Set GSM module baud rate and UART pins
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    delay(3000);

    // Restart SIM800 module, it takes quite some time
    // To skip it, call init() instead of restart()
    debugSerial.println("Initializing modem...");
    modem.restart();

    String modemInfo = modem.getModemInfo();
    debugSerial.print("Modem Info: ");
    debugSerial.println(modemInfo);
}

/*boolean simMqttConnect() 
{
    debugSerial.print("Connecting to ");
    //  debugSerial.print(broker);

    // Connect to MQTT Broker
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    boolean status = mqtt.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS,will_feed,2,0,disconnect_msg);

    //  boolean status = mqtt.connect("GsmClientTest");

    // Or, if you want to authenticate MQTT:
    // boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");

    if (status == false) {
    debugSerial.println(" fail");
    return false;
    }

    debugSerial.println(" success");
    //  mqtt.subscribe(topicLed);
    return mqtt.connected();
}*/


bool isNetavailable()
{
    if (!modem.isNetworkConnected()) 
    {
        debugSerial.println("Network disconnected");
        return true;
    }
    if (!modem.waitForNetwork(180000L, true)) 
    {
      debugSerial.println(" fail");
      delay(10000);
    }
    if (modem.isNetworkConnected()) {
      debugSerial.println("Network re-connected");
      return true;
    }
    return false;
}


bool isGprsConnected()
{
    if (!modem.isGprsConnected()) {
        debugSerial.println("GPRS disconnected!");
        debugSerial.print(F("Connecting to "));
        debugSerial.print(apn);
        if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
            debugSerial.println(" fail");
            delay(10000);
        }
        if (modem.isGprsConnected()) 
        { 
            debugSerial.println("GPRS reconnected"); 
            return true;
        }
    }
    else
    {
        debugSerial.println("GPRS connected!");
        return true;
    }
    return false;
}


void webConnect()
{
  debugSerial.print("Connecting to ");
  debugSerial.println(server);
  if (!gsmClient.connect(server, port)) {
    debugSerial.println(" fail");
    delay(10000);
    return;
  }
  debugSerial.println(" success");

  // Make a HTTP GET request:
  debugSerial.println("Performing HTTP GET request...");
  gsmClient.print(String("GET ") + resource + " HTTP/1.1\r\n");
  gsmClient.print(String("Host: ") + server + "\r\n");
  gsmClient.print("Connection: close\r\n\r\n");
  gsmClient.println();

  uint32_t timeout = millis();
  while (gsmClient.connected() && millis() - timeout < 10000L) {
    // Print available data
    while (gsmClient.available()) {
      char c = gsmClient.read();
      debugSerial.print(c);
      timeout = millis();
    }
  }
  debugSerial.println();

  // Shutdown

  gsmClient.stop();
//  debugSerial.println(F("Server disconnected"));
  
}
void balanceCheck(){
  Serial.println("balance check");
  Serial.println(modem.sendUSSD("*566#"));
  Serial.println("Net check");
  Serial.println(modem.sendUSSD("*121*1*2#"));
  Serial.print("calling: ");
  Serial.println(modem.callNumber("+8801811177722"));
  
}


void setup()
{
  debugSerial.begin(115200);
  simbegin();  
  Serial.println("<----------- Device start -------------------->");
}

void loop()
{
  isNetavailable();
  delay(5000);
  isGprsConnected();
  delay(5000);
  webConnect();
  delay(5000);
  balanceCheck();
  delay(5000); 
 
}
