/*
 * TEncoder.cpp
 *
 *  Created on: 1 Mar, 2015
 *      Author: Travis
 */

#include <TEncoder.h>

TEncoder::TEncoder( const Config &config,
					uint16_t interval,
					float	wheelDiameter,
					float   gearRatio,
					int		countPerRevolution) :
	libsc::DirEncoder::DirEncoder(config),
	wheelDiameter(wheelDiameter),
	countPerRevolution(countPerRevolution),
	gearRatio(gearRatio)
{
	updateInterval=interval;
}

float TEncoder::getCarSpeedByEncoderCount()
{
	Update();
	//TODO is this correct?
	float distance=2*PI * wheelDiameter *GetCount() / (gearRatio * countPerRevolution);
	return distance*1000.0f/updateInterval;
//	return GetCount();
}
float TEncoder::getCarSpeedByEncoderCount(int32_t count)
{
	return PI * wheelDiameter* count / countPerRevolution;
}
void TEncoder::setUpdateInterval(uint16_t interval)
{
	updateInterval=interval;
}

float			TEncoder::getDistanceTraveled()
{
	return 2*PI * wheelDiameter *GetCount() / (gearRatio * countPerRevolution);
}
