hw_timer_t * timer = NULL;
int i=0;
int p=0;

void IRAM_ATTR onTimerHandler() 
{
    //This code will be executed every 1000 ticks, 1ms
    i++;
    if(i%1000==0)
    {
      p++;
      Serial.print("millis: "); Serial.println(i);
      Serial.print("sec:"); Serial.println(p);
    }
    
    
}

void setup()
{
  Serial.begin(115200);
    // Prescaler 80 is for 80MHz clock. One tick of the timer is 1us
    timer = timerBegin(0, 80, true); 

    //Set the handler for the timer
    timerAttachInterrupt(timer, &onTimerHandler, true); 

    // How often handler should be triggered? 1000 means every 1000 ticks, 1ms
    //1000,000 1s
    timerAlarmWrite(timer, 1000, true); 

    //And enable the timer
    timerAlarmEnable(timer); 
}

void loop() {
    //Here you can do whatever you want
    Serial.println("hello");
    delay(10000);
    Serial.println("esp");
    delay(5000);
}
