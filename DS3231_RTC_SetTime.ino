#include <DS3231.h>
#include <Wire.h>

DS3231 myRTC;

bool century = false;
bool h12Flag;
bool pmFlag;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
		byte& hour, byte& minute, byte& second) {
	// Call this if you notice something coming in on
	// the serial port. The stuff coming in should be in
	// the order YYMMDDwHHMMSS, with an 'x' at the end (or an "a").
	boolean gotString = false;
	char inChar;
	byte temp1, temp2;
	char inString[20];

	byte j=0;
	while (!gotString) {
		while (Serial.available()) {
			inChar = Serial.read();
			inString[j] = inChar;
			j += 1;
			if (inChar == 'x') {
				gotString = true;
			}
			if (inChar == 'a') {
				return;
			}
		}
	}
	Serial.println(inString);
	// Read year first
	temp1 = (byte)inString[0] -48;
	temp2 = (byte)inString[1] -48;
	year = temp1*10 + temp2;
	// now month
	temp1 = (byte)inString[2] -48;
	temp2 = (byte)inString[3] -48;
	month = temp1*10 + temp2;
	// now date
	temp1 = (byte)inString[4] -48;
	temp2 = (byte)inString[5] -48;
	date = temp1*10 + temp2;
	// now Day of Week
	dOW = (byte)inString[6] - 48;
	// now hour
	temp1 = (byte)inString[7] -48;
	temp2 = (byte)inString[8] -48;
	hour = temp1*10 + temp2;
	// now minute
	temp1 = (byte)inString[9] -48;
	temp2 = (byte)inString[10] -48;
	minute = temp1*10 + temp2;
	// now second
	temp1 = (byte)inString[11] -48;
	temp2 = (byte)inString[12] -48;
	second = temp1*10 + temp2;

	//myRTC.setClockMode(false);  // set to 24h
	myRTC.setClockMode(true); // set to 12h

	myRTC.setYear(year);
	myRTC.setMonth(month);
	myRTC.setDate(date);
	myRTC.setDoW(dOW);
	myRTC.setHour(hour);
	myRTC.setMinute(minute);
	myRTC.setSecond(second);
}

void setup() {
	// Start the serial port
	Serial.begin(57600);

	// Start the I2C interface
	Wire.begin();

	Serial.println("Enter date string in the order: YYMMDDwHHMMSS, with an 'x' at the end.");
	Serial.println("('a' to abort and check saved date)");
	getDateStuff(year, month, date, dOW, hour, minute, second);
}
void loop() {
	// Start with the year
	Serial.print("2");
	if (century) {			// Won't need this for 89 years.
		Serial.print("1");
	} else {
		Serial.print("0");
	}
	Serial.print(myRTC.getYear(), DEC);
	Serial.print(' ');

	// then the month
	Serial.print(myRTC.getMonth(century) , DEC);
	Serial.print(" ");

	// then the date
	Serial.print(myRTC.getDate(), DEC);
	Serial.print(" ");

	// and the day of the week
	Serial.print(myRTC.getDoW(), DEC);
	Serial.print(" ");

	// Finally the hour, minute, and second
	Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
	Serial.print(" ");
	Serial.print(myRTC.getMinute(), DEC);
	Serial.print(" ");
	Serial.print(myRTC.getSecond(), DEC);

	// Add AM/PM indicator
	if (h12Flag) {
		if (pmFlag) {
			Serial.print(" PM ");
		} else {
			Serial.print(" AM ");
		}
	} else {
		Serial.print(" 24h ");
	}
	// Optional
	// Display the temperature
	Serial.print("T=");
	Serial.print(myRTC.getTemperature(), 2);
	Serial.println();
	delay(1000);
}
