/*
 Name:		KMP.h
 Created:	19.11.2017 08:53:38
 Author:	Thomas
 Editor:	http://www.visualmicro.com
*/

#ifndef _KMP_h
#define _KMP_h


#define M1_FWD_BIT 4
#define M1_BWD_BIT 5
#define M1_PWM_PIN 5

#define M2_FWD_BIT 6
#define M2_BWD_BIT 7
#define M2_PWM_PIN 6

#define M3_FWD_BIT 3
#define M3_BWD_BIT 2
#define M3_PWM_PIN 9

#define M4_FWD_BIT 1
#define M4_BWD_BIT 0
#define M4_PWM_PIN 10

#define CLOCK_PIN 7
#define DATA_PIN  13
#define LATCH_PIN 12
#define RESET_PIN 8


#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class KMP
{

public:
	KMP();
	~KMP();

	void Stop();
	void SetSpeed(uint8_t ammout);

	void DriveLeft(uint8_t driveSpeed);
	void DriveRight(uint8_t driveSpeed);
	void DriveForward(uint8_t driveSpeed);
	void DriveBackward(uint8_t driveSpeed);

	void TurnLeft();
	void TurnRight();

	uint8_t GetMotorsControllByte();

	enum MotorState
	{
		FWD,
		BWD,
		STOP,
	};

	struct Motor 
	{
	public:
		MotorState state = STOP;
		uint8_t speed = 255;

		uint8_t bitFwd, bitBwd;
		uint8_t pinPwm;

		Motor(uint8_t fwd, uint8_t bwd, uint8_t pwm) {
			bitFwd = fwd;
			bitBwd = bwd;

			pinPwm = pwm;

			pinMode(pinPwm, OUTPUT);
		}
	};

private:
	Motor motors[4] =
	{
		Motor(M1_FWD_BIT, M1_BWD_BIT, M1_PWM_PIN),
		Motor(M2_FWD_BIT, M2_BWD_BIT, M2_PWM_PIN),
		Motor(M3_FWD_BIT, M3_BWD_BIT, M3_PWM_PIN),
		Motor(M4_FWD_BIT, M4_BWD_BIT, M4_PWM_PIN)
	};

	uint8_t motorsControllByte;
	
	void WriteControllByte();
	void SetAllMotors(MotorState state);
	void SetAllSpeed(uint8_t speed);

};

#endif

