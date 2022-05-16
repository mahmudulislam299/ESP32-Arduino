
#include <ThreeWire.h>  
#include <RtcDS1302.h>

//ThreeWire myWire(4,5,2); // IO, SCLK, CE
ThreeWire myWire(21,22,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

 
#include <SHT21.h>  // include SHT21 library

SHT21 sht; 

float temp;   // variable to store temperature
float humidity; // variable to store hemidity
#define countof(a) (sizeof(a) / sizeof(a[0]))


void setup () 
{
    Serial.begin(115200);

//    Serial.print("compiled: ");
//    Serial.print(__DATE__);
//    Serial.println(__TIME__);
   

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
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

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    sht.begin(21,22);  
}

void loop () 
{
    showTime();
    showTH();    
    Serial.println("------");
    Serial.println();
    
    delay(2000); // ten seconds
}


void showTime()
{
  Rtc.Begin();
//  RtcDateTime now = Rtc.GetDateTime();
//
//  printDateTime(now);
//  Serial.println();
//
//  if (!now.IsValid())
//  {
//      Serial.println("RTC lost confidence in the DateTime!");
//  }

  Serial.print("running : "); Serial.println(Rtc.GetIsRunning());
  Serial.println(Rtc.getUnixTime());
    
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
