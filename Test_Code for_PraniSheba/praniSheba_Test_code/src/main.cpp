#include "main.h"

int id = 0;

void allBegin() {
  Serial.begin(SERIAL_SPEED);
  Serial.print("hello test code");
  framInit();
  flashBegin();
  humTempSensorBegin();
  led_begin();
  printInstruction();
}

void mainLoop() {
  id = getInstructionID();
  switch (id)
  {
    
    case 1:
      printInstruction();
     break;
    case 2:
      flashCheckAuto();
      framLoop();
      scanI2cBus();
      rtcCheck();
      checkAllGasSensor();
      checkHumTempSensor();
      led_blink();
    break;
    
    case 3:
      scanI2cBus();
    break;
    case 4: 
      rtcCheck();
    break;
    case 5:
    case 6:
    case 7:
    case 8:
      flashCheck((id - 4));
    break;
    case 9:
      checkAllGasSensor();
    break;
    case 10:
      checkHumTempSensor();
    break;
    case 11:
      led_blink();
    break;
    case 12:
      led_blink_specific();
    break;
    case 13:
      framLoop();
    break;

    default:
    break;
  }
  if(id) Serial.println("press 1 to show instructions");
}