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
	for(int i=0;i<sensorCount;i++)
	{
		sensor[i].update();
		resources->state.magneticSensorReading[i]
			=sensor[i].movingAverage();
	}
#endif
}
void TMagneticSensorModule::loopWhileSuspension()
{
	for(int i=0;i<sensorCount;i++)
	{
		resources->state.magneticSensorReading[i]
			=sensor[i].adcReading();
	}
}
void TMagneticSensorModule::debugLoop()
{

}
#endif


