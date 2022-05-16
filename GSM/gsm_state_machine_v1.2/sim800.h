#ifndef _SIM800_H_
#define _SIM800_H_

// Select your modem:
#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SerialAT Serial1

#include <TinyGsmClient.h>
#include <PubSubClient.h>


//
//#define MODEM_RST            5
//#define MODEM_PWKEY          4
//#define MODEM_POWER_ON       23
//#define MODEM_TX             27
//#define MODEM_RX             26


#define MODEM_RST            5
#define MODEM_PWKEY          101
#define MODEM_POWER_ON       100
#define MODEM_TX             17
#define MODEM_RX             16




const char apn[]      = "gpinternet";
const char gprsUser[] = "";
const char gprsPass[] = "";
const char server[]   = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";

typedef enum 
{
  GSM_BEGIN,
  GSM_NETWORK,
  GSM_GPRS,
  GSM_HTTP
}gsmState_t;



#endif //_SIM800_H_
