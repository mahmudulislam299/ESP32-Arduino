
void setup()
{ 
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() 
{
  // TinyGsmAutoBaud();

 if (Serial2.available())
 {
   Serial.write(Serial2.read());
 }
 
 if (Serial.available())
 {
   while(Serial.available())
   { 
     uint8_t c = Serial.read();
     if(c == '$')
     {
        Serial2.write(0x1a);
     }
     else
     {
       Serial2.write(c);
     }
   }
 
   Serial2.println();
 
 }

}

  void TinyGsmAutoBaud() 
  {
  
    static uint32_t rates[] = {9600, 115200, 57600, 1200, 2400, 4800, 19200, 38400,  74400, 74880,
                             230400, 460800, 14400, 28800};

    for (uint8_t i = 0; i < sizeof(rates) / sizeof(rates[0]); i++) 
    {
      uint32_t rate = rates[i];
   

    
      Serial.print("Trying baud rate"); Serial.println(rate);
      Serial2.begin(rate);
      delay(10);
      for (int j = 0; j < 10; j++) 
      {
        Serial2.print("AT\r\n");
        delay(5);
        String input = Serial2.readString();
        Serial.println(input);
        if (input.indexOf("OK") >= 0) 
        {
          Serial.print("Modem responded at rate");
          Serial.println(rate);
        }
      }
    }
 
}
