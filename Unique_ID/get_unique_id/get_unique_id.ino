void setup() {
  Serial.begin(115200);
  Serial.println("hello world");
}

void loop() {
  uint64_t chipid = ESP.getEfuseMac();
  Serial.println("chip ID:");
  Serial.println(chipid);
  delay(2000);

}
