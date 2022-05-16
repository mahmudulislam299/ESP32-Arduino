#include <soc/rtc.h>
#include <TimeLib.h>
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

// Sync control variable
static volatile uint32_t _syncTime = 0;
//static uint32_t utcOffset = (-3 * 3600);
static uint32_t utcOffset = 0; // Use UTC

/*void DeepSleep() {


  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1); //1 = High, 0 = Low
  //If you were to use ext1, you would use it like
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  const int ext_wakeup_pin_1 = 2;
  const uint64_t ext_wakeup_pin_1_mask = 1ULL << ext_wakeup_pin_1;
  //const int ext_wakeup_pin_2 = 4;
  //const uint64_t ext_wakeup_pin_2_mask = 1ULL << ext_wakeup_pin_2;

  // printf("Enabling EXT1 wakeup on pins GPIO%d, GPIO%d\n", ext_wakeup_pin_1);
  esp_sleep_enable_ext1_wakeup(ext_wakeup_pin_1_mask, ESP_EXT1_WAKEUP_ANY_HIGH);

  //Go to sleep now

  esp_deep_sleep_start();
  //esp_deep_sleep(1000000LL);
  //ESP.restart();
  Serial.println("This will never be printed");
}*/

bool go_to_sleep = false;


/*void IRAM_ATTR ISR() {
  go_to_sleep = true;
}*/

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
//  struct timeval now = { 0 };
//  settimeofday(&now, NULL);

  //setTime(int hr,int min,int sec,int day, int month, int yr);
//  Serial.println("attach Interrupt");
//  attachInterrupt(digitalPinToInterrupt(2), ISR, FALLING);
}

void loop() {
//  //Start:
//  Serial.println("start main loop");
//  if (go_to_sleep) {
//    //detachInterrupt(2);
//    Serial.println("\n\nGoing to sleep now");
//    go_to_sleep = false;
//    //pinMode(2, INPUT);
//    DeepSleep();
//  }
  gettimeofday(&tv,NULL);
  unixtime = tv.tv_sec;

  Serial.println(unixtime);


  struct tm timeinfo;
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  delay(2000);

}
