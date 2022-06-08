#ifndef _SIM800_H_
#define _SIM800_H_

#include "includefile.h"

// Select your modem:
#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial

#if defined(ESP32_LILYGO)
  #define SerialAT Serial1
#elif defined(ESP32_DEVKIT)
  #define SerialAT Serial2
#else
#error "No board Selected"
#endif


// #include <TinyGsmClient.h>
#include "src\lib\TinyGSM\src\TinyGsmClient.h"
#include <PubSubClient.h>
#include <ArduinoHttpClient.h>


#if defined(ESP32_LILYGO)
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define SERIAL_AT_BAUD_RATE  115200
#elif defined(ESP32_DEVKIT)
#define MODEM_RST            5
#define MODEM_PWKEY          100
#define MODEM_POWER_ON       101
#define MODEM_TX             17
#define MODEM_RX             16
#define SERIAL_AT_BAUD_RATE  115200
#else
#error "No board Selected"
#endif




const char apn[]      = "gpinternet"; //"gpinternet"; //WAP
const char gprsUser[] = "";
const char gprsPass[] = "";




typedef enum 
{
  SIM_BEGIN,
  SIM_NETWORK,
  SIM_NETWORK_WAIT,
  SIM_GPRS,
  SIM_GPRS_WAIT,
  SIM_HTTP,
  SIM_MQTT
}simState_t;

bool isTimeForRoutineCheck();
void test();
void simBegin();
void simDetails();
bool isSimNetworkConnected();
bool waitforSimNetwork();
void simNetworkDetails();
bool isSimGprsConnected();
bool isSimGprsWait();
void simGPRSdetails();
void radioOFF();
void powerOFF();



extern TinyGsm modem;
// extern TinyGsm modem2;
// extern TinyGsmClient simClient2;
extern TinyGsmClient simClient;
extern PubSubClient  simMqtt;
// extern HttpClient http;


#endif //_SIM800_H_
