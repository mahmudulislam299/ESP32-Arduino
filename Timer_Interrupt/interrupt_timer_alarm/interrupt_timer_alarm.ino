volatile int count;    // Trigger 
int totalInterrupts;   // counts the number of triggering of the alarm

#define LED_PIN 2

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Code with critica section
void IRAM_ATTR onTime() {
   portENTER_CRITICAL_ISR(&timerMux);
   count++;
   Serial.println("jj");
   portEXIT_CRITICAL_ISR(&timerMux);
}

// Code without critical section
/*void IRAM_ATTR onTime() {
   count++;
}*/

void setup() {
   Serial.begin(115200);
  
   // Configure LED output
   pinMode(LED_PIN, OUTPUT);
   digitalWrite(LED_PIN, LOW);

   // Configure the Prescaler at 80 the quarter of the ESP32 is cadence at 80Mhz
   // 80000000 / 80 = 1000000 tics / seconde
   timer = timerBegin(0, 80, true);                
   timerAttachInterrupt(timer, &onTime, true);    
    
   // Sets an alarm to sound every second
   timerAlarmWrite(timer, 1000000, true);           
   timerAlarmEnable(timer);
}

void loop() {
    if (count > 0) {
       // Comment out enter / exit to deactivate the critical section 
       portENTER_CRITICAL(&timerMux);
       count--;
       portEXIT_CRITICAL(&timerMux);

       totalInterrupts++;
       Serial.print("totalInterrupts");
       Serial.println(totalInterrupts);
       if ( totalInterrupts%2 == 0) {
         // Lights up the LED if the counter is even 
         digitalWrite(LED_PIN, HIGH);
       } else {
         // Then swith off
         digitalWrite(LED_PIN, LOW);
       }


       delay(10000);
    }
}
