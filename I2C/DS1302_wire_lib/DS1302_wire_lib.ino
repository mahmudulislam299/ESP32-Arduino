#include <Wire.h>

// 1 set the time of the clock
// 2 read the time of the clock
// 3 set the interuppt pulse rate - sqw - frequency

#define DS1302_ADDRESS 0x68
#define DS1302_SECONDS_REG_READ 0x81
#define DS1302_SECONDS_REG_WRITE 0x80
#define DS1302_CONTROL_REG 0x0E
#define DS1302_REG_TIMEDATE_BURST 0xBE
#define THREEWIRE_READFLAG 0x01
#define DS1302_REG_WP 0x8E
#define DS1302_WP 7



typedef struct timeParameters
{
  uint8_t ss;
  uint8_t mm;
  uint8_t hh;
  uint8_t dy;
  uint8_t d;
  uint8_t m;
  uint8_t y;
};

static uint8_t convertValueIN(uint8_t value);
static uint8_t convertValueOUT(uint8_t value);


void setINTFreq(uint8_t freqOption)
{
  /*
   * option 1: 1 Hz
   * option 2: 1.024khz
   * option 3: 4.096khz
   * option 4: 8.196khz
   * option 5: OFF
   */

   Wire.beginTransmission(DS1302_ADDRESS);
   Wire.write(DS1302_CONTROL_REG);
   Wire.endTransmission();

   Wire.requestFrom(DS1302_ADDRESS,1);
   byte currentConfig = Wire.read();

   if (freqOption == 5)
   {
    byte offConfig = currentConfig | 0b00000100;

    Wire.beginTransmission(DS1302_ADDRESS);
    Wire.write(DS1302_CONTROL_REG);
    Wire.write(offConfig);
    Wire.endTransmission();    
   }
   else if (freqOption <5)
   {
      uint8_t option = freqOption - 1;
      byte newConfig = currentConfig & 0b11100111; // to clear bit4 and bit3(RS1 and RS2)
      newConfig = currentConfig & 0b11111011;

      newConfig = newConfig | (option << 3);

      Wire.beginTransmission(DS1302_ADDRESS);
      Wire.write(DS1302_CONTROL_REG);
      Wire.write(newConfig);
      Wire.endTransmission();      
   }
   delay(5);
   
}

void setTime(timeParameters * timeVals)
{
  /*
   * From datasheet
   * 0 - seconds
   * 1 - minutes
   * 2 - hours
   * 3 - day
   * 4 - date
   * 5 - month
   * 6 - year
   */

   Wire.beginTransmission(DS1302_REG_TIMEDATE_BURST);
//   Wire.write(DS1302_SECONDS_REG_WRITE);

   Wire.write(convertValueOUT(timeVals->ss));
   Wire.write(convertValueOUT(timeVals->mm));
   Wire.write(convertValueOUT(timeVals->hh));
   Wire.write(convertValueOUT(timeVals->d));
   Wire.write(convertValueOUT(timeVals->m));
   Wire.write(0); // bcoz not interested in day
   Wire.write(convertValueOUT(timeVals->y)-2000);
   Wire.write(0);
   Wire.endTransmission();
   delay(5); // 5 ms delay to complete the transmission
   
}

void readTime(timeParameters *timeVals)
{
  Wire.beginTransmission(DS1302_REG_TIMEDATE_BURST);
//  Wire.write(DS1302_SECONDS_REG_READ);
//  Wire.endTransmission();

//  Wire.requestFrom(DS1302_ADDRESS,(byte)sizeof(timeParameters));

  timeVals->ss = convertValueIN(Wire.read());
  timeVals->mm = convertValueIN(Wire.read());
  timeVals->hh = convertValueIN(Wire.read());
  timeVals->d = convertValueIN(Wire.read());
  timeVals->m = convertValueIN(Wire.read());

  Wire.read(); // we dont want to save day value
  timeVals->y = convertValueIN(Wire.read());
  Wire.read(); // we dont want to save day value
  Wire.endTransmission();
  delay(5);
}

void printTime(timeParameters *t)
{
  Serial.print(t->y);
  Serial.print(" ");
  Serial.print(t->m);
  Serial.print(" ");
  Serial.print(t->d);
  Serial.print(" ");
  Serial.print(t->hh);
  Serial.print(" ");
  Serial.print(t->mm);
  Serial.print(" ");
  Serial.print(t->ss);
  Serial.println();
}

static uint8_t convertValueIN(uint8_t value)
{
  uint8_t convertedVal = value - 6 * (value >> 4);
  return convertedVal;
}

static uint8_t convertValueOUT(uint8_t value)
{
  uint8_t convertedVal = value + 6 * (value/10);
  return convertedVal; 
}

int timeTrigs = 0;
void timeFunc()
{
  timeTrigs+=1;
}

timeParameters foo;


uint8_t getReg(uint8_t regAddress)
{

  Wire.beginTransmission(regAddress | THREEWIRE_READFLAG);
  uint8_t regValue = Wire.read();
  Wire.endTransmission();
  return regValue;
}

void setReg(uint8_t regAddress, uint8_t regValue)
{
  Wire.beginTransmission(regAddress);
  Wire.write(regValue);
  Wire.endTransmission();
}

bool GetIsRunning()
{
  uint8_t ch = getReg(DS1302_SECONDS_REG_WRITE);
  return !(ch & _BV(DS1302_SECONDS_REG_WRITE));
}

bool GetIsWriteProtected()
{
  uint8_t wp = getReg(DS1302_REG_WP);
  return !!(wp & _BV(DS1302_WP));
}

void SetIsWriteProtected(bool isWriteProtected)
{
  uint8_t wp = getReg(DS1302_REG_WP);
  if (isWriteProtected)
  {
      wp |= _BV(DS1302_WP);
  }
  else
  {
      wp &= ~_BV(DS1302_WP);
  }
  setReg(DS1302_REG_WP, wp);
}

    
void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  Serial.println("start DS1302 RTC");

  timeParameters time ={0,30,11,0,16,12,21};
  setTime(&time);
  Serial.print("write protected : ");
  Serial.println(GetIsWriteProtected());
  SetIsWriteProtected(false);
  Serial.print("write protected : ");
  Serial.println(GetIsWriteProtected());
  

}

 
void loop() 
{
  timeParameters t ;
  readTime(&t);
  printTime(&t);
  Serial.print("get running : ");
  Serial.println(GetIsRunning());
  Serial.print("write protected : ");
  Serial.println(GetIsWriteProtected());
  delay(5000);
}
