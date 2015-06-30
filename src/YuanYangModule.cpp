/*
 * YuanYangModule.cpp
 *
 *  Created on: 27 Jun, 2015
 *      Author: Travis
 */

#include "YuanYangModule.h"

YuanYangModule::YuanYangModule(Resources* r) : Module(r,SONIC)
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
