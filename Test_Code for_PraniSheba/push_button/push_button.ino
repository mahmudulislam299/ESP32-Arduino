
const int PushButton = 13;
const int buzzer = 25;
const int led = 2;

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  pinMode(PushButton, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop()

{
  int Push_button_state = digitalRead(PushButton);
 
  if ( Push_button_state == HIGH )
  { 
    Serial.println("high");
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(2000);
  }
  else 
  {
  Serial.println("low");
  digitalWrite(buzzer,LOW);
  digitalWrite(led,LOW);
  }
}
