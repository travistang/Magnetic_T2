/*
 * tLed.cpp
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#include "tLed.h"
int TLed::s_count=0;
libsc::Led::Config getLedConfig(int id)
{
	libsc::Led::Config config;
	config.id=id;
	return config;
}
TLed::TLed(const Led::Config &config) :
	Led::Led(config),enabled(true),
	blinkInterval(20),
	ID(s_count),
	lastUpdateTime(libsc::System::Time())
{
	s_count++;
}
TLed::TLed():TLed(getLedConfig(s_count))
{
}
void TLed::c_setEnable(int id,bool flag)
{
	if(ID==id)
	enabled=flag;
}

void TLed::c_setBlinkInterval(int id,uint16_t interval)
{
	if(ID==id)
	{
		blinkInterval=interval;
	}

}
