
#include <WiFi.h>
#include <WiFiMulti.h>
#include "./src/pubsubclient/src/PubSubClient.h"

#define MQTT_SERVER     "192.168.0.56"
#define MQTT_PORT        1883

#define MQTT_USER     "esp1"
#define MQTT_PASS     "esp1"
#define MQTT_CLIENTID "esp1"


const char *topic = "topic_esp";
uint32_t millisPrev = 0;
const char *will_feed = "lastwill";
const char disconnect_msg[] = "i will be disconnected";


WiFiMulti WiFiMulti;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Msg arrived [");
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
    // mqtt.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS,will_feed,2,0,disconnect_msg);
    if (client.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS, will_feed,2,true,disconnect_msg)) 
//  if (client.connect(MQTT_CLIENTID)) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("esp","hello world");
      // ... and resubscribe
      // client.subscribe("topic2", 1);
      // client.subscribe("topic4", 1);
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
  client.setKeepAlive(15);
  reconnect();
  client.qos2ResetBuff();
  Serial.println(F("MQTT Setup Done"));
}

void loop()
{
  // if (!client.connected()) {
  //   reconnect();
  // }
  static uint16_t num = 0;
  static uint8_t mid = 3;
  uint8_t payloadLen = 10;
  static bool newMsgFlag = false;
  client.loop();
  // if(!client.loop())
  {
    // Serial.println("trying to reconnect tom mqtt");
    // if (client.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS))
    // {
    //   Serial.println("mqtt connected");
    //   // Once connected, publish an announcement...
    //   // client.publish("esp","hello world");
    //   // ... and resubscribe
    //   client.subscribe("topic2", 1);
    //   client.subscribe("topic4", 1);
    // } 
    // else 
    // {
    //   Serial.print("failed, rc=");
    //   Serial.print(client.state());
    //   Serial.println(" try again in 5 seconds");
    //   // Wait 5 seconds before retrying
    //   delay(5000);
    // }
  }


  if(millis() - millisPrev > 30000 && newMsgFlag == true )
  {
    mid++;
    num++;
    if(mid>100) mid = 1;
    newMsgFlag = false;

    millisPrev = millis();
    // (const char* topic, const uint8_t * payload, unsigned int plength,uint8_t msgId);
    char *payload= "hello";

    String pp = "the number is " + String(num);
    const char *payload2 = pp.c_str();

    const uint8_t *payloadPtr;
    payloadPtr = (uint8_t *)payload2;
    uint16_t len = pp.length()+1;
    Serial.println("\n\n");

    Serial.print("start publishing. mid: ");
    Serial.println(mid);
    Serial.println(pp);
    client.publish_Q1(topic,payloadPtr,len,mid, true, false);
    
  }

  newMsgFlag = client.isqos2ack(mid);

}
