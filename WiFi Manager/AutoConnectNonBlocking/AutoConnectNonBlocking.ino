#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
WiFiManager wm;

void setup() 
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //reset settings - wipe credentials for testing
//    wm.resetSettings();

    wm.setConfigPortalBlocking(false);
    wm.setConfigPortalTimeout(60);
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect("AutoConnectAP"))
    {
        Serial.println("connected...yeey :)");
    }
    else {
        Serial.println("Configportal running");
    }

    wm.startConfigPortal();
    // wm.startWebPortal();
}

void loop() {
    wm.process();
    // put your main code here, to run repeatedly:
    static uint32_t prevMillis = 0;
    if ((millis() - prevMillis) > 1000)
    {
      Serial.println("its non blocking");
      prevMillis = millis();
    }

    static uint32_t prevMillisWifi = 0;
    if ((millis() - prevMillisWifi ) > 4000)
    {
      if (WiFi.status() != WL_CONNECTED)
      {
        Serial.println("WiFi not Connected");
      }
      else
      {
        Serial.println("WiFi is Connected");
      }

      prevMillisWifi = millis();
    }
    
}
