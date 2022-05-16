#include <soc/rtc.h>
//#include <TimeLib.h>
#include <sys/time.h>

#define SYNC_TIMEOUT 60000
#define CALIBRATE_ONE(cali_clk) calibrate_one(cali_clk, #cali_clk)


struct timeval tv;
uint32_t unixtime;

static uint32_t calibrate_one(rtc_cal_sel_t cal_clk, const char *name)
{
  const uint32_t cal_count = 1000;
  const float factor = (1 << 19) * 1000.0f;
  uint32_t cali_val;
  printf("%s:\n", name);

  for (int i = 0; i < 5; ++i)
  {
    printf("calibrate (%d): ", i);
    cali_val = rtc_clk_cal(cal_clk, cal_count);
    printf("%.3f kHz\n", factor / (float)cali_val);
  }
  return cali_val;
}






bool enable_rtc()
{
  delay(500);
  Serial.println("start");
  // ------------- Start RTC Clock and Calibration --------------
  rtc_clk_32k_bootstrap(512);
  rtc_clk_32k_bootstrap(512);
  rtc_clk_32k_bootstrap(512);
  rtc_clk_32k_enable(true);

  delay(1000); //i did it

  uint32_t cal_32k = CALIBRATE_ONE(RTC_CAL_32K_XTAL);
  rtc_clk_slow_freq_set(RTC_SLOW_FREQ_32K_XTAL);
  

  if (cal_32k == 0)
  {
//    printf("32K XTAL OSC has not started up");
    Serial.println("32K XTAL OSC has not started up");
  }
  else
  {
//    printf("XTAL OSC - Okay");
    Serial.println("XTAL OSC - Okay");
  }

  if (rtc_clk_32k_enabled())
  {
    Serial.println("OSC Enabled");
  }
  return cal_32k;
}


void setup() {
  Serial.begin(115200);
  Serial.println("statr after 20 sec");
  while(enable_rtc() == false);
  {
    Serial.println("external crystal not enabled");
  }
  



  unixtime = 1639294235;
  tv.tv_sec = unixtime;  // epoch time (seconds)
  tv.tv_usec =0 ;// ms;    // microseconds
  settimeofday(&tv, NULL);

}

void loop() {
  gettimeofday(&tv,NULL);
  unixtime = tv.tv_sec;

  Serial.println(unixtime);


  struct tm timeinfo;
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  delay(2000);

}
