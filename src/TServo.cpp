/*
 * TServo.cpp
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#include <TServo.h>

TServo::TServo(const Config &config,uint16_t lowerBound,
		uint16_t upperBound,float multiplier)
:libsc::TrsD05::TrsD05(config),
 lowerBound(lowerBound),upperBound(upperBound)
{
	angleMultiplier=multiplier;
}

void TServo::setAngleBySignalDifference(float dif)
{
	SetDegree(900-angleMultiplier*dif);
}

void TServo::SetDegree(uint16_t degree)
{
	uint16_t safeDegree=libutil::Clamp(lowerBound,degree,upperBound);
	Servo::SetDegree(safeDegree);
}
void TServo::SetReverseDegree(uint16_t degree)
{
	SetDegree(900-degree);
}
void TServo::SetDegreeWithPID(uint16_t degree)
{
	uint16_t safeDegree=libutil::Clamp(lowerBound,pid.getTunedValue(degree),upperBound);
	Servo::SetDegree(safeDegree);
}

void TServo::SetPID(float p,float i,float d)
{
	pid.setControlValue(PID<uint16_t>::Controller::P,p);
	pid.setControlValue(PID<uint16_t>::Controller::I,i);
	pid.setControlValue(PID<uint16_t>::Controller::D,d);
}
