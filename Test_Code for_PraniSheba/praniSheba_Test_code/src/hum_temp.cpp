#include "hum_temp.h"
#include "lib\SHT21-Arduino-Library\SHT21.h"
#include "Arduino.h"


SHT21 sht;

void humTempSensorBegin() {
	sht.begin();
}

void checkHumTempSensor() {
	float temp = sht.getTemperature();
	if(temp > 5 && temp < 100) {
		Serial.print("temp ok : ");
		Serial.println(temp);
	} else {
		Serial.println("temp NOK");
	}


	float hum = sht.getHumidity();
	if(hum > 5 && hum < 100) {
		Serial.print("hum ok : ");
		Serial.println(hum);
	} else {
		Serial.println("hum NOK");
	}
}