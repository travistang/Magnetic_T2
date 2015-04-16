/*
 * TLedModule.cpp
 *
 *  Created on: 24 Mar, 2015
 *      Author: Travis
 */

#include <TLedModule.h>
#if VERSION >=2L
TLedModule::TLedModule(Resources* resources)
:Module(resources,LED),ledCount(resources->config.c_ledCount){
	if(resources==0)delete this;
	led=new TLed[ledCount]();
	timer=new TimerInt[ledCount];
	for(int i=0;i<ledCount;i++)
	{
		led[i].SetEnable(false);
		timer[i]=libsc::System::Time();
	}
}
TLedModule::~TLedModule()
{
	delete[] led;
	delete[] timer;
}

void TLedModule::task()
{
	TimerInt currentTime=libsc::System::Time();
	for(int i=0;i<ledCount;i++)
	{
		if(currentTime-timer[i]>=i*100)
			{
				led[i].Switch();
				timer[i]=libsc::System::Time();
			}
	}
}

void	TLedModule::loopWhileSuspension()
{
	for(int i=0;i<ledCount;i++)
	{
		led[i].SetEnable(true);
	}
}

void	TLedModule::debugLoop()
{
	return;
}
#endif
