/*
 * MotorPID.cpp
 *
 *  Created on: 9 Jul, 2015
 *      Author: Travis
 */

#include "MotorPID.h"

MotorPID::MotorPID(Resources* r) : resources(r)
,timer(libsc::System::Time())
{
	updateParams();
	lastError = 0;
}

void MotorPID::updateParams()
{
	kp = resources->config.c_motorPIDControlVariable[0];
	ki = resources->config.c_motorPIDControlVariable[1];
	kd = resources->config.c_motorPIDControlVariable[2];
	lowerBound = resources->config.c_motorPowerLowerBound;
	upperBound = resources->config.c_motorPowerUpperBound;
//	sp = resources->config.c_targetEncoderCount;
	sp = resources->config.c_motorPIDSp;
}

//void MotorPID::setTarget(int32_t targetCount)
//{
//	resources->config.c_targetEncoderCount() = targetCount;
//	updateParams();
//}

void MotorPID::updateMotorValue()
{
	updateParams();

	uint16_t dt = libsc::System::Time() - timer;
	if(dt == 0)
		dt = 1;
	int32_t error = sp - resources->state.encoderCount;
	float result = (float)resources->config.c_motorPower;

	result += kp*error;
	result += kd*(error-lastError)/dt;
	result += ki*(error+lastError)*dt/2;

	if(result < 0)
	{
		resources->config.c_motorRotateClockwise = false;
		result = -result;
	}else
	{
		resources->config.c_motorRotateClockwise = true;
	}

	if(result< lowerBound) result = lowerBound;
	if(result> upperBound) result = upperBound;
	resources->config.c_motorPower = result;

	timer = libsc::System::Time();
}
