#include <EEPROM.h>

// define the number of bytes you want to access
#define EEPROM_SIZE 4096
#define TIMER_INTERVAL 1
hw_timer_t * timer = NULL;
volatile int i=0;
int prev_i = 0;
int p=0;

uint8_t arr[1500];

void IRAM_ATTR onTimer() 
{
    //This code will be executed every 1000 ticks, 1ms
    i = i  + TIMER_INTERVAL;
//    Serial.print("sec:"); Serial.println(i);   
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology "); 
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology "); 
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology "); 
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology "); 
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology "); 
//    Serial.println("mahmudul islam - adrosho pranisheba ltd - iot technology ");
//    Serial.println("ok1"); 
    
}


void timerbegin()
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_INTERVAL*1000000, true);
  timerAlarmEnable(timer);
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("start");
  EEPROM.begin(EEPROM_SIZE);
  timerbegin();

}

void loop() 
{

//  if(i!=prev_i)
//  {
//    Serial.print("sec: "); Serial.println(i);
//    prev_i = i;
//  }
   uint8_t cmd = getSerialCmd();
  
  if (cmd == 1)
  {
    uint8_t value = 48;
    Serial.println("got 1");
    for(int i =0; i <=1000; i++)
    {
       EEPROM.write(i, i+2);
    }
   
    EEPROM.commit();
    Serial.println("done");
  }

  else if (cmd ==2)
  {
    Serial.println("got 2");
    for (int j = 0; j <=1000; j++)
    {
      arr[j]= EEPROM.read(j);
//      Serial.print(arr[j]);
    } 
    Serial.println("\ndone reading");
     for (int j = 0; j <=1000; j++)
    {
//      arr[j]= EEPROM.read(j);
      Serial.print(arr[j]); Serial.print(" ");
    } 
    Serial.println("\ndone printing");
  }
}

uint8_t getSerialCmd()
{
 
  int cmd;
  if(Serial.available()>0)
  {
    Serial.print(F("Input cmd: "));
    cmd = Serial.parseInt();
    Serial.println(cmd);
    Serial.println(F("------------------------------"));
    return cmd;
  }
  else
  {
    return 0;
  }
}
