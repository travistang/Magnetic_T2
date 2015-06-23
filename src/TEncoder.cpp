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
					int		countPerRevolution) :
	libsc::DirEncoder::DirEncoder(config),
	wheelDiameter(wheelDiameter),
	countPerRevolution(countPerRevolution)
{
	updateInterval=interval;
}

float TEncoder::getCarSpeedByEncoderCount()
{
	Update();
	float distance=PI * wheelDiameter
					  * (float)GetCount() / (float)countPerRevolution;
	return distance*1000.0f/(float)updateInterval;
//	return GetCount();
}

void TEncoder::setUpdateInterval(uint16_t interval)
{
	updateInterval=interval;
}
