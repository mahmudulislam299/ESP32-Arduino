/*

  PubSubClient.cpp - A simple client for MQTT.
  Nick O'Leary
  http://knolleary.net
*/

#include "PubSubClient.h"
#include "Arduino.h"

#if defined(BS_V2)
    #define debugmq(...)        Serial1.print(__VA_ARGS__)
    #define debugmqln(...)      Serial1.println(__VA_ARGS__)
#else
    #define debugmq(...)        Serial.print(__VA_ARGS__)
    #define debugmqln(...)      Serial.println(__VA_ARGS__)
#endif

qos2_state _qos2Packet;
uint16_t buffPending;
uint8_t pipeMgsID;

PubSubClient::PubSubClient() 
{
    this->_state = MQTT_DISCONNECTED;
    this->_client = NULL;
    this->stream = NULL;
    setCallback(NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(IPAddress addr, uint16_t port, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(addr, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(IPAddress addr, uint16_t port, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(addr,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(addr, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(addr,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::PubSubClient(const char* domain, uint16_t port, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(const char* domain, uint16_t port, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
PubSubClient::PubSubClient(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) 
{
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

PubSubClient::~PubSubClient() 
{
  free(this->buffer);
}

boolean PubSubClient::connect(const char *id) 
{
    return connect(id,NULL,NULL,0,0,0,0,1);
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass) 
{
    return connect(id,user,pass,0,0,0,0,1);
}

boolean PubSubClient::connect(const char *id, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage) 
{
    return connect(id,NULL,NULL,willTopic,willQos,willRetain,willMessage,1);
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage) 
{
    return connect(id,user,pass,willTopic,willQos,willRetain,willMessage,1);
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage, boolean cleanSession) 
{
    _QOS_TYPE = willQos;
    // for QOS2 only
    if(_QOS_TYPE == 2)
    {
    	_qos2Packet._qos2CurrentIndex = 0;
    	for(uint16_t i=0;i<MQTT_QOS2_MAX_BUFFER;i++)
    	{
    		_qos2Packet._qos2Acknowledged[i] = true;
    		_qos2Packet._qos2bufferID[i] = NULL;
    		_qos2Packet._qos2MgsID[i] = i+1;
    		_qos2Packet._qos2Flag[i]= NULL;
    		_qos2Packet._qos2Plength[i] = NULL;
    		_qos2Packet._qos2SentTime[i] = NULL;
    	}
    }
    qos2ARPacketID = 0;
    //qos2 end
    
    if (!connected()) 
    {
        Serial.println("[]trying to connect ot mqtt");
        int result = 0;
        _QOS1Acknowledged = true;		// added for qos1

        if(_client->connected()) 
        {
            result = 1;
        } 
        else 
        {
            if (domain != NULL) 
            {
                result = _client->connect(this->domain, this->port);
            } 
            else 
            {
                result = _client->connect(this->ip, this->port);
            }
        }

        if (result == 1) 
        {
            nextMsgId = 1;
            // Leave room in the buffer for header and variable length field
            uint16_t length = MQTT_MAX_HEADER_SIZE;
            unsigned int j;

#if MQTT_VERSION == MQTT_VERSION_3_1
            uint8_t d[9] = {0x00,0x06,'M','Q','I','s','d','p', MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 9
#elif MQTT_VERSION == MQTT_VERSION_3_1_1
            uint8_t d[7] = {0x00,0x04,'M','Q','T','T',MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 7
#endif
            for (j = 0;j<MQTT_HEADER_VERSION_LENGTH;j++)
            {
                this->buffer[length++] = d[j];
            }

            uint8_t v;
            if (willTopic) 
            {
                v = 0x04|(willQos<<3)|(willRetain<<5);
            } 
            else 
            {
                v = 0x00;
            }
            if (cleanSession) 
            {
                v = v|0x02;
            }

            if(user != NULL) 
            {
                v = v|0x80;

                if(pass != NULL) 
                {
                    v = v|(0x80>>1);
                }
            }
            this->buffer[length++] = v;

            this->buffer[length++] = ((this->keepAlive) >> 8);
            this->buffer[length++] = ((this->keepAlive) & 0xFF);

            CHECK_STRING_LENGTH(length,id)
            length = writeString(id,this->buffer,length);
            if (willTopic) 
            {
                CHECK_STRING_LENGTH(length,willTopic)
                length = writeString(willTopic,this->buffer,length);
                CHECK_STRING_LENGTH(length,willMessage)
                length = writeString(willMessage,this->buffer,length);
            }

            if(user != NULL) 
            {
                CHECK_STRING_LENGTH(length,user)
                length = writeString(user,this->buffer,length);
                if(pass != NULL) 
                {
                    CHECK_STRING_LENGTH(length,pass)
                    length = writeString(pass,this->buffer,length);
                }
            }

            write(MQTTCONNECT,this->buffer,length-MQTT_MAX_HEADER_SIZE);

            lastInActivity = lastOutActivity = millis();

            while (!_client->available()) 
            {
                unsigned long t = millis();
                if (t-lastInActivity >= ((int32_t) this->socketTimeout*1000UL)) 
                {
                    _state = MQTT_CONNECTION_TIMEOUT;
                    Serial.println("** connection timeout");
                    Serial.print("state: "); Serial.println(_state);
                    Serial.print("mqtt state: "); Serial.println(this->_state);
                    _client->stop();
                    return false;
                }
            }
            uint8_t llen;
            uint32_t len = readPacket(&llen);

            if (len == 4) 
            {
                if (buffer[3] == 0) 
                {
                    lastInActivity = millis();
                    pingOutstanding = false;
                    _state = MQTT_CONNECTED;
                    Serial.println("[]mqtt connected...");

                    Serial.println("MQTT_CONNECTED");
                    Serial.print("_state:"); Serial.println(_state);
                    Serial.print("****mqtt state::"); Serial.println(this->_state);

                    return true;
                } 
                else 
                {
                    _state = buffer[3];
                    Serial.println("buffer[3];");
                    Serial.print("_state:"); Serial.println(_state);
                    Serial.print("****mqtt state::"); Serial.println(this->_state);
                }
            }
            _client->stop();
        } 
        else 
        {
            _state = MQTT_CONNECT_FAILED;
            Serial.println("MQTT_CONNECT_FAILED");
            Serial.print("_state:"); Serial.println(_state);
            Serial.print("****mqtt state::"); Serial.println(this->_state);
        }
        return false;
    }
    return true;
}

// reads a byte into result
boolean PubSubClient::readByte(uint8_t * result) 
{
   uint32_t previousMillis = millis();
   while(!_client->available()) 
   {
     yield();
     uint32_t currentMillis = millis();
     if(currentMillis - previousMillis >= ((int32_t) this->socketTimeout * 1000))
     {
       return false;
     }
   }
   *result = _client->read();
   return true;
}

// reads a byte into result[*index] and increments index
boolean PubSubClient::readByte(uint8_t * result, uint16_t * index)
{
  uint16_t current_index = *index;
  uint8_t * write_address = &(result[current_index]);
  if(readByte(write_address))
  {
    *index = current_index + 1;
    return true;
  }
  return false;
}

uint32_t PubSubClient::readPacket(uint8_t* lengthLength) 
{
    uint16_t len = 0;
    if(!readByte(this->buffer, &len)) return 0;
    bool isPublish = (this->buffer[0] & 0xF0) == MQTTPUBLISH;
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint16_t skip = 0;
    uint32_t start = 0;

    do {
        if (len == 5) 
        {
            // Invalid remaining length encoding - kill the connection
            _state = MQTT_DISCONNECTED;
            _client->stop();
            return 0;
        }
        if(!readByte(&digit)) return 0;
        this->buffer[len++] = digit;
        length += (digit & 127) * multiplier;
        multiplier <<=7; //multiplier *= 128
    } while ((digit & 128) != 0);
    *lengthLength = len-1;

    if (isPublish) 
    {
        // Read in topic length to calculate bytes to skip over for Stream writing
        if(!readByte(this->buffer, &len)) return 0;
        if(!readByte(this->buffer, &len)) return 0;
        skip = (this->buffer[*lengthLength+1]<<8)+this->buffer[*lengthLength+2];
        start = 2;
        if (this->buffer[0]&MQTTQOS1) 
        {
            // skip message id
            skip += 2;
        }
    }
    uint32_t idx = len;

    for (uint32_t i = start;i<length;i++) 
    {
        if(!readByte(&digit)) return 0;
        if (this->stream) 
        {
            if (isPublish && idx-*lengthLength-2>skip) 
            {
                this->stream->write(digit);
            }
        }

        if (len < this->bufferSize) 
        {
            this->buffer[len] = digit;
            len++;
        }
        idx++;
    }

    if (!this->stream && idx > this->bufferSize) 
    {
        len = 0; // This will cause the packet to be ignored.
    }
    return len;
}

boolean PubSubClient::loop() 
{
    static int pingRetry = 0;
    if (connected()) 
    {
        unsigned long t = millis();
        if ((t - lastInActivity > this->keepAlive*1000UL) || (t - lastOutActivity > this->keepAlive*1000UL)) 
        {
            if (pingOutstanding) 
            {
                pingRetry = 0;
                this->_state = MQTT_CONNECTION_TIMEOUT;
                _client->stop();
                return false;
            } 
            else 
            {
                Serial.println("[] sending mqtt_ping_req");
                this->buffer[0] = MQTTPINGREQ;
                this->buffer[1] = 0;
                _client->write(this->buffer,2);
                lastOutActivity = t;
                lastInActivity = t;
                pingRetry++;
                if(pingRetry >= 4)
                {
                    Serial.print("[] pingRetry"); 
                    Serial.println(pingRetry);
                    pingOutstanding = true;
                }
            }
        }
        
        t = millis();
        if ((t - _QOS1_SENT_TIME >= MQTT_QOS1_WAIT_TIME) && (_QOS1Acknowledged==false))
        {  // Resend QOS1 message if not acknowledged
           //debug   debugmq("*MQQT q1 RESENDING");
            Serial.println("[]resending last msg agian");
              publish_Q1(_SentQOS1Topic, _SentQOS1buffer, _SENTQOS1Length, NULL, false,true);   // send last message again
              _QOS1_SENT_TIME = millis();                                                   //Reset timer
        }

        //------------------------------For QOS2 only---------------------
        t = millis();
        if(((t - _qos2Packet._qos2SentTime[qos2ARPacketID]) > MQTT_QOS2_WAIT_TIME) && (_qos2Packet._qos2Acknowledged[qos2ARPacketID] == false))
        {
        	
        	if(_qos2Packet._qos2Flag[qos2ARPacketID] == MQTTPUBLISH)
        	{
        		debugmqln("[PubSubClient]-- retrying QOS2 MQTTPUBLISH--");
        		uint16_t tempPacketID = _qos2Packet._qos2CurrentIndex;
        		_qos2Packet._qos2CurrentIndex = qos2ARPacketID;
        		_qos2Packet._qos2Acknowledged[qos2ARPacketID] = true;
        		publish_Q1(_SentQOS1Topic, _qos2Packet._qos2bufferID[qos2ARPacketID], _qos2Packet._qos2Plength[qos2ARPacketID]);
        		_qos2Packet._qos2CurrentIndex = tempPacketID;
        		
        	}
            else if(_qos2Packet._qos2Flag[qos2ARPacketID] == MQTTPUBREL)
            {
        		debugmqln("[PubSubClient]-- retrying QOS2 MQTTPUBREL--");
        		qos2Response(MQTTPUBREL | MQTTQOS1 , qos2ARPacketID+1);
        		_qos2Packet._qos2Flag[qos2ARPacketID] = MQTTPUBREL;   
        		_qos2Packet._qos2SentTime[qos2ARPacketID] = millis();   
        	}
		}
		
		qos2ARPacketID++;
    	if(qos2ARPacketID >= MQTT_QOS2_MAX_BUFFER)
    	{
    		qos2ARPacketID = 0;
    	}
        
        //-------------------------------

        if (_client->available()) 
        {
            uint8_t llen;
            uint16_t len = readPacket(&llen);
            uint16_t msgId = 0;
            uint8_t *payload;
            if (len > 0) 
            {
                lastInActivity = t;
                uint8_t type = this->buffer[0]&0xF0;
                if (type == MQTTPUBLISH) 
                {
                    Serial.println("[] got MQTTPUBLISH ");
                    if (callback) 
                    {
                        uint16_t tl = (this->buffer[llen+1]<<8)+this->buffer[llen+2]; /* topic length in bytes */
                        memmove(this->buffer+llen+2,this->buffer+llen+3,tl); /* move topic inside buffer 1 byte to front */
                        this->buffer[llen+2+tl] = 0; /* end the topic as a 'C' string with \x00 */
                        char *topic = (char*) this->buffer+llen+2;
                        // msgId only present for QOS>0
                        if ((this->buffer[0] & 0x06) == MQTTQOS1) 
                        {
                            Serial.println("[] calling call back for qos1");
                            msgId = (this->buffer[llen+3+tl]<<8)+this->buffer[llen+3+tl+1];
                            payload = this->buffer+llen+3+tl+2;
                            callback(topic,payload,len-llen-3-tl-2);

                            this->buffer[0] = MQTTPUBACK;
                            this->buffer[1] = 2;
                            this->buffer[2] = (msgId >> 8);
                            this->buffer[3] = (msgId & 0xFF);
                            _client->write(this->buffer,4);
                            Serial.println("[] sending MQTTPUBACK");
                            lastOutActivity = t;

                        } 
                        else 
                        {
                            Serial.println("[] calling call back for qos0");
                            payload = this->buffer+llen+3+tl;
                            callback(topic,payload,len-llen-3-tl);
                        }
                    }
                } 
                else if (type == MQTTPINGREQ) 
                {
                    Serial.println("[] got MQTTPINGREQ");
                    this->buffer[0] = MQTTPINGRESP;
                    this->buffer[1] = 0;
                    _client->write(this->buffer,2);
                    Serial.println("[] send MQTTPINGRESP");
                } 
                else if (type == MQTTPINGRESP) 
                {
                    Serial.println("[] got MQTTPINGRESP");
                    pingOutstanding = false;
                } 
                else if (type == MQTTPUBACK) 
                { 
          //debug   
                    Serial.println("[] got MQTTPUBACK");   
                	debugmq("*MQQT PUBACK mid:"); debugmqln(((buffer[2]<<8)+ buffer[3])); debugmq(" looking for:"); debugmqln(_QOS1MSGID);      
                    if (((buffer[2]<<8)+ buffer[3])==_QOS1MSGID)
                    { 
          //debug          debugmqln(" --- PUBACK SEEN:----");
                    _QOS1Acknowledged=true; 
                    debugmqln("[PubSubClient]--- Qos1 Acknowledged ---");
                	}
                } 
                else if(type == MQTTPUBREC)
                {
                    Serial.println("[] got MQTTPUBREC");
                	qos2MgsId = (buffer[2] << 8) + buffer[3];
                    Serial.print("qos2MgsId"); Serial.println(qos2MgsId);

                	if (qos2MgsId == _qos2Packet._qos2MgsID[qos2MgsId-1])
                    { 
                        //debug          
                		debugmq("[PubSubClient]--- PUBREC SEEN: ----for mid: ");
                		debugmqln(qos2MgsId);
                    	if(_qos2Packet._qos2Flag[qos2MgsId-1] == MQTTPUBLISH)
                    	{
                            qos2Response(MQTTPUBREL | MQTTQOS1 , qos2MgsId);
                    		_qos2Packet._qos2Flag[qos2MgsId-1] = MQTTPUBREL;   
                    		_qos2Packet._qos2SentTime[qos2MgsId-1] = millis(); 
                            Serial.print("send MQTTPUBREL for");
                            Serial.println(qos2MgsId);        
                    	}
                    // debugmqln("[PubSubClient]Qos1 Acknowledged");
                	}
                } 
                else if(type == MQTTPUBCOMP)
                {
                    Serial.println("[] got MQTTPUBCOMP");
                	qos2MgsId = (buffer[2] << 8)+ buffer[3];
                	if (qos2MgsId == _qos2Packet._qos2MgsID[qos2MgsId-1])
                    {
                		debugmq("[PubSubClient]--- Qos2 Acknowledged:--- for mid: ");
                		debugmqln(qos2MgsId);
                		_qos2Packet._qos2Acknowledged[qos2MgsId-1] = true;
                		_qos2Packet._qos2bufferID[qos2MgsId-1] = NULL;
                		_qos2Packet._qos2SentTime[qos2MgsId-1] = NULL;
                		_qos2Packet._qos2Flag[qos2MgsId-1] = MQTTPUBCOMP;
                	}
                }

            } 
            else if (!connected()) 
            {
                // readPacket has closed the connection
                return false;
            }
        }
        return true;
    }
    return false;
}

boolean PubSubClient::qos2Response(uint8_t header, uint16_t qMgsID)
{
	this->buffer[0] = header;
    this->buffer[1] = 2;
    this->buffer[2] = (qMgsID >> 8);
    this->buffer[3] = (qMgsID & 0xFF);
    return _client->write(this->buffer,4);
}

boolean PubSubClient::isqos2ack(uint8_t mid)
{
    // debugmq("[PubSubClient]qos2 ack:");
    // debugmqln(mid);
    return _qos2Packet._qos2Acknowledged[mid-1];
}

boolean PubSubClient::publish(const char* topic, const char* payload) 
{
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,false);
}

boolean PubSubClient::publish(const char* topic, const char* payload, boolean retained) 
{
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,retained);
}

boolean PubSubClient::publish(const char* topic, const uint8_t* payload, unsigned int plength) 
{
    return publish(topic, payload, plength, false);
}

boolean PubSubClient::publish(const char* topic, const uint8_t* payload, unsigned int plength, boolean retained) 
{
    if (connected()) 
    {
        if (this->bufferSize < MQTT_MAX_HEADER_SIZE + 2+strnlen(topic, this->bufferSize) + plength) 
        {
            // Too long
            Serial.println("[] too long");
            return false;
        }
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);

        // Add payload
        uint16_t i;
        for (i=0;i<plength;i++) 
        {
            this->buffer[length++] = payload[i];
        }

        // Write the header
        uint8_t header = MQTTPUBLISH;
        if (retained) 
        {
            header |= 1;
        }
        Serial.println("[] published");
        return write(header,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean PubSubClient::publish_Q1(const char* topic, const uint8_t* payload, unsigned int plength) 
{
    return publish_Q1(topic, payload, plength, NULL, false,false);
}
boolean PubSubClient::publish_Q1(const char* topic, const uint8_t* payload, unsigned int plength, uint8_t msgId) 
{
    
    return publish_Q1(topic, payload, plength, msgId, false,false);
}

boolean PubSubClient::publish_Q1(const char* topic, const uint8_t* payload, unsigned int plength, uint8_t mid, boolean retained, boolean QOS1_MSG_Repeat) 
{
    debugmqln("++ trying to publish..");
    if (connected()) 
    {
        if (MQTT_MAX_PACKET_SIZE < 5 + 2+strlen(topic) + plength) 
        {
            debugmq("[PubSubClient] too long packet");
            return false;
        }
        // Leave room in the buffer for header and variable length field
        uint16_t length = 5;
        length = writeString(topic,this->buffer,length);
        uint16_t i;
        strncpy(_SentQOS1Topic,topic,20);                                   
        // for (i=0;i<plength;i++) { _SentQOS1buffer[i]=payload[i];/*debugmq("Data ")*/}         
        // _SentQOS1buffer[sizeof(payload)-1]='\0';
        _SentQOS1buffer = payload;
        _SENTQOS1Length = plength;
        Serial.print("_QOS_TYPE"); Serial.println(_QOS_TYPE);

        if(_QOS_TYPE==1)
        {
            Serial.println("$$ qos = 1");

   			  // memset(_SentQOS1buffer,'\0',MQTT_MAX_PACKET_SIZE);      
                                                   
              if(QOS1_MSG_Repeat==false) {_QOS1MSGID= _QOS1MSGID +1 ;}     // If last msg was acknowledged then increment id , else we are retransmitting, so use last msgid   
              if (_QOS1MSGID==0){_QOS1MSGID=1;}                            // msgid 0 is a disconnect
              this->buffer[length]=(_QOS1MSGID >> 8);                            //add msg id for qos1
              this->buffer[length+1]= (_QOS1MSGID & 0xFF);                       // 
              length=length+2;                                             //
              _QOS1_SENT_TIME=millis();                                    // set time for PUBACK check
              _QOS1Acknowledged=false;                                     // set Acknowledged flag false    
      		//debug      
              debugmq("[PubSubClient]*MQQT qos1 publish mid:"); debugmqln(_QOS1MSGID); 
      	}
        else if(_QOS_TYPE==2)
        {
            Serial.println("$$ qos = 2");

      		if(_qos2Packet._qos2CurrentIndex>=MQTT_QOS2_MAX_BUFFER)
      		{
      			_qos2Packet._qos2CurrentIndex = 0;
      		}

      		qos2IndexRetry = 0;
            if(mid)
            {
                if(_qos2Packet._qos2Acknowledged[mid-1] == false)
                {
                    debugmqln("[PubSubClient]Buffer is full....processing queue.>>>>>");
                    return false;
                }
                else
                {
                    _qos2Packet._qos2CurrentIndex = (mid-1);
                    Serial.print("qos2 current index: "); Serial.println( _qos2Packet._qos2CurrentIndex);
                }
            }
            else
            {
                while(_qos2Packet._qos2Acknowledged[_qos2Packet._qos2CurrentIndex] == false)
                {
                    _qos2Packet._qos2CurrentIndex++;
                    if(_qos2Packet._qos2CurrentIndex>=MQTT_QOS2_MAX_BUFFER)
                    {
                        _qos2Packet._qos2CurrentIndex = 0;
                    }
                    qos2IndexRetry++;
                    if(qos2IndexRetry >= MQTT_QOS2_MAX_BUFFER){
                        debugmqln("[PubSubClient]Buffer is full....processing queue.");
                        return false;
                    }
                }
            }
      		

      		_qos2Packet._qos2Acknowledged[_qos2Packet._qos2CurrentIndex] = false;
      		_qos2Packet._qos2bufferID[_qos2Packet._qos2CurrentIndex] = (uint8_t*)payload;
      		_qos2Packet._qos2Plength[_qos2Packet._qos2CurrentIndex] = plength;
      		this->buffer[length] = (_qos2Packet._qos2MgsID[_qos2Packet._qos2CurrentIndex] >> 8);                            //add msg id for qos1
            this->buffer[length+1] = (_qos2Packet._qos2MgsID[_qos2Packet._qos2CurrentIndex] & 0xFF);                       // 
            length=length+2;
            _qos2Packet._qos2Flag[_qos2Packet._qos2CurrentIndex] = MQTTPUBLISH;
            _qos2Packet._qos2SentTime[_qos2Packet._qos2CurrentIndex]=millis();
            
            //debug
            debugmq("[PubSubClient]*MQQT qos2 publish MGS id:"); debugmqln(_qos2Packet._qos2MgsID[_qos2Packet._qos2CurrentIndex]);

            _qos2Packet._qos2CurrentIndex++;      			
      	}

                            
        for (i=0;i<plength;i++) {
            this->buffer[length++] = payload[i];
        }
        //debug
        // debugmq("Full Data With payload: ");
        // for (i=0;i<=length;i++) {
        // 	debugmq(this->buffer[i]);
        // 	debugmq(" ");
        //     // this->buffer[length++] = payload[i];
        // }

        // debugmqln("");
        uint8_t header;

        if(_QOS_TYPE == 1)
        {
        	header = MQTTPUBLISH|MQTTQOS1;      
        }else if(_QOS_TYPE == 2)
        {
        	header = MQTTPUBLISH|MQTTQOS2;
        }
                               // Main change so it sends qos 1     
        if (retained) { header |= 1; }    
                                                // set for follow up
     //debug  if((_QOS1MSGID>=10)&&(QOS1_MSG_Repeat==false)) {debugmq("testing retry");return true;}    // test - deliberately do not send - so that retry will be activated
        return write(header,this->buffer,length-5);
    }
    else
    {
        Serial.println("not connected");
    }
    return false;
}

boolean PubSubClient::qos2Full(void)
{
	if(qos2IndexRetry >= MQTT_QOS2_MAX_BUFFER)
    {
		return true;
	}
    else
    {
		return false;
	}
}

uint16_t PubSubClient::qos2Empty(void)
{
	uint16_t i = 0; 
	buffPending = 0;
	while(i <MQTT_QOS2_MAX_BUFFER)
	{
		if(_qos2Packet._qos2Acknowledged[i] == false)
        {
			buffPending++;
		}
		i++;
	}

	return buffPending;
}

void PubSubClient::qos2ResetBuff(void)
{
	uint16_t i = 0; 
	// buffPending = 0;
	while(i <MQTT_QOS2_MAX_BUFFER)
	{
		_qos2Packet._qos2Acknowledged[i] = true;
		i++;
	}
    Serial.println("clear qos2 buffer>>");
}


uint8_t* PubSubClient::qos2BufferAddr(void)
{
   	uint16_t tempBufID = 0;
   	while (tempBufID < MQTT_QOS2_MAX_BUFFER)
   	{
   		if(_qos2Packet._qos2Acknowledged[tempBufID] == false)
   		{
   			return _qos2Packet._qos2bufferID[tempBufID];

   		}
   		tempBufID++;
   	}
   	return NULL;   	
}

boolean PubSubClient::publish_P(const char* topic, const char* payload, boolean retained) 
{
    return publish_P(topic, (const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0, retained);
}

boolean PubSubClient::publish_P(const char* topic, const uint8_t* payload, unsigned int plength, boolean retained) {
    uint8_t llen = 0;
    uint8_t digit;
    unsigned int rc = 0;
    uint16_t tlen;
    unsigned int pos = 0;
    unsigned int i;
    uint8_t header;
    unsigned int len;
    int expectedLength;

    if (!connected()) {
        return false;
    }

    tlen = strnlen(topic, this->bufferSize);

    header = MQTTPUBLISH;
    if (retained) {
        header |= 1;
    }
    this->buffer[pos++] = header;
    len = plength + 2 + tlen;
    do {
        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        this->buffer[pos++] = digit;
        llen++;
    } while(len>0);

    pos = writeString(topic,this->buffer,pos);

    rc += _client->write(this->buffer,pos);

    for (i=0;i<plength;i++) 
    {
        rc += _client->write((char)pgm_read_byte_near(payload + i));
    }

    lastOutActivity = millis();

    expectedLength = 1 + llen + 2 + tlen + plength;

    return (rc == expectedLength);
}

boolean PubSubClient::beginPublish(const char* topic, unsigned int plength, boolean retained) 
{
    if (connected()) 
    {
        // Send the header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);
        uint8_t header = MQTTPUBLISH;
        if (retained) 
        {
            header |= 1;
        }
        size_t hlen = buildHeader(header, this->buffer, plength+length-MQTT_MAX_HEADER_SIZE);
        uint16_t rc = _client->write(this->buffer+(MQTT_MAX_HEADER_SIZE-hlen),length-(MQTT_MAX_HEADER_SIZE-hlen));
        lastOutActivity = millis();
        return (rc == (length-(MQTT_MAX_HEADER_SIZE-hlen)));
    }
    return false;
}

int PubSubClient::endPublish() 
{
 return 1;
}

size_t PubSubClient::write(uint8_t data) 
{
    lastOutActivity = millis();
    return _client->write(data);
}

size_t PubSubClient::write(const uint8_t *buffer, size_t size) 
{
    lastOutActivity = millis();
    return _client->write(buffer,size);
}

size_t PubSubClient::buildHeader(uint8_t header, uint8_t* buf, uint16_t length) 
{
    uint8_t lenBuf[4];
    uint8_t llen = 0;
    uint8_t digit;
    uint8_t pos = 0;
    uint16_t len = length;
    do 
    {

        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) 
        {
            digit |= 0x80;
        }
        lenBuf[pos++] = digit;
        llen++;
    } while(len>0);

    buf[4-llen] = header;
    for (int i=0;i<llen;i++) 
    {
        buf[MQTT_MAX_HEADER_SIZE-llen+i] = lenBuf[i];
    }
    return llen+1; // Full header size is variable length bit plus the 1-byte fixed header
}

boolean PubSubClient::write(uint8_t header, uint8_t* buf, uint16_t length) 
{
    uint16_t rc;
    uint8_t hlen = buildHeader(header, buf, length);
    // debugmqln((char*)buf);
#ifdef MQTT_MAX_TRANSFER_SIZE
    uint8_t* writeBuf = buf+(MQTT_MAX_HEADER_SIZE-hlen);

    uint16_t bytesRemaining = length+hlen;  //Match the length type
    uint8_t bytesToWrite;
    boolean result = true;
    while((bytesRemaining > 0) && result) 
    {
        bytesToWrite = (bytesRemaining > MQTT_MAX_TRANSFER_SIZE)?MQTT_MAX_TRANSFER_SIZE:bytesRemaining;
        rc = _client->write(writeBuf,bytesToWrite);
        result = (rc == bytesToWrite);
        bytesRemaining -= rc;
        writeBuf += rc;
    }
    debugmqln("[PubSubClient] write output:"+result);
    return result;
#else
    rc = _client->write(buf+(MQTT_MAX_HEADER_SIZE-hlen),length+hlen);
    lastOutActivity = millis();
    debugmq("[PubSubClient] write output rc: ");
    debugmq(rc);
    debugmq(" len: "); 
    uint16_t tlen = hlen+length;
    debugmqln(tlen);
    return (rc == hlen+length);
#endif
}

boolean PubSubClient::subscribe(const char* topic) 
{
    return subscribe(topic, 0);
}

boolean PubSubClient::subscribe(const char* topic, uint8_t qos) 
{
    size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0) 
    {
        return false;
    }
    if (qos > 1) 
    {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) 
    {
        // Too long
        return false;
    }
    if (connected()) 
    {
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) 
        {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString((char*)topic, this->buffer,length);
        this->buffer[length++] = qos;
        Serial.print("[] subcribing to "); Serial.println(topic);
        return write(MQTTSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean PubSubClient::unsubscribe(const char* topic) 
{
	size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0) {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) 
    {
        // Too long
        return false;
    }
    if (connected()) 
    {
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) 
        {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString(topic, this->buffer,length);
        return write(MQTTUNSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

void PubSubClient::disconnect() 
{
    this->buffer[0] = MQTTDISCONNECT;
    this->buffer[1] = 0;
    _client->write(this->buffer,2);
    _state = MQTT_DISCONNECTED;
    _client->flush();
    _client->stop();
    lastInActivity = lastOutActivity = millis();
}

uint16_t PubSubClient::writeString(const char* string, uint8_t* buf, uint16_t pos) 
{
    const char* idp = string;
    uint16_t i = 0;
    pos += 2;
    while (*idp) {
        buf[pos++] = *idp++;
        i++;
    }
    buf[pos-i-2] = (i >> 8);
    buf[pos-i-1] = (i & 0xFF);
    return pos;
}


boolean PubSubClient::connected() 
{
    boolean rc;
    if (_client == NULL ) 
    {
        Serial.println("** client not found");
        rc = false;
    } 
    else 
    {
        rc = (int)_client->connected();
    
        if (!rc) 
        {
            if (this->_state == MQTT_CONNECTED) 
            {
                this->_state = MQTT_CONNECTION_LOST;
                _client->flush();
                _client->stop();
                Serial.println("** connection lost");
            }
            Serial.print("rc:"); Serial.println(rc);
            Serial.print("mqtt state: "); Serial.println(this->_state);
        } 
        else 
        {
            // Serial.println("** mqtt connection connected");
            return this->_state == MQTT_CONNECTED;
            
        }
    }
    return rc;
}

PubSubClient& PubSubClient::setServer(uint8_t * ip, uint16_t port) 
{
    IPAddress addr(ip[0],ip[1],ip[2],ip[3]);
    return setServer(addr,port);
}

PubSubClient& PubSubClient::setServer(IPAddress ip, uint16_t port) 
{
    this->ip = ip;
    this->port = port;
    this->domain = NULL;
    return *this;
}

PubSubClient& PubSubClient::setServer(const char * domain, uint16_t port) 
{
    this->domain = domain;
    this->port = port;
    return *this;
}

PubSubClient& PubSubClient::setCallback(MQTT_CALLBACK_SIGNATURE) 
{
    this->callback = callback;
    return *this;
}

PubSubClient& PubSubClient::setClient(Client& client)
{
    this->_client = &client;
    return *this;
}

PubSubClient& PubSubClient::setStream(Stream& stream)
{
    this->stream = &stream;
    return *this;
}

int PubSubClient::state() 
{
    return (int)this->_state;
}

boolean PubSubClient::setBufferSize(uint16_t size) 
{
    if (size == 0) 
    {
        // Cannot set it back to 0
        return false;
    }
    if (this->bufferSize == 0) 
    {
        this->buffer = (uint8_t*)malloc(size);
    } 
    else 
    {
        uint8_t* newBuffer = (uint8_t*)realloc(this->buffer, size);
        if (newBuffer != NULL) 
        {
            this->buffer = newBuffer;
        } 
        else 
        {
            return false;
        }
    }
    this->bufferSize = size;
    return (this->buffer != NULL);
}

uint16_t PubSubClient::getBufferSize() 
{
    return this->bufferSize;
}
PubSubClient& PubSubClient::setKeepAlive(uint16_t keepAlive) 
{
    this->keepAlive = keepAlive;
    return *this;
}
PubSubClient& PubSubClient::setSocketTimeout(uint16_t timeout) 
{
    this->socketTimeout = timeout;
    return *this;
}
