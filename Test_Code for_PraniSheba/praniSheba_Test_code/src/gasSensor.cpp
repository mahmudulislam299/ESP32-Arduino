#include "gasSensor.h"
#include "param.h"
#include "Arduino.h"

void checkAllGasSensor(){
	uint32_t mq4_val = analogRead(MQ4_PIN);
	uint32_t mq135_val = analogRead(MQ135_PIN);
	uint32_t mq2_val = analogRead(MQ2_PIN);

	Serial.print(mq4_val);
	if(mq4_val>0){
		Serial.print("  :mq4 ok | ");
	} else {
		Serial.print("   :mq4 Nok | ");
	}

	Serial.print(mq135_val);
	if(mq135_val>0){
		Serial.print("  :mq135 ok | ");
	} else {
		Serial.print("  :mq135 Nok | ");
	}


	Serial.print(mq2_val);
	if(mq2_val>0){
		Serial.println("   :mq2 ok");
	} else {
		Serial.println("   :mq2 Nok");
	}
}