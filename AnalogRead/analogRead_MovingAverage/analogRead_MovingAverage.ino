const int dataPin = 36;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  float x = movingAverage(analogRead(dataPin));
  static uint32_t millisPrev = 0;

  if (millis() - millisPrev > 2000)
  {
    Serial.println(x);
    millisPrev = millis();
  }
  

}


float movingAverage(float value) 
{
  const byte nvalues = 8;             // Moving average window size

  static byte current = 0;            // Index for current value
  static byte cvalues = 0;            // Count of values read (<= nvalues)
  static float sum = 0;               // Rolling sum
  static float values[nvalues];

  sum += value;

  // If the window is full, adjust the sum by deleting the oldest value
  if (cvalues == nvalues)
  {
    sum -= values[current];
  }

  values[current] = value;          // Replace the oldest with the latest

  if (++current >= nvalues)
  {
    current = 0;
  }

  if (cvalues < nvalues)
  {
    cvalues += 1;
  }

  return sum/cvalues;
}
