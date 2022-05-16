const int numReadings = 10;

int readings1[numReadings], readings2[numReadings];      // the readings from the analog input
int readIndex1 = 0, readIndex2 = 0;              // the index of the current reading
int total1 = 0, total2 = 0;                  // the running total
int average1 = 0, average2 = 0;                // the average

const int inputPin1 = 36; 
const int inputPin2 = 39;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(115200);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
  }
}

void loop()
{
//  sensor1();
  sensor2();
}
void sensor1() 
{

  total1 = total1 - readings1[readIndex1];
  readings1[readIndex1] = analogRead(inputPin1);
  total1 = total1 + readings1[readIndex1];
  readIndex1 = readIndex1 + 1;

  if (readIndex1 >= numReadings) 
  {
    readIndex1 = 0;
  }

  // calculate the average:
  average1 = total1 / numReadings;
  // send it to the computer as ASCII digits
  int potValue1 = average1;
  float voltage= potValue1 / 4096.0;
  voltage = voltage * 3.3 +.18;

  static uint32_t millisPrev = 0;

  if (millis()- millisPrev > 2000)
  {  
    Serial.print(potValue1); 
    Serial.print("   |   vol:  ");
    Serial.print(voltage);
    Serial.print("   |  actual vol:  ");
    Serial.println(3*voltage);
    millisPrev = millis();
  }
}

void sensor2() {

  total2 = total2 - readings2[readIndex2];
  readings2[readIndex2] = analogRead(inputPin2);
  total2 = total2 + readings2[readIndex2];
  readIndex2 = readIndex2 + 1;

  if (readIndex1 >= numReadings) 
  {
    readIndex1 = 0;
  }

  // calculate the average:
  average2 = total2 / numReadings;
  // send it to the computer as ASCII digits
  int potValue2 = average2;
  float voltage= potValue2 / 4096.0;
  voltage = voltage * 3.3 +.18;

  static uint32_t millisPrev2 = 0;

  if (millis()- millisPrev2 > 2000)
  {  
    Serial.print(potValue2); 
    Serial.print("   |   vol:  ");
    Serial.print(voltage);
    Serial.print("   |  actual vol:  ");
    Serial.println(3*voltage);
    millisPrev2 = millis();
  }
}
