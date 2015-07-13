/*
 * TMagneticSensorModule.cpp
 *
 *  Created on: 25 Mar, 2015
 *      Author: Travis
 */

#include <TMagneticSensorModule.h>
#if VERSION >=2L
TMagneticSensorModule::
TMagneticSensorModule(Resources* resources)
:Module(resources,MAGNETIC_SENSOR),sensorCount(resources->
		config.c_magneticSensorCount)
{
	if(sensorCount>resources->config.MAX_MAGNETIC_SENSOR_COUNT)
	{
		delete this;
		return;
	}
	sensor=new TMagneticSensor
			[sensorCount];
	timer=new TimerInt[sensorCount];
	for(int i=0;i<sensorCount;i++)
	{
		MagneticSensor::MGConfig config=
				MagneticSensor::getMagneticSensorConfig();
		timer[i]=libsc::System::Time();
	}
}
TMagneticSensorModule::~TMagneticSensorModule()
{
	if(sensorCount>resources->config.MAX_MAGNETIC_SENSOR_COUNT)
	{
		delete[] timer;
		delete[] sensor;
	}

}

void TMagneticSensorModule::task()
{
//		MagneticSensor::ReadingState state[4];
//		int i=0;
#if INSTANCE_STORAGE_METHOD == 1
//	for(int i=0;i<sensorCount;i++)
//	{
//		sensor[i].update();
//		resources->state.magneticSensorReading[i]
//			=sensor[i].movingAverage();
//	}
#endif
	loopWhileSuspension();
}
void TMagneticSensorModule::loopWhileSuspension()
{
	for(int i=0;i<sensorCount;i++)
	{
		resources->state.magneticSensorReading[i]
			=sensor[i].adcReading()/resources->state.magneticSensorReadingAverage[i];
	}
}
void TMagneticSensorModule::debugLoop()
{

}
#endif

void TMagneticSensorModule::alternateTask()
{
	float sum [6] = { 0 };
	int sampleCount = 2000;
	for(int i = 0 ;i<sampleCount; i++)
	{
		for(int j = 0; j<sensorCount; j++)
		{
			sum[j] +=sensor [j].adcReading();
		}
	}
	for(int i = 0; i < 6; i++)
	{
		sum[i] /= sampleCount ;
		resources->state.magneticSensorReadingAverage[i] = sum[i];
	}
	buzz(7);
	resources->config.c_isFetchingReadingAverage = false ;
}


