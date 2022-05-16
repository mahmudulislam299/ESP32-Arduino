
#include <WiFi.h>
#include <WiFiMulti.h>
#include <PubSubClient.h>

#define MQTT_SERVER     "192.168.0.90"
#define MQTT_PORT        1887

#define MQTT_USER     "nodered"
#define MQTT_PASS     "123456"
#define MQTT_CLIENTID "12"


WiFiMulti WiFiMulti;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void wifiBegin()
{
  // We start by connecting to a WiFi network
    WiFiMulti.addAP("APS_Office","praniSheba@2021#");

    Serial.println();
    Serial.println();
    Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
//    if (client.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS)) 
  if (client.connect(MQTT_CLIENTID)) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test","hello world");
      // ... and resubscribe
      client.subscribe("birth");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  wifiBegin();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  Serial.println(F("MQTT Setup Done"));
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
