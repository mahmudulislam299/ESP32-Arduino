#include "ringQ.h"
#include "Serial.h"


#define BUFFER_LEN   100 
#define DATA_BUFFER_LEN 40

uint8_t *generateData(uint8_t *buff, uint16_t len);
void dataPrint(uint8_t *buff, uint16_t len);


uint8_t data_buff[DATA_BUFFER_LEN];


uint8_t ringQBuff[BUFFER_LEN];

struct ramq_t *ringqObj;

qObj_t *tailObj;





void setup() {
  SerialBegin(115200);
  Serial.begin(115200);
 
  ringqObj = ramqNew(ringQBuff, BUFFER_LEN);

  randomSeed(micros());

}



void loop() {
  if(Serial.available())
  {
    char a = Serial.read();
    if(a == '1')
    {
      memset(data_buff, '\0', DATA_BUFFER_LEN);
      uint16_t len = random(15,20);
      generateData(data_buff,len);
      ramqPush(ringqObj,data_buff,len);
      Serial.println("Reading Data Before Push: ");
      dataPrint(data_buff,len);
    }else if(a == '2')
    {
      tailObj = ramqPop(ringqObj);
      if(tailObj)
      {
        memset(data_buff, '\0', DATA_BUFFER_LEN);
        memcpy(data_buff, (tailObj ->ptr + sizeof(struct qObj_t)), tailObj->len);
        Serial.println("Reading Data After Pop: ");
        dataPrint(data_buff,tailObj->len);
      }      
    }
  }
  
}


uint8_t *generateData(uint8_t *buff, uint16_t len)
{
  uint8_t *tBuff = buff;
  for(int i=0; i<len; i++)
  {
    tBuff[i] = random(255);
  }
  return buff;
}


void dataPrint(uint8_t *buff, uint16_t len)
{
  Serial.print("Data Length: ");
  Serial.println(len);
  uint8_t *tBuff = buff;
  for(int i=0; i<len; i++)
  {
    Serial.print(tBuff[i] , HEX);
    Serial.print(" ");
  }
  Serial.println("");
//  return buff;
}
