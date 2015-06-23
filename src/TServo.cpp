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
void TServo::SetDegreeWithPID(float dif)
{
//	uint16_t safeDegree=libutil::Clamp(lowerBound,pid.getTunedValue(dif),upperBound);
	Servo::SetDegree(pid.getTunedValue(dif));
}

void TServo::SetPID(float p,float i,float d)
{
	pid.setControlValue(PID<float,uint16_t>::Controller::P,p);
	pid.setControlValue(PID<float,uint16_t>::Controller::I,i);
	pid.setControlValue(PID<float,uint16_t>::Controller::D,d);
}
