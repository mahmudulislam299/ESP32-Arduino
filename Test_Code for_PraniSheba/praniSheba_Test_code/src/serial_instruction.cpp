#include "serial_instruction.h"
#include "Arduino.h"

int getInstructionID() {
	if (Serial.available() > 0){
		int id = Serial.parseInt();
		return id;
	} else {
		return 0;
	}
}

void printInstruction() {
	Serial.println("<------- Instruction -------------->");
	Serial.println(" Press 1 to show instruction");
	Serial.println(" Press 2 to check all automatically");
	Serial.println(" Press 3 to check I2C bus");
	Serial.println(" Press 4 to check RTC");
	Serial.println(" Press 5 to read Flash");
	Serial.println(" Press 6 to write in Flash");
	Serial.println(" Press 7 to eraseSector sector in Flash");
	Serial.println(" Press 8 to erase full Flash chip");
	Serial.println(" Press 9 to check NH3 CH4 Sensors");
	Serial.println(" Press 10 to check Hum & Temp Sensors");
	Serial.println(" Press 11 to check LEDs");
	Serial.println(" Press 12 to check NH3 CH4 Sensors");
	Serial.println(" Press 13 to check FRAM");


	Serial.println("<---------------------------------->");
}

