
void setup()
{ 
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() 
{

  if (Serial2.available())
  {
    Serial.write(Serial2.read());
  }
  
  if (Serial.available())
  {
    while(Serial.available())
    { 
      Serial2.write(Serial.read());
    }
  
    Serial2.println();
  
  }

}
