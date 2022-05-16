int heartbeatPin = 27; // The Arduino will send the heartbeat at this output pin.
int heartbeatInterval = 4000; // Heartbeat will be sent to the 555 timer at this interval, in milliseconds.
int i;

void heartbeat() 
{

  Serial.println("Heartbeat sent!");
//  pinMode(heartbeatPin, OUTPUT);
//  digitalWrite(heartbeatPin,LOW);
//  
//  delay(1); // Should be enough time to pulse to get the 555 to recognize it.
//  pinMode(heartbeatPin, INPUT);

//    pinMode(heartbeatPin, OUTPUT);
    digitalWrite(heartbeatPin, HIGH);
    delay(1);
    digitalWrite(heartbeatPin, LOW);
//    pinMode(heartbeatPin, INPUT);
}

void setup() 
{
    pinMode(heartbeatPin, OUTPUT);
    digitalWrite(heartbeatPin, LOW);
    Serial.begin(115200);
    Serial.println("*** ESP32 reset ***");    
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    i = Serial.parseInt();

    // prints the received integer
    Serial.print("I received: ");
    Serial.println(i);
  }
  
  static uint32_t millisPrev = 0;

  if (millis() - millisPrev > 3000)
  {
    if( i!=1)
    {
      heartbeat();
    }
    Serial.println(".");
    millisPrev = millis();
  }
}
