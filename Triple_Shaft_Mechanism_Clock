
//source code for "3D Printed Triple Shaft Stepper Motor Mechanism With Arduino Control" article from instructables.com
#include <AccelStepper.h>
#include <DS3231.h>

bool century = false;
bool h12Flag;
bool pmFlag;

int currentHour;
int currentMinute;
int currentSecond;

DS3231 myRTC;

//Define some steppers and the pins that will use
//Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin1 2
#define stepPin1 5
#define dirPin2 3
#define stepPin2 6
#define dirPin3 4
#define stepPin3 7
int stepsPerRevolution = 360;
long secondPos;
long minutePos;
long hourPos;
long hourStep;
long minuteStep;
int tempSecond = 0;

//Create a new instance of the AccelStepper class:
AccelStepper hourMotor = AccelStepper(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper minuteMotor = AccelStepper(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper secondMotor = AccelStepper(AccelStepper::DRIVER, stepPin3, dirPin3);

void setup()
{
	//Start the serial port for debugging
	//Serial.begin(57600);

	//Start the I2C interface
	Wire.begin();
	hourMotor.setMaxSpeed(1000.0);
	minuteMotor.setMaxSpeed(1000.0);
	secondMotor.setMaxSpeed(1000.0);

	hourStep = 60/(stepsPerRevolution/12); //2
	minuteStep = 60/(stepsPerRevolution/60); //10

	secondMotor.setCurrentPosition(0);
	minuteMotor.setCurrentPosition(0);
	hourMotor.setCurrentPosition(0);

}

void loop()
{
	//for debugging
	//Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
	//Serial.print(" ");
	//Serial.print(myRTC.getMinute(), DEC);
	//Serial.print(" ");
	//Serial.println(myRTC.getSecond(), DEC);
	currentHour = myRTC.getHour(h12Flag, pmFlag);
	currentMinute = myRTC.getMinute();
	currentSecond = myRTC.getSecond();

	//the hour hand ( setClockMode (see the "DS3231_RTC_SetTime" sketch) is true so the hour integer is between 0 and 12 )
	if (hourMotor.currentPosition() == stepsPerRevolution && currentHour == 0)
	{
		hourMotor.setCurrentPosition(0) ;
	}
	hourPos = (currentHour * (stepsPerRevolution/12)) + (currentMinute + 1)/hourStep;
	while (hourMotor.currentPosition() < hourPos)
	{
		//Serial.print("H__");
		//Serial.print(currentHour);
		//Serial.print("  ");
		//Serial.print("H** ");
		//Serial.print(hourMotor.currentPosition());
		//Serial.print("  ");
		//Serial.print("H-- ");
		//Serial.println(hourPos);
		hourMotor.moveTo(hourPos);
		hourMotor.setSpeed(125);  //constant speed
		hourMotor.run();
	}

	//the minute hand
	if (minuteMotor.currentPosition() == stepsPerRevolution  && currentMinute == 0)
	{
		minuteMotor.setCurrentPosition(0);
	}
	minutePos = currentMinute * (stepsPerRevolution/60) + (currentSecond + 1)/minuteStep;
	while (minuteMotor.currentPosition() < minutePos + 1)
	{
		//Serial.print("M__");
		//Serial.print(currentMinute);
		//Serial.print("M** ");
		//Serial.print(minuteMotor.currentPosition());
		//Serial.print("M-- ");
		//Serial.println(minutePos);
		minuteMotor.moveTo(minutePos);
		minuteMotor.setSpeed(125);	//constant speed
		minuteMotor.run();
	}

	//the second hand
	if (secondMotor.currentPosition() == stepsPerRevolution && currentSecond == 1)
	{
		secondMotor.setCurrentPosition(0);
	}
	if (currentSecond == 0) {
		secondPos = stepsPerRevolution; //starting the clock at 0 second exactly should be avoided
	}
	else {
		secondPos = currentSecond * (stepsPerRevolution/60) ;
	}
	while (secondMotor.currentPosition() < secondPos)
	{
		//Serial.print("S__");
		//Serial.print(currentSecond);
		//Serial.print("  ");
		//Serial.print("S** ");
		//Serial.print(secondMotor.currentPosition());
		//Serial.print("  ");
		//Serial.print("S-- ");
		//Serial.println(secondPos);
		secondMotor.setAcceleration(100); //acceleration/deceleration mode
		secondMotor.setMaxSpeed(200);
		secondMotor.moveTo(secondPos);
		//secondMotor.setSpeed(100);
		secondMotor.run();
	}
}
