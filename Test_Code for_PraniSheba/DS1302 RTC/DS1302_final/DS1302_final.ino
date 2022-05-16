//#include <ThreeWire.h>  
//#include <RtcDS1302.h>
// #include <SHT21.h>  // include SHT21 library
#if defined(PROD_BUILD)   
#include "./src/lib/RTC_1302/src/ThreeWire.h"
#include "./src/lib/RTC_1302/src/RtcDS1302.h"
#include "./src/lib/SHT21-Arduino-Library/SHT21.h"
#endif


ThreeWire myWire(21,22,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);


SHT21 sht; 
float temp;   // variable to store temperature
float humidity; // variable to store hemidity

int i=0;

hw_timer_t * timer = NULL;
void timer1Start1();

void IRAM_ATTR onTimerHandler() 
{
  Serial.println(i);
  i++;

}

void setup () 
{
    Serial.begin(250000);
     timerbegin();
     rtcBegin();


    

}

void loop () 
{
    Serial.print("running : "); Serial.println(Rtc.GetIsRunning());

    Serial.println(Rtc.getUnixTime());
    
    showTH();
   
    
    delay(5000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))


void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

void timerbegin()
{
  timer = timerBegin(0, 80, true); 
  
  //Set the handler for the timer
  timerAttachInterrupt(timer, &onTimerHandler, true); 

  // How often handler should be triggered? 1000 means every 1000 ticks, 1ms
  //1000,000 1s
  timerAlarmWrite(timer, 1000000, true); 

  //And enable the timer
  timerAlarmEnable(timer);
}


void rtcBegin()
{
  Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    uint32_t unix;
    unix = dateTime2unix(compiled);

    Rtc.setUnixTime(unix);

     if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.setUnixTime(unix);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
}

void showTH()
{
    sht.begin(21,22);  

    temp = sht.getTemperature();  // get temp from SHT 
    humidity = sht.getHumidity(); // get temp from SHT

    Serial.print("Temp: ");      // print readings
    Serial.print(temp);
    Serial.print("\t Humidity: ");
    Serial.println(humidity);

}
