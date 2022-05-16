#include "http.h"
// #include "sim800.h"



uint32_t getUnixTime()
{
  static uint32_t millisHttp = millis();
  Serial.println("<------------HTTP connect Begin---------------------->");
  Serial.println("getting unixtime...");
  // Serial.print("Connecting to ");
  // Serial.println(server);
  if (!simClient.connect(server, port)) 
  {
    Serial.println("...failed to connect server");
    simMqttConnect();
    isSimMqttconnected(); 
    return 0UL;
  }
  
  // Serial.println("Performing HTTP GET request...");
  simClient.print(String("GET ") + resource + " HTTP/1.1\r\n");
  simClient.print(String("Host: ") + server + "\r\n");
  simClient.print("Connection: close\r\n\r\n");
  simClient.println();


  uint32_t timeout = millis();
  char arr[32];
  uint8_t index=0;
  while (simClient.connected() && millis() - timeout < 10000L) 
  {
    while (simClient.available()) 
    {
      arr[index] = simClient.read();
      index++;
      if(index>=32) index = 0;
      timeout = millis();       
    }
  }
  simClient.stop();
  
  
  char time[12]; int8_t copy=-1; uint8_t indexTime=0;
  for (uint8_t i =0; i<32 ; i++)
  {
    if(arr[i]=='\"') 
    {
      copy =copy*(-1);
      i++;
      time[indexTime] ='\0';
    }

    if(copy == 1)
    { 
      
      time[indexTime] = arr[i];
      indexTime++;
    }
  }
  Serial.print("time: "); Serial.println(time);

  uint32_t unixtime = atoi(time);
  Serial.print("unixtime: "); Serial.println(unixtime);
  // Serial.print("http time: "); Serial.println(uint32_t(millis()-millisHttp));
  simMqttConnect();
  isSimMqttconnected();
  return unixtime;
}