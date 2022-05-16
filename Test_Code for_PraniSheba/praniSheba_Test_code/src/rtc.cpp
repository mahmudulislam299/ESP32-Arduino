#include "rtc.h"
#include <Wire.h>
#include "Arduino.h"

#define DS1307_ADDRESS 0x68
byte zero = 0x00; //workaround for issue #527

int second ; int m ;
int hour;
int weekday;
int monthDay;
int month;
int year;

void printDate();
bool getdate();
byte bcdToDec(byte val);
byte decToBcd(byte val);
void setDateTime();


void rtcCheck() {

	setDateTime();

	if(getdate()) {
		printDate();
		Serial.println("\n\nresult: RTC OK------------------->");
		
	} else {
		Serial.println("result: RTC not OK------------------->");
	}



}

void setDateTime() {

	byte second =45; //0-59
	byte m =29; //0-59
	byte hour =8; //0-23
	byte weekday=2;
	byte monthDay =23; //1-31
	byte month =3; //1-12
	byte year =13; //0-99

	Wire.beginTransmission(DS1307_ADDRESS);

	Wire.write(zero); //stop Oscillator

	Wire.write(decToBcd(second));
	Wire.write(decToBcd(m));
	Wire.write(decToBcd(hour));
	Wire.write(decToBcd(weekday));
	Wire.write(decToBcd(monthDay));
	Wire.write(decToBcd(month));
	Wire.write(decToBcd(year));

	Wire.write(zero); //start

	Wire.endTransmission();

}

byte decToBcd(byte val) {
	// Convert normal decimal numbers to binary coded decimal
	return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val) {
	// Convert binary coded decimal to normal decimal numbers
	return ( (val/16*10) + (val%16) );
}

bool getdate()
{

	Wire.beginTransmission(DS1307_ADDRESS);

	Wire.write(zero);

	Wire.endTransmission();

	Wire.requestFrom(0x68,7);

	//Serial.println(Wire.available());
	if(Wire.available()>0)
	{
		second = bcdToDec(Wire.read());
		m = bcdToDec(Wire.read());
		hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
		weekday=bcdToDec(Wire.read());
		monthDay = bcdToDec(Wire.read());
		month = bcdToDec(Wire.read());
		year = bcdToDec(Wire.read());
		return true;
	} else {
		return false;
	}

}

void printDate(){

	Serial.print(monthDay);
	Serial.print("/");

	Serial.print(month);
	Serial.print("/");

	Serial.print(year);
	Serial.print(" ");
	Serial.print(hour);
	Serial.print(":");
	Serial.print(m);
	Serial.print(":");
	Serial.println(second);
}