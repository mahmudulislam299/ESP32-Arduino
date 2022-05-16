#include "includefile.h"


simState_t simState;

bool flag = false;
bool powerFlag = false;
bool radioFlag = false;

void setup() 
{
  Serial.begin(250000);
 
  simBegin();
  simState = SIM_BEGIN;
  Serial.println("loop begin");

}

void loop() {
  int i = Serial.parseInt();
  // if(i) Serial.println(i);
  if(i == 1)
  {
    Serial.println("ready for loop");
    i = 0;
    flag = true;
  }
  if(i == 2)
  {
    Serial.println("ready for loop");
    i = 0;
    flag = true;
    powerFlag = true;
  }

  if(i == 3)
  {
    Serial.println("ready for loop");
    i = 0;
    flag = true;
    radioFlag = true;
  }

  if(flag)
  {
    switch(simState)
    {
      case SIM_BEGIN:
        if(isTimeForRoutineCheck())
        {
          simState = SIM_NETWORK;
        }
        break;

      case SIM_NETWORK:
        if(isSimNetworkConnected())
        {
          simState = SIM_GPRS;
        }
        else
        {
          simState = SIM_NETWORK_WAIT;
        }
        break;

      case SIM_NETWORK_WAIT:
        if(!waitforSimNetwork())
        {
          simState = SIM_GPRS;
        }
        break;
      
      case SIM_GPRS:
        if(isSimGprsConnected())
        {
          simState = SIM_HTTP;
        }
        else 
        {
          simState = SIM_GPRS_WAIT;
        }
        break;
      case SIM_GPRS_WAIT:
        if(!isSimGprsWait())
        {
          simState = SIM_GPRS;
        }
        break;

      case SIM_HTTP:
        // getUnixTime();
        // test();
        simState = SIM_MQTT;
        break;

      case SIM_MQTT:
        mqttCheck();
        simState = SIM_BEGIN;
        Serial.println("<------------mqtt publish---------------------->");
        mqttPublish();
        Serial.println("<------------SIM loop finished---------------------->");
        flag = false;
        if(radioFlag)
        {
          radioOFF();
          radioFlag = false;
        }
        if(powerFlag)
        {
          powerOFF();
          powerFlag = false;
        }
        break;
    }

    mqttLoop();
  } 
}
