#include "led.h"
#include "lib\ShiftRegister74HC595\src\ShiftRegister74HC595.h"
#include "Arduino.h"
#include "param.h"

// parameters: (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595<TOTAL_SR> sr(SR_DATA, SR_CLOCK, SR_LATCH);



void led_begin()
{
// #if defined(SR_PWM)
//   pinMode(SR_PWM, OUTPUT);
//   digitalWrite(SR_PWM, LOW);
// #endif
  //analogWrite(SR_PWM,230);
  sr.setAllLow(); // set all pins LOW
	delay(500);
	sr.setAllHigh();
	delay(2000);
	sr.setAllLow();
  
}

void led_blink()
{
  //  sr.setAllHigh(); // set all pins HIGH
  //  delay(500);

  //  sr.setAllLow(); // set all pins LOW
  //  delay(500);
  for (int i = 0; i < 21; i++)
  {
    sr.set(i, HIGH);
    delay(500);
    sr.set(i, LOW);
  }
  //   sr.set(15, HIGH);
}

void led_blink_specific() {
	Serial.println("Enter LED No: ");
	while(!Serial.available());
	int ledNo = Serial.parseInt();
	Serial.print("LED No: ");
	Serial.println(ledNo);
	sr.set(ledNo,HIGH);
	delay(1000);
	sr.set(ledNo, LOW);
}
