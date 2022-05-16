#include "time.h"
#include <sys/time.h>

struct timeval tv;
uint32_t unixtime;

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  unixtime = 1639039630;
  tv.tv_sec = unixtime;  // epoch time (seconds)
  tv.tv_usec =0 ;// ms;    // microseconds
  settimeofday(&tv, NULL);

}

void loop()
{
  gettimeofday(&tv,NULL);
  unixtime = tv.tv_sec;

  Serial.println(unixtime);


  struct tm timeinfo;
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//  uint32_t epoch;
//  epoch = mktime(&timeinfo);
//  Serial.println(epoch);


  
  delay(2000);

}
