/*
 * TMagneticSensor.cpp
 *
 *  Created on: 29 Mar, 2015
 *      Author: Travis
 */

#include "TMagneticSensor.h"
unsigned int TMagneticSensor::sensorCount=0;
unsigned int TMagneticSensor::window=6;
TMagneticSensor::TMagneticSensor() :
	adc(getConfig()),sum(0),filter(0),
	max(100),min(0),sampleCount(0)
{
	sample=new float[window];
}

uint16_t TMagneticSensor::adcReading()
{
	return adc.GetResult();
}
float TMagneticSensor::rawReading()
{
	return adc.GetResultF()/3.3 *(max-min)+min;
}
float TMagneticSensor::filteredReading()
{
	if(filter==0)return rawReading();
	return filter->Filter(rawReading());
}
void TMagneticSensor::update()
{
	/*
	 * Update moving average by using __reading();
	 */
	if(window==0)return;
	float reading;
	if(filter!=0)
	{
		reading=filteredReading();

	}else
	{
		reading=rawReading();
	}
	sampleCount++;
	if(sampleCount<window)
	{
		sample[sampleCount-1]=reading;
		sum+=reading;
	}else
	{
		sum-=sample[0];
		for(unsigned int i=0;i<window-1;i++)
		{
			sample[i]=sample[i+1];
		}
		sample[window-1]=reading;
		sum+=reading;
		sampleCount--;
	}
}
float TMagneticSensor::movingAverage()
{
	if(sampleCount==0)return 0;
	return sum/sampleCount;
}
void TMagneticSensor::useFilter(Filter* filter)
{
	this->filter=filter;
}
void TMagneticSensor::setRange(float min,float max)
{
	if(max<=min)return;
	this->min=min;
	this->max=max;
}
