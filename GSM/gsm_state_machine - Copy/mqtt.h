#ifndef _MQTT_H_
#define _MQTT_H_
#include <Arduino.h>
#include "includefile.h"


#define MQTT_SERVER     "iot.pranisheba.com.bd"
#define MQTT_PORT        1884
#define MQTT_USER     "B2008"
#define MQTT_PASS     "B2008"
#define MQTT_CLIENTID "B2008"

#define BASE_STATION_ID   MQTT_CLIENTID





bool simMqttConnect();
bool isSimMqttconnected();
void mqttCheck();
void mqttLoop();
void mqttPublish();

#endif //_MQTT_H_