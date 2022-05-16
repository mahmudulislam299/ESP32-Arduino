#include <WiFi.h>
#include <AsyncUDP.h>

const char * ssid = "APS_Office";
const char * pass = "praniSheba@2021#";

// I am using 4 Sliders the 5th one is not used
const int NUM_SLIDERS = 5;
// I am using a NODEMCU ESP 32S and pins SVP, SVN, P34, P35, (P32 (Not used))
const int analogInputs[NUM_SLIDERS] = {36, 39, 34, 35, 32};

int analogSliderValues[NUM_SLIDERS];

AsyncUDP udp;

void setup()
{
    // Set all slider pins to INPUT
    for (int i = 0; i < NUM_SLIDERS; i++) 
    {
      pinMode(analogInputs[i], INPUT);
    }
    // Get WiFi going
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) 
    {
        Serial.println("WiFi Failed");
        while(1) 
        {
            delay(1000);
        }
    }
}

// Get slider pin values
void updateSliderValues() 
{
  static int p = 1;
  for (int i = 0; i < NUM_SLIDERS; i++) 
  {
     analogSliderValues[i] = p;
  }
  p++;
}

// TODO only send values if there is significant change in values to limit network traffick
// UDP Broadcast slider values
void sendSliderValues() 
{
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) 
  {
    builtString += String((int)analogSliderValues[i]);
    // Build the string to broadcast by seperating values using | except for last value
    if (i < NUM_SLIDERS - 1) 
    {
      builtString += String("-");
    }
  }
  Serial.println(builtString);
  // Send UDP Broadcast to 255.255.255.255 (default broadcast addr), Port 2255
  udp.broadcastTo(builtString.c_str(), 2255);
}

void loop()
{
    updateSliderValues();
    sendSliderValues(); // Send data
    delay(5000);
}
