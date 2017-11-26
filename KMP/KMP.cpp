/*
 Name:		KMP.cpp
 Created:	19.11.2017 08:53:38
 Author:	Thomas
 Editor:	http://www.visualmicro.com
*/

#include "KMP.h"


KMP::KMP()
{
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(LATCH_PIN, OUTPUT);
	pinMode(DATA_PIN, OUTPUT);

	pinMode(RESET_PIN, OUTPUT);

	digitalWrite(RESET_PIN, HIGH);

	for (int i = 0; i < 4; i++) {
		pinMode(motors[i].pinPwm, OUTPUT);
	}
}

KMP::~KMP() 
{
	digitalWrite(RESET_PIN, LOW);
}

void KMP::Stop()
{
	digitalWrite(RESET_PIN, LOW);

	SetAllMotors(STOP);
	SetAllSpeed(255);

	WriteControllByte();

	digitalWrite(RESET_PIN, HIGH);
}

void KMP::SetSpeed(uint8_t ammount)
{
	SetAllSpeed(ammount);

	WriteControllByte();
}


void KMP::DriveLeft(uint8_t driveSpeed)
{
	SetAllSpeed(driveSpeed);

	WriteControllByte();
}

void KMP::DriveRight(uint8_t driveSpeed)
{
	SetAllSpeed(driveSpeed);

	WriteControllByte();
}

void KMP::DriveForward(uint8_t driveSpeed)
{
	SetAllMotors(FWD);
	SetAllSpeed(driveSpeed);

	WriteControllByte();
}

void KMP::DriveBackward(uint8_t driveSpeed)
{
	SetAllMotors(BWD);
	SetAllSpeed(driveSpeed);

	WriteControllByte();
}


void KMP::TurnLeft()
{
	motors[0].state = BWD;
	motors[1].state = BWD;
	motors[2].state = FWD;
	motors[3].state = FWD;

	WriteControllByte();
}

void KMP::TurnRight()
{
	motors[0].state = FWD;
	motors[1].state = FWD;
	motors[2].state = BWD;
	motors[3].state = BWD;

	WriteControllByte();
}


void KMP::WriteControllByte()
{
	// Foreach motor
	for (int i = 0; i < 4; i++) {


		if (motors[i].state == STOP) {
			bitClear(motorsControllByte, motors[i].bitFwd);
			bitClear(motorsControllByte, motors[i].bitBwd);
		}
		else if (motors[i].state == FWD) {
			bitSet(motorsControllByte, motors[i].bitFwd);
			bitClear(motorsControllByte, motors[i].bitBwd);
		}
		else if (motors[i].state == BWD) {
			bitClear(motorsControllByte, motors[i].bitFwd);
			bitSet(motorsControllByte, motors[i].bitBwd);
		}
	}


	digitalWrite(LATCH_PIN, LOW);
	shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, motorsControllByte);

	for (int i = 0; i < 4; i++) {
		analogWrite(motors[i].pinPwm, motors[i].speed);
	}

	digitalWrite(LATCH_PIN, HIGH);
}

uint8_t KMP::GetMotorsControllByte()
{
	return motorsControllByte;
}

void KMP::SetAllMotors(MotorState state) 
{
	// Foreach motor
	for (int i = 0; i < 4; i++) {
		motors[i].state = state;
	}
}

void KMP::SetAllSpeed(uint8_t speed)
{
	// Foreach motor
	for (int i = 0; i < 4; i++) {
		motors[i].speed = speed;
	}
}