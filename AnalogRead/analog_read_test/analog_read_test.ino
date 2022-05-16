// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin1 = 36; //A0 MQ4
const int potPin2 = 39; //A1 MQ135
                        //A2 

// variable for storing the potentiometer value
int potValue1 = 0;
int potValue2 = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  sensor1();
  sensor2();
  Serial.println();
  delay(2000);
}

void sensor1()
{
  // Reading potentiometer value
  potValue1 = analogRead(potPin1);
  float voltage= potValue1 / 4096.0;
  voltage = voltage * 3.3 +.18;
  Serial.print(potValue1); 
  Serial.print("   |   vol:  ");
  Serial.print(voltage);
  Serial.print("   |  actual vol:  ");
  Serial.println(3*voltage);
}

void sensor2()
{
  // Reading potentiometer value
  potValue2 = analogRead(potPin2);
  float voltage= potValue2 / 4096.0;
  voltage = voltage * 3.3 +.18;
  Serial.print(potValue2); 
  Serial.print("   |   vol:  ");
  Serial.print(voltage);
  Serial.print("   |  actual vol:  ");
  Serial.println(3*voltage);
}


// subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(1);        // delay in between reads for stability
