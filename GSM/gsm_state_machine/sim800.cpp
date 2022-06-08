#include "sim800.h"

// const char server[]   = "vsh.pp.ua";
// const char resource[] = "/TinyGSM/logo.txt";
// const char server[] = "showcase.api.linx.twenty57.net";
// const char resource[] = "/UnixTime/tounix?date=now";

TinyGsm         modem(SerialAT);
// TinyGsm         modem2(SerialAT);
// TinyGsmClient   simClient2(modem2);
TinyGsmClient   simClient(modem);
PubSubClient    simMqtt(simClient);
// HttpClient      http(simClient,server,80);
HttpClient      http(simClient,server,80);

uint32_t prevMillisNetwork = 0;
uint32_t prevMillisGPRS = 0;
uint32_t prevMillisRChk = 0;
bool beginFlag;


bool isTimeForRoutineCheck()
{
  if((millis() - prevMillisRChk > 20000) || beginFlag )
  {
    Serial.println("<------------SIM loop Begin---------------------->");
    prevMillisRChk = millis();
    beginFlag = false;
    return true;
  }
  return false;
}

void test()
{
//     static uint32_t millisTest = millis();
//    SerialMon.println(F("getting unixtime... "));
//   int err = http.get(resource);
//   if (err != 0) {
//     SerialMon.println(F("failed to connect"));
//     delay(10000);
//     return;
//   }

//   int status = http.responseStatusCode();
//   // SerialMon.print(F("Response status code: "));
//   // SerialMon.println(status);
//   if (!status) {
//     delay(10000);
//     return;
//   }

// //   SerialMon.println(F("Response Headers:"));
// //   while (http.headerAvailable()) {
// //     String headerName  = http.readHeaderName();
// //     String headerValue = http.readHeaderValue();
// //     SerialMon.println("    " + headerName + " : " + headerValue);
// //   }

// //   int length = http.contentLength();
// //   if (length >= 0) {
// //     SerialMon.print(F("Content length is: "));
// //     SerialMon.println(length);
// //   }

// //   if (http.isResponseChunked()) {
// //     SerialMon.println(F("The response is chunked"));
// //   }

//   String body = http.responseBody();
//   SerialMon.print(F("Response:"));
//   SerialMon.println(body);

//   // SerialMon.print(F("Body length is: "));
//   // SerialMon.println(body.length());

//   // Shutdown

//   http.stop();
//   // SerialMon.println(F("Server disconnected"));
//   Serial.print("test time: "); Serial.println(uint32_t(millis()-millisTest));
}

void simBegin()
{  
  // pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  // pinMode(MODEM_POWER_ON, OUTPUT);
  // digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  // digitalWrite(MODEM_POWER_ON, HIGH);

  SerialAT.begin(SERIAL_AT_BAUD_RATE, SERIAL_8N1, MODEM_RX, MODEM_TX);
  
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  simDetails();
  beginFlag = true;


}

void simDetails()
{
    String modemInfo = modem.getModemInfo();
    SerialMon.print("Modem Info: ");
    SerialMon.println(modemInfo);

    String modemName = modem.getModemName();
    SerialMon.print("Modem Name: ");
    SerialMon.println(modemName);   

    int modemRegStatus = modem.getRegistrationStatus();
    SerialMon.print("Modem Reg Status: ");
    SerialMon.println(modemRegStatus);
  
}

bool isSimNetworkConnected()
{
    Serial.println("<------------Network check Begin---------------------->");
    bool f = modem.isNetworkConnected();
    if(f)
    {
        SerialMon.println("[Network is Connected]");
        simNetworkDetails();
    }
    else
    {
        SerialMon.println("[Network disconnected]");
    }

    prevMillisNetwork = 0;

    return f;
}

bool waitforSimNetwork()
{
  while(millis() - prevMillisNetwork > 10000)
  {
    Serial.println("<------------Network wait Begin---------------------->");
    if (!modem.waitForNetwork(180000L, true)) 
    {
      prevMillisNetwork = millis();
      SerialMon.println("...fail");
      SerialMon.println("[[[delay for network 10000]]]]");
    }
    if (modem.isNetworkConnected()) 
    {
      SerialMon.println("Network re-connected");
      prevMillisNetwork = 0;
      return false;
    }
    else
    {
      return true;
    }
  }
  return true;
}

void simNetworkDetails()
{
    int16_t SigQuality = modem.getSignalQuality();
    Serial.print("GSM Signal Quality: ");
    Serial.println(modem.getSignalQuality());
    
    // String localIP = modem.getLocalIP();
    // Serial.print("Sim Local IP: ");
    // Serial.println(localIP);
    
}

bool isSimGprsConnected()
{
  
  Serial.println("<------------GPRS check Begin---------------------->");
  if (!modem.isGprsConnected()) 
  {
    SerialMon.println("GPRS disconnected!");
    SerialMon.print(F("Connecting to "));
    SerialMon.println(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
    {
      SerialMon.println("...fail");
      SerialMon.println("[[[delay for gprs 10000]]]]");
      prevMillisGPRS = millis();
      return false;
    }
    else 
    {
      SerialMon.println("[GPRS reconnected]");
      simGPRSdetails();
      return true;
    }
  }
  else
  {
    SerialMon.println("[GPRS connected]");
    simGPRSdetails();
    return true;
  }
}

bool isSimGprsWait()
{
  while(millis() - prevMillisGPRS > 10000)
  {
    SerialMon.println("...delay complete");
    return false;
  }
  return true;
}

void simGPRSdetails()
{
    
    String CCID = modem.getSimCCID();
    String IMEI = modem.getIMEI();
    String IMSI = modem.getIMSI();
    // String operator = modem.getOperator();
    int simStatus = modem.getSimStatus();
    
    // Serial.print("operator: "); Serial.println(operator);
    Serial.print("CCID: "); Serial.println(CCID);
    Serial.print("IMEI: "); Serial.println(IMEI);
    Serial.print("IMSI: "); Serial.println(IMSI);
    Serial.print("simStatus: "); Serial.println(simStatus);
}

void radioOFF()
{
  Serial.println("trying ot radio off.....");
  bool f =modem.radioOff();
  if(f) Serial.println("radio off works ");
  else Serial.println("radio off doesnot work");
}

void powerOFF()
{
  Serial.println("trying to power off.....");
  bool f =modem.poweroff();
  if(f) Serial.println("power off works ");
  else Serial.println("power off doesnot work");
}


