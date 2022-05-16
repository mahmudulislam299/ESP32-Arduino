int LED= 2;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(LED,HIGH);
  Serial.println("on");
  delay(1000);
  digitalWrite(LED,LOW);
  Serial.println("off");
}
