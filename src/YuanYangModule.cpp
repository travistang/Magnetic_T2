/*
 * YuanYangModule.cpp
 *
 *  Created on: 27 Jun, 2015
 *      Author: Travis
 */

#include "YuanYangModule.h"

YuanYangModule::YuanYangModule(Resources* r) : Module(r,SONIC)
//,batteryMeter(getBmConfig())
//,batteryMeter({r->config.c_voltmeterVoltageRatio})
{}


void YuanYangModule::task()
{
	if(sonic.is_valid())
	{
		resources->state.carDistance = sonic.distance();
		uint16_t dist = resources->state.carDistance;
		if(dist<20)
		{
			buzz();
		}

	}else
	{
		resources->state.carDistance = -1;
	}
}

//void YuanYangModule::checkVoltage()
//{
//	resources->config.c_batteryVoltage = batteryMeter.GetVoltage();
//	if(resources->config.c_batteryVoltage <= resources->config.c_batteryMinVoltage)
//		while(1)
//			buzz();
//}

//libsc::BatteryMeter::Config YuanYangModule::getBmConfig()
//{
//	libsc::BatteryMeter::Config config;
//	config.voltage_ratio = resources->config.c_voltmeterVoltageRatio;
//	return config;
//}