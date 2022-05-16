#include "mqtt.h"


/*************** disconnect will message ***********/
char const disconnect_msg[] = "{\"status\" : 0}";
char const connected_msg[]  = "{\"status\" : 1}";

/**************Publish Topics**************************/
char const *payload_topic = BASE_STATION_ID"/data";
char const *log_topic      = BASE_STATION_ID"/log";
char const *config_ack_topic = BASE_STATION_ID"/conf_ack";
char const *will_feed = BASE_STATION_ID"/last_will";
/**************Subscribe Topics**************************/
char const *config_topic   = BASE_STATION_ID"/conf";


// char const *log_payload = "[[22,{\"id\":\"B2008\",\"ts\":\"1645666666\",\"data\":[80,80,80,80,80,80,80,80,80,80]}]]";


bool simMqttConnect() 
{
    
    Serial.println("Connecting to broker ...");

    // Connect to MQTT Broker
    simMqtt.setServer(MQTT_SERVER, MQTT_PORT);
    bool status = simMqtt.connect(MQTT_CLIENTID,MQTT_USER,MQTT_PASS,will_feed,2,0,disconnect_msg);

    if (status == false) 
    {
        Serial.println(" fail");
        return false;
    }

    return simMqtt.connected();
}

bool isSimMqttconnected()
{
    bool f = simMqtt.connected();
    if(f) Serial.println("sim Mqtt connected");
    else Serial.println("Sim Mqttt disconnectd");
    return f;
}

void mqttCheck()
{
    Serial.println("<------------Connect to MQTT Broker ---------------------->");
    if(!isSimMqttconnected())
    {
        simMqttConnect(); 
        isSimMqttconnected();
    }

}

void mqttLoop()
{
    bool f = simMqtt.loop();
    if(!f) Serial.println("mqtt loop not connectd");
}

void mqttPublish()
{
    String payload_str = create_payload();
    const char * payload = payload_str.c_str();
    Serial.println(payload);
    simMqtt.publish(log_topic,payload);
}