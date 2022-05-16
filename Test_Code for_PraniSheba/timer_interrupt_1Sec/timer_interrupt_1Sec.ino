hw_timer_t * timer = NULL;
int i=0;
int p=0;

void IRAM_ATTR onTimerHandler() 
{
    //This code will be executed every 1000 ticks, 1ms
    i++;
    Serial.print("sec:"); Serial.println(i);    
    
}

void setup()
{
  Serial.begin(115200);
  timerbegin();
//    // Prescaler 80 is for 80MHz clock. One tick of the timer is 1us
//    timer = timerBegin(0, 80, true); 
//
//    //Set the handler for the timer
//    timerAttachInterrupt(timer, &onTimerHandler, true); 
//
//    // How often handler should be triggered? 1000 means every 1000 ticks, 1ms
//    //1000,000 1s
//    timerAlarmWrite(timer, 1000, true); 
//
//    //And enable the timer
//    timerAlarmEnable(timer); 
}

void loop() {
uint8_t cmd ;//= getSerialCmd();
//  Serial.println(F("------------------------------"));
  if (cmd == 1)
  {
    Serial.println("got 1");
  }

  else if (cmd ==2)
  {
    Serial.println("got 2");
  }
}


uint8_t getSerialCmd()
{
  Serial.print(F("Input cmd: "));
  int cmd;
  if(Serial.available()>0)
  {
//    delay(10);
    cmd = Serial.parseInt();
    Serial.println(cmd);
  }
  else
  {
    cmd = 0;
  }
  
  
  return cmd;
}


void timerbegin()
{
  // Prescaler 80 is for 80MHz clock. One tick of the timer is 1us
    timer = timerBegin(0, 80, true); 

    //Set the handler for the timer
    timerAttachInterrupt(timer, &onTimerHandler, true); 

    // How often handler should be triggered? 1000 means every 1000 ticks, 1ms
    //1000,000 1s
    timerAlarmWrite(timer, 1000000, true); 

    //And enable the timer
    timerAlarmEnable(timer); 
}
